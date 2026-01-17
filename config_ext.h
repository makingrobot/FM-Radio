#ifndef _CONFIG_EXT_H
#define _CONFIG_EXT_H

#define FM_AUDIO_BASIC          1
#define FM_AUDIO_ADVANCED       0

#if FM_AUDIO_BASIC==1
#include "src/fmradio/app_config.h"
#include "src/fmradio/board_config.h"

#elif FM_AUDIO_ADVANCED==1
#include "src/fmradio2/app_config.h"
#include "src/fmradio2/board_config.h"

#endif

#endif