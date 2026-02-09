/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_ADVANCED==1

#include <Arduino.h>
#include <Wire.h>
#include "fm_radio.h"
#include "src/framework/sys/log.h"

#define TAG "FMRadio"

/**
 * Arduino三方库：Radio
 * URL：http://www.mathertel.de/Arduino/RadioLibrary.aspx
 */
FMRadio::FMRadio(){
	radio_ = new TEA5767();
}

void FMRadio::Init() {
	delay(200);
	
	radio_->init();
	radio_->setVolume(2);
	radio_->setMono(false);
}

void FMRadio::SetFrequency(uint16_t frequency){
	radio_->setBandFrequency(RADIO_BAND_FM, frequency);
}

std::string FMRadio::GetFrequency() {
	char s[12] = { 0 };
	radio_->formatFrequency(s, sizeof(s));
	return std::string(s);
}

bool FMRadio::IsStereo() {
	RADIO_INFO info;
	radio_->getRadioInfo(&info);
	return info.stereo;
}

uint8_t FMRadio::GetRSSI() {
	RADIO_INFO info;
	radio_->getRadioInfo(&info);
	return info.rssi;
}

#endif