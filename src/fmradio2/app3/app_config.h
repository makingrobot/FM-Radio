#include "config.h"
#if FM_AUDIO_ADVANCED==1 && FM_AUDIO_ADVANCED_APP3==1

#ifndef _APP_CONFIG_H
#define _APP_CONFIG_H

//////////////////////////////////////////////////////////////////////////////////
// 特性

// 定时器
#define CONFIG_USE_SW_TIMER                 1

// WIFI配置
#define CONFIG_USE_WIFI                     0
#define CONFIG_WIFI_CONFIGURE_ENABLE        0  

// 时钟（刷新界面）
#define CONFIG_CLOCK_ENABLE                 0  

// OTA
#define CONFIG_OTA_ENABLE                   0  
#define CONFIG_OTA_URL                      ""


#endif //_APP_CONFIG_H

#endif