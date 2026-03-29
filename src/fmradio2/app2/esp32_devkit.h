/**
 * FM收音机
 * 
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_ADVANCED==1 && FM_AUDIO_ADVANCED_APP2==1

#ifndef _ESP32_DEVKIT_H
#define _ESP32_DEVKIT_H

#include <driver/gpio.h>

#include "src/framework/sys/log.h"
#include "src/framework/app/application.h"
#include "src/framework/board/board.h"
#include "src/framework/board/button.h"
#include "src/framework/display/display.h"
#include "src/framework/audio/audio_codec.h"
#include "src/framework/led/led.h"
#include "src/framework/sys/frt_task.h"

#include "board_config.h"

static const std::string kPrevButton = "prev_button";
static const std::string kNextButton = "next_button";

class ESP32_DEVKIT : public Board {
private:
    Display *display_ = nullptr;
    AudioCodec *audio_codec_;
    FrtTask *buttontick_task_;

    void InitializeI2C();
    void InitializeButtons();
    void InitializeDisplay();
    void InitializeAudioCodec();

public:
    ESP32_DEVKIT();

    Display* GetDisplay() override { return display_; }
    AudioCodec *GetAudioCodec() { return audio_codec_; }
    
    void ButtonTick();
};

#endif //_ESP32_DEVKIT_H

#endif
