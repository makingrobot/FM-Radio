/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_BASIC==1

#ifndef _ESP32_DEVKIT_H
#define _ESP32_DEVKIT_H

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "src/framework/sys/log.h"
#include "src/framework/app/application.h"
#include "src/framework/board/board.h"
#include "src/framework/display/display.h"
#include "src/framework/led/led.h"

#include "board_config.h"

static const std::string kPrevButton = "prev_button";
static const std::string kNextButton = "next_button";

class ESP32_DEVKIT : public Board {
private:
    Display *display_ = nullptr;
    TaskHandle_t button_taskhandle_;

    void InitializeButtons();
    void InitializeDisplay();
    void InitializePeripherals();

public:
    ESP32_DEVKIT();

    Display* GetDisplay() override { return display_; }

    void ButtonTick();
};

#endif //_ESP32_DEVKIT_H

#endif