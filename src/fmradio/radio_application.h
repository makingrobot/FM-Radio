/**
 * FM收音机
 * 
 * Author: Billy Zhang（vx: billyzh）
 */

#ifndef _RADIO_APPLICATION_H
#define _RADIO_APPLICATION_H

#include "src/framework/app/application.h"
#include <string>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "fm_radio.h"

class RadioApplication : public Application {
public:
    RadioApplication();
    
    bool OnPhysicalButtonEvent(const std::string& button_name, const ButtonAction action) override;
    bool OnSensorDataEvent(const std::string& sensor_name, const SensorValue& value) override;

    const std::string& GetAppName() const override { return "FMRadio"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    void ChangeFrequency(uint8_t index);
    
    QueueHandle_t queue_;

    std::string last_message_;
    FMRadio *radio_;

    uint8_t index_ = 0;


};

#endif //_RADIO_APPLICATION_H
