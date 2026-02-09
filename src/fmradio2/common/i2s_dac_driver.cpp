#include "config.h"
#if FM_AUDIO_ADVANCED==1

#include <Arduino.h>

#include "i2s_dac_driver.h"
#include "src/framework/sys/log.h"

#define TAG "I2sDacDriver"
#define SAMPLE_RATE (96000)

bool I2sDacDriver::Init(i2s_port_t port, int sample_rate, i2s_data_bit_width_t bit_width) {
    i2s_port_ = port;

    i2s_chan_config_t tx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(port, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&tx_chan_cfg, &tx_chan_, NULL));
    
    i2s_std_config_t tx_std_cfg = {
        .clk_cfg = {
            .sample_rate_hz = sample_rate,
            .clk_src = I2S_CLK_SRC_DEFAULT, 
            .mclk_multiple = I2S_MCLK_MULTIPLE_384, 
            .bclk_div = 8, 
        },
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(bit_width, I2S_SLOT_MODE_STEREO),
        .gpio_cfg = {
            .mclk = mclk_pin_,
            .bclk = bclk_pin_,
            .ws = ws_pin_,
            .dout = GPIO_NUM_NC,
            .din = data_pin_,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_chan_, &tx_std_cfg));
    /* Enable the TX channel */
    ESP_ERROR_CHECK(i2s_channel_enable(tx_chan_));

    Log::Info(TAG, "I2S tx channel initialized.");
    return true;
}

int I2sDacDriver::Write(audio_data_t *data) {
    size_t bytes;
    int ret = i2s_channel_write(tx_chan_, data->samples, data->size, &bytes, 1000);
    return ret; 
}

#endif