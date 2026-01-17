#ifndef _BOARD_DEF_EXT_H
#define _BOARD_DEF_EXT_H

#define BOARD_NAME "esp32-devkit"

#if FM_AUDIO_BASIC == 1
#include "src/fmradio/esp32_devkit.h"

#elif FM_AUDIO_ADVANCED == 1
#include "src/fmradio2/esp32_devkit.h"

#endif

#endif