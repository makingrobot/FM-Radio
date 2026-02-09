/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_ADVANCED==1

#ifndef _FM_RADIO_H
#define _FM_RADIO_H

#include <string>
#include <Arduino.h>
#include <radio.h>
#include <TEA5767.h>

class FMRadio {
private:
	TEA5767 *radio_;
	
public:
	FMRadio();
	void Init();
	void SetFrequency(uint16_t frequency);
	std::string GetFrequency();
	bool IsStereo();
	uint8_t GetRSSI();
	
};

#endif //_FM_AUDIO_H

#endif