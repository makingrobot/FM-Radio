#include "config.h"
#if FM_AUDIO_ADVANCED==1

#include <Arduino.h>

#include "i2s_adc_driver.h"
#include "src/framework/sys/log.h"

#define TAG "I2sAdcDriver"
#define SAMPLE_RATE (96000)

bool I2sAdcDriver::Init(i2s_port_t port, int sample_rate, i2s_data_bit_width_t bit_width) {
    i2s_port_ = port;

    i2s_chan_config_t rx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(port, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&rx_chan_cfg, NULL, &rx_chan_));

    i2s_std_config_t rx_std_cfg = {
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
            .dout = data_pin_,
            .din = GPIO_NUM_NC,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_chan_, &rx_std_cfg));
    /* Enable the RX channel */
    ESP_ERROR_CHECK(i2s_channel_enable(rx_chan_));

    Log::Info(TAG, "I2S rx channel initialized.");
    return true;
}

int I2sAdcDriver::Read(audio_data_t *data, uint8_t *buf) {
    size_t bytes = 0;
    int ret = i2s_channel_read(rx_chan_, buf, BUFF_SIZE, &bytes, 1000);
    if (ret == ESP_OK)
    {
        data->size = bytes;
        memcpy(data->samples, buf, bytes);
    }

    return ret;
}

#endif