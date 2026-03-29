/**
 * FM收音机
 *
 * 本程序可不受限制的用于学习，商业用途请联系作者。
 *
 * Author: Billy Zhang（vx: billyzh）
 */
#include "config.h"
#if FM_AUDIO_ADVANCED == 1 && FM_AUDIO_ADVANCED_APP1 == 1

#ifndef _RADIO_APPLICATION_H
#define _RADIO_APPLICATION_H

#include <string>

#include "src/framework/app/application.h"
#include "src/framework/audio/audio_pipe.h"
#include "src/framework/sys/frt_queue.h"
#include "../common/fm_radio.h"

class RadioApplication : public Application
{
public:
    RadioApplication();

    bool OnPhysicalButtonEvent(const std::string &button_name, const ButtonAction action) override;

    const std::string &GetAppName() const override { return "FMRadio"; }
    const std::string &GetAppVersion() const override { return "1.0.0"; }

protected:
    void OnInit() override;
    void OnLoop() override;

private:
    void ChangeFrequency(uint8_t index);

    std::string last_message_;
    FMRadio *radio_;
    AudioPipe *pipe_;

    FrtQueue *button_queue_;

    uint8_t index_ = 0;
};

#endif //_RADIO_APPLICATION_H

#endif