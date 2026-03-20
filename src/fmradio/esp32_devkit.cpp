/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_BASIC==1

#include "esp32_devkit.h"

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <esp_system.h>
#include <driver/gpio.h>

#include "src/framework/board/onebutton_impl.h"
#include "src/framework/display/u8g2_display.h"
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

void ESP32_DEVKIT::ButtonTick() {
    for (const auto& pair : button_map()) {
        pair.second->Tick();
    }
}

void ESP32_DEVKIT::InitializeI2C() {
    // TEA5767使用
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    // SSD1306使用
    Wire1.begin(I2C_SDA_2_PIN, I2C_SCL_2_PIN);
}

void ESP32_DEVKIT::InitializeButtons() {
    Log::Info( TAG, "Init buttons ......");

    std::shared_ptr<Button> prev_button = std::make_shared<OneButtonImpl>(kPrevButton, PREV_BUTTON_PIN);
    prev_button->BindAction(ButtonAction::Click);
    AddButton(prev_button);

    std::shared_ptr<Button> next_button = std::make_shared<OneButtonImpl>(kNextButton, NEXT_BUTTON_PIN);
    next_button->BindAction(ButtonAction::Click);
    AddButton(next_button);

    buttontick_task_ = new FrtTask("ButtonTick_Task");
    buttontick_task_->OnLoop([this](){
        ButtonTick();
        delay(1);
    });
    buttontick_task_->Start(4096, tskIDLE_PRIORITY + 1);
}

void ESP32_DEVKIT::InitializeDisplay() {

    Log::Info( TAG, "Init ssd1306 display ......" );

    U8G2 *u8g2 = new U8G2_SSD1306_128X64_NONAME_F_SW_I2C(
        /* rotation */ U8G2_R0, 
        /* i2c clk */ I2C_SCL_2_PIN,
        /* i2c data */ I2C_SDA_2_PIN,
        /* reset=*/ U8X8_PIN_NONE
    );
    u8g2->setI2CAddress(OLED_I2C_ADDRESS << 1);

    //u8g2_font_unifont_t_chinese2
    display_ = new U8g2Display(u8g2, DISPLAY_WIDTH, DISPLAY_HEIGHT, u8g2_font_wqy14_t_gb2312);

}

void ESP32_DEVKIT::InitializePeripherals() {
    
    Log::Info( TAG, "Init peripherals ......");

}

#endif