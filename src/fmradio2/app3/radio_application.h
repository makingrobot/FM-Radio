/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_ADVANCED==1 && FM_AUDIO_ADVANCED_APP3==1

#ifndef _RADIO_APPLICATION_H
#define _RADIO_APPLICATION_H

#include "src/framework/app/application.h"
#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "../common/fm_radio.h"

class RadioApplication : public Application {
public:
    RadioApplication();
    
    void AudioInputTask();
    void AudioOutputTask();
    
    bool OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) override;
    
    const std::string& GetAppName() const override { return "FMRadio"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    void ChangeFrequency(uint8_t index);
    
    QueueHandle_t button_queue_ = NULL;
    QueueHandle_t audio_queue_ = NULL;
    TaskHandle_t audio_input_taskhandle_;
    TaskHandle_t audio_output_taskhandle_;

    std::string last_message_;
    FMRadio *radio_;
    
    uint8_t index_ = 0;


};

#endif //_RADIO_APPLICATION_H

#endif