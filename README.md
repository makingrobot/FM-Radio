## FM 收音机

一款使用TEA5767模组的FM 收音机应用，基于ESP32 Arduino Framework开发框架

## 套件
### 一、基础套件
基础收音机功能
* 1 x ESP32-S3 兼容开发板
* 1 x TEA5767模块（I2C接口）
* 1 x SSD1306显示模块（I2C接口）
* 2 x 按键模块
* 1 x 有源小音箱
* 1 x 电源模块（可选）

### 二、进阶套件
具备收单机功能、录制存储，WAV，MP3音频播放，音频频谱显示
* 1 x ESP32-S3 兼容开发板
* 1 x TEA5767模块（I2C接口）
* 1 x SSD1306显示模块（I2C接口）
* 1 x 2.4寸 TFT LCD显示模块（SPI接口）,带SD存储
* 3 x 按键模块
* 1 x I2S音频ADC模块
* 1 x I2S音频DAC模块
* 1 x 电位器模块
* 1 x 有源小音箱
* 1 x 电源模块（可选）

### 编译
* 打开src/fm-radio/board_config.h文件 修改对应引脚编号；
* 基础套件：打开config_ext.h文件，设置 FM_AUDIO_BASIC 为1，
* 进阶套件：打开config_ext.h文件，设置 FM_AUDIO_ADVANCED 为1，FM_AUDIO_ADVANCED_APPx 为1；
* 编译上传运行；

### 应用说明
* src/fmradio：简单收音机
* src/fmradio2/app1：基于I2S通道的收音机
* src/fmradio2/app2: 支持录音的收音机
* src/fmradio2/app3: 支持音频频谱显示的收音机
