#include "config.h"
#if FM_AUDIO_ADVANCED==1

#ifndef _I2S_COMMON_H
#define _I2S_COMMON_H

#define CHANNELS        (2)
#define BITSPERSAMPLE   (24)
#define SAMPLE_SIZE     (240)
#define BUFF_SIZE       (SAMPLE_SIZE * CHANNELS * (BITSPERSAMPLE / 8)) // 两声道，24比特
#define AUDIO_QUEUE_SIZE 10

// Structure to hold audio data
typedef struct
{
    uint8_t samples[BUFF_SIZE];
    size_t size;
} audio_data_t;

#endif

#endif