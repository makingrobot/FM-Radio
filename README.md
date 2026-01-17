## FM 收音机

一款使用TEA5767模组的FM 收音机应用，基于ESP32 Arduino Framework开发框架

## 套件
### 一、基础套件
具备基础收音机功能
* 1 x ESP32 兼容开发板
* 1 x TEA5767模块（I2C接口）
* 1 x SSD1306显示模块（I2C接口）
* 2 x 按键模块
* 1 x 有源小音箱
* 1 x 电源模块（可选）

### 二、进阶套件
除基础功能外，还支持录制存储
* 1 x ESP32 兼容开发板
* 1 x TEA5767模块（I2C接口）
* 1 x 2.4寸 TFT LCD显示模块（SPI接口）,带SD存储
* 2 x 按键模块
* 1 x 音频ADC模块（模拟信号转I2S信号）
* 1 x I2S音频放大模块
* 1 x 无源小音箱
* 1 x 电源模块（可选）

### 编译
1. 打开src/fm-radio/board_config.h文件 修改对应引脚编号；
2. 打开config_ext.h文件，基础套件设置 FM_AUDIO_BASIC 为1，进阶套件设置 FM_AUDIO_ADVANCED 为1；
3. 编译上传运行；
