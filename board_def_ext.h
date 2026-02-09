#ifndef _BOARD_DEF_EXT_H
#define _BOARD_DEF_EXT_H

#define BOARD_NAME "esp32-devkit"

#if FM_AUDIO_BASIC == 1
#include "src/fmradio/esp32_devkit.h"

#elif FM_AUDIO_ADVANCED_APP1 == 1
#include "src/fmradio2/app1/esp32_devkit.h"

#elif FM_AUDIO_ADVANCED_APP2 == 1
#include "src/fmradio2/app2/esp32_devkit.h"

#elif FM_AUDIO_ADVANCED_APP3 == 1
#include "src/fmradio2/app3/esp32_devkit.h"

#endif

#endif