## FM数字收音机

一款使用TEA5767模组的FM数字收音机应用，基于ESP32 Arduino Framework开发框架

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

## 应用
### 一、基础应用 - 简单收音机
简单收音机应用使用基础套件，TEA5767收音机模块直连有源音箱，两个按键用于调台，OLED模块显示FM频道信息。
* 打开config_ext.h文件，设置 FM_AUDIO_BASIC 为1，FM_AUDIO_ADVANCED 为0
* 打开src/fm-radio/board_config.h文件 修改对应引脚编号（或按默认设置引脚连线）；
* 编译上传运行

### 二、高级应用 - 基于I2S通道的收音机
基于I2S通道的收音机应用使用进阶套件。本应用中，我们采集TEA5767收音机模块的音频数据，将转为数字信号（A/D转换），然后使用I2S通道转输到音频放大模块输出给喇叭（D/A转换）。
* 打开config_ext.h文件，设置 FM_AUDIO_BASIC 为0，FM_AUDIO_ADVANCED 为1，FM_AUDIO_ADVANCED_APP1 为1；
* 打开src/fm-radio2/app1/board_config.h文件 修改对应引脚编号（或按默认设置引脚连线）；
* 编译上传运行；

### 三、高级应用 - 支持录音的收音机
支持录音的收音机应用使用进阶套件。本应用中，我们采集TEA5767收音机模块的音频数据，将转为数字信号（A/D转换），然后将音频数据保存到SD卡上的文件中。
* 打开config_ext.h文件，设置 FM_AUDIO_BASIC 为0，FM_AUDIO_ADVANCED 为1，FM_AUDIO_ADVANCED_APP2 为1；
* 打开src/fm-radio2/app2/board_config.h文件 修改对应引脚编号（或按默认设置引脚连线）；
* 编译上传运行；

### 四、高级应用 - 支持音频频谱显示的收音机
支持音频频谱显示的收音机使用进阶套件。本应用中，我们采集TEA5767收音机模块的音频数据，将转为数字信号（A/D转换），然后使用I2S通道转输到音频放大模块输出给喇叭（D/A转换），同时在TFT-LCD显示屏上显示音频频谱信息。
* 打开config_ext.h文件，设置 FM_AUDIO_BASIC 为0，FM_AUDIO_ADVANCED 为1，FM_AUDIO_ADVANCED_APP3 为1；
* 打开src/fm-radio2/app3/board_config.h文件 修改对应引脚编号（或按默认设置引脚连线）；
* 编译上传运行；