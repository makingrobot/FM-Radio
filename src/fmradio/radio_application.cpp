/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "radio_application.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/board.h"
#include "src/framework/lang/lang_zh_cn.h"
#include "src/framework/display/u8g2_display.h"
#include "src/framework/sys/settings.h"
#include "esp32_devkit.h"

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#define TAG "RadioApplication"

/**
 * 北京FM台频率
 * 
 * 北京文艺广播 FM87.6 
 * 北京新闻广播 FM94.5/AM828 
 * 北京音乐广播 FM97.4 
 * 京津冀之声 FM100.6 
 * 北京体育广播 FM102.5
 * 北京交通广播 FM103.9 
 * 北京城市广播副中心之声 FM107.3/AM1026 
 */

// 换成本地的FM台， 87.6 MHz = 8760 
static const uint16_t kFMFreq[7] = { 8760, 9450, 9740, 10060, 10250, 10390, 10730 };

static const std::string NVS_RADIO = "radio";
static const std::string NVS_CHN_INDEX = "chn_index";

void* create_application() {
    return new RadioApplication();
}

RadioApplication::RadioApplication() : Application() { 

    queue_ = xQueueCreate(1, sizeof(uint8_t));
}

void RadioApplication::OnInit() {
    radio_ = new FMRadio();
    radio_->Init();

    Settings sett(NVS_RADIO);
    int chn_index = sett.GetInt(NVS_CHN_INDEX, 0);

    radio_->SetFrequency(kFMFreq[chn_index]);
}

void RadioApplication::OnLoop() {

    uint8_t receive;
    if (xQueueReceive(queue_, &receive, 0) == pdPASS) {
        Log::Info(TAG, "receive %d", receive);
        if (receive == 1) {
            if (index_ > 0) {
                index_--;
                ChangeFrequency(index_);
            }
        } else if (receive == 2) {
            if (index_ < sizeof(kFMFreq)-1) {
                index_++;
                ChangeFrequency(index_);
            }
        }
        delay(100);
    }
    
    U8g2Display *display = (U8g2Display*)Board::GetInstance().GetDisplay();
    display->SetStatus(std::format("FM: {0}", radio_->GetFrequency() ));
    display->GetWindow()->SetText(1, std::format("RSSI: {0}", radio_->GetRSSI()) );
    display->GetWindow()->SetText(2, radio_->IsStereo() ? "STEREO " : "MONO");
    delay(100);
}

/**
 * 物理按键事件处理
 */
bool RadioApplication::OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) {

    Log::Info(TAG, "响应按钮：%s 的操作：%d", button_name.c_str(), action);

    if (action == ButtonAction::Click) {
        uint8_t value = 0;
        if (button_name == kPrevButton) {
            value = 1;
        } else if (button_name == kNextButton) {
            value = 2;
        }
        
        if (value > 0) {
            xQueueOverwrite(queue_, &value);
            return true;
        }
    }

    return Application::OnPhysicalButtonEvent(button_name, action);

}

bool RadioApplication::OnSensorDataEvent(const std::string& sensor_name, const SensorValue& value) {

    return Application::OnSensorDataEvent(sensor_name, value);
}

void RadioApplication::ChangeFrequency(uint8_t index) {
    radio_->SetFrequency(kFMFreq[index]);
    Log::Info(TAG, "set frequency %.1f, index:%d", kFMFreq[index] / 100.0f, index);

    Settings sett(NVS_RADIO, true);
    sett.SetInt(NVS_CHN_INDEX, index);
}
