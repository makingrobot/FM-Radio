#include "config.h"
#if FM_AUDIO_ADVANCED==1

#ifndef _I2S_ADC_DRIVER_H
#define _I2S_ADC_DRIVER_H

#include <driver/gpio.h>
#include <driver/i2s_std.h>
#include "i2s_common.h"

/**
 * I2S ADC驱动
 * 
 * 本驱动使用早期ESP32 I2S库。
 */
class I2sAdcDriver {
public:
    I2sAdcDriver(gpio_num_t mclk_pin, gpio_num_t bclk_pin, gpio_num_t ws_pin, gpio_num_t data_pin) 
        : mclk_pin_(mclk_pin), bclk_pin_(bclk_pin), ws_pin_(ws_pin), data_pin_(data_pin) {

    }

    bool Init(i2s_port_t port, int sample_rate, i2s_data_bit_width_t bit_width);

    /**
     * I2S_Read()
     * @parameter data: pointer to buffer
     * @parameter buf: buffer size
     * @return Number of bytes read
     */
    int Read(audio_data_t *data, uint8_t *buf);

private:
    const gpio_num_t mclk_pin_;
    const gpio_num_t bclk_pin_;
    const gpio_num_t ws_pin_;
    const gpio_num_t data_pin_;

    i2s_chan_handle_t rx_chan_;
    i2s_port_t i2s_port_;
};

#endif //_I2S_ADC_DRIVER_H

#endif