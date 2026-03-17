/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_ADVANCED==1 && FM_AUDIO_ADVANCED_APP3==1

#include "esp32_devkit.h"

#include <Arduino.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <esp_system.h>
#include <driver/gpio.h>

#include "src/framework/board/onebutton_impl.h"
#include "src/framework/display/tft_display.h"
#include "src/framework/sys/system_reset.h"
#include "src/framework/led/gpio_led.h"

#define TAG "ESP32_DEVKIT"

void* create_board() { 
    return new ESP32_DEVKIT();
}

ESP32_DEVKIT::ESP32_DEVKIT() : Board() {
    Log::Info(TAG, "===== Create Board ...... =====");

    //I2cDetect(GPIO_NUM_22, GPIO_NUM_21);
    InitializeI2C();
    InitializeButtons();
    InitializeDisplay();
    InitializePeripherals();

    Log::Info( TAG, "===== Board config completed. =====");
}

void ESP32_DEVKIT::InitializeI2C() {
    // TEA5767
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

}

void ESP32_DEVKIT::ButtonTick() {
    for (auto& pair : button_map()) {
        pair.second->Tick();
    }
}

void ESP32_DEVKIT::InitializeButtons() {
    Log::Info( TAG, "Init buttons ......");

    std::shared_ptr<Button> prev_button = std::make_shared<OneButtonImpl>(kPrevButton, PREV_BUTTON_PIN);
    prev_button->BindAction(ButtonAction::Click);
    AddButton(prev_button);

    std::shared_ptr<Button> next_button = std::make_shared<OneButtonImpl>(kNextButton, NEXT_BUTTON_PIN);
    next_button->BindAction(ButtonAction::Click);
    AddButton(next_button);

    xTaskCreate([](void* param) {
        ESP32_DEVKIT *board = (ESP32_DEVKIT *)param;
        while (1) {
            board->ButtonTick();
            delay(1);
        }
    }, "ButtonTick_Task", 4096, this, 1, NULL);
}

void ESP32_DEVKIT::InitializeDisplay() {

    Log::Info( TAG, "Init ssd1306 display ......" );
    
    /**
     * 注意！！！
     * 请在TFT_eSPI库包内的User_Setup.h中配置引脚
     */
    tft_espi_ = new TFT_eSPI(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    tft_espi_->invertDisplay(DISPLAY_INVERT_COLOR);
    
    //u8g2_font_unifont_t_chinese2
    display_ = new TftDisplay(tft_espi_, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    
}

void ESP32_DEVKIT::InitializePeripherals() {
    
    Log::Info( TAG, "Init peripherals ......");

    // ADC
    adc_driver_ = new I2sAdcDriver(GPIO_NUM_NC, GPIO_NUM_NC, GPIO_NUM_NC, GPIO_NUM_NC);

    // DAC
    dac_driver_ = new I2sDacDriver(GPIO_NUM_NC, GPIO_NUM_NC, GPIO_NUM_NC, GPIO_NUM_NC);
    
}

#endif