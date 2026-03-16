/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_AUDIO_CODER_WAV==1

#include <Arduino.h>
#include "wav_decoder.h"

WavDecoder::WavDecoder(AudioSource *source) : source_(source)
{
    buffSize = 128;
    buff = NULL;
    buffPtr = 0;
    buffLen = 0;
}

WavDecoder::~WavDecoder()
{
    free(buff);
    buff = NULL;
}

bool WavDecoder::Stop()
{
    free(buff);
    buff = NULL;
    return source_->Close();
}

bool WavDecoder::Init()
{
    if (!ReadWAVInfo()) {
      Serial.printf_P(PSTR("Init: failed during ReadWAVInfo\n"));
      return false;
    }

    return true;
}

bool WavDecoder::Decode()
{
    if (eof_) return false;
    
    // Try and stuff the buffer one sample at a time
    if (bitsPerSample_ == 8) {
        uint8_t l, r;
        if (!GetBufferedData(1, &l)) Stop();
        if (channels_ == 2) {
            if (!GetBufferedData(1, &r)) Stop();
        } else {
            r = 0;
        }
        samples_[0] = l;
        samples_[1] = r;

        return true;
    } else if (bitsPerSample_ == 16) {
        if (!GetBufferedData(2, &samples_[0])) Stop();
        if (channels_ == 2) {
            if (!GetBufferedData(2, &samples_[1])) Stop();
        } else {
            samples_[1] = 0;
        }
        return true;
    }

    return false;
}

// Handle buffered reading, reload each time we run out of data
bool WavDecoder::GetBufferedData(int bytes, void *dest)
{
  uint8_t *p = reinterpret_cast<uint8_t*>(dest);
  while (bytes--) {
    // Potentially load next batch of data...
    if (buffPtr >= buffLen) {
        buffPtr = 0;
        uint32_t toRead = availBytes > buffSize ? buffSize : availBytes;
        buffLen = source_->Read( buff, toRead );
        availBytes -= buffLen;
    }
    if (buffPtr >= buffLen) {
        eof_ = true;
        return false; // No data left!
    }

    *(p++) = buff[buffPtr++];
  }
  return true;
}

bool WavDecoder::ReadWAVInfo()
{
    uint32_t u32;
    uint16_t u16;
    int toSkip;

    // WAV specification document:
    // https://www.aelius.com/njh/wavemetatools/doc/riffmci.pdf

    // Header == "RIFF"
    if (!ReadU32(&u32)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if (u32 != 0x46464952) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, invalid RIFF header\n"));
      return false;
    }

    // Skip ChunkSize
    if (!ReadU32(&u32)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };

    // Format == "WAVE"
    if (!ReadU32(&u32)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if (u32 != 0x45564157) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, invalid WAVE header\n"));
      return false;
    }

    // there might be JUNK or PAD - ignore it by continuing reading until we get to "fmt "
    while (1) {
      if (!ReadU32(&u32)) {
        Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
        return false;
      };
      if (u32 == 0x20746d66) break; // 'fmt '
    };

    // subchunk size
    if (!ReadU32(&u32)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if (u32 == 16) { toSkip = 0; }
    else if (u32 == 18) { toSkip = 18 - 16; }
    else if (u32 == 40) { toSkip = 40 - 16; }
    else {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, appears not to be standard PCM \n"));
      return false;
    } // we only do standard PCM

    // AudioFormat
    if (!ReadU16(&u16)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if (u16 != 1) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, AudioFormat appears not to be standard PCM \n"));
      return false;
    } // we only do standard PCM

    // NumChannels
    if (!ReadU16(&channels_)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if ((channels_<1) || (channels_>2)) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, only mono and stereo are supported \n"));
      return false;
    } // Mono or stereo support only

    // SampleRate
    if (!ReadU32(&sampleRate_)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if (sampleRate_ < 1) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, unknown sample rate \n"));
      return false;
    }  // Weird rate, punt.  Will need to check w/DAC to see if supported

    // Ignore byterate and blockalign
    if (!ReadU32(&u32)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if (!ReadU16(&u16)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };

    // Bits per sample
    if (!ReadU16(&bitsPerSample_)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    if ((bitsPerSample_!=8) && (bitsPerSample_ != 16)) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, only 8 or 16 bits is supported \n"));
      return false;
    }  // Only 8 or 16 bits

    // Skip any extra header
    while (toSkip) {
      uint8_t ign;
      if (!ReadU8(&ign)) {
        Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
        return false;
      };
      toSkip--;
    }

    // look for data subchunk
    do {
      // id == "data"
      if (!ReadU32(&u32)) {
        Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
        return false;
      };
      if (u32 == 0x61746164) break; // "data"
      // Skip size, read until end of chunk
      if (!ReadU32(&u32)) {
        Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
        return false;
      };
      if(!source_->Seek(u32, SEEK_CUR)) {
        Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data, seek failed\n"));
        return false;
      }
    } while (1);

    // Skip size, read until end of file...
    if (!ReadU32(&u32)) {
      Serial.printf_P(PSTR("ReadWAVInfo: failed to read WAV data\n"));
      return false;
    };
    availBytes = u32;

    // Now set up the buffer or fail
    buff = reinterpret_cast<uint8_t *>(malloc(buffSize));
    if (!buff) {
      Serial.printf_P(PSTR("ReadWAVInfo: cannot read WAV, failed to set up buffer \n"));
      return false;
    };
    buffPtr = 0;
    buffLen = 0;

    return true;
}

#endif