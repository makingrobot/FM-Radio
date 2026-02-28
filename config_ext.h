#ifndef _CONFIG_EXT_H
#define _CONFIG_EXT_H

#define FM_AUDIO_BASIC          1
#define FM_AUDIO_ADVANCED       0

#if FM_AUDIO_ADVANCED==1
#define FM_AUDIO_ADVANCED_APP1  1
#endif

#if FM_AUDIO_BASIC==1
#include "src/fmradio/app_config.h"
#include "src/fmradio/board_config.h"

#elif FM_AUDIO_ADVANCED_APP1==1
#include "src/fmradio2/app1/app_config.h"
#include "src/fmradio2/app1/board_config.h"

#elif FM_AUDIO_ADVANCED_APP2==1
#include "src/fmradio2/app2/app_config.h"
#include "src/fmradio2/app2/board_config.h"

#elif FM_AUDIO_ADVANCED_APP3==1
#include "src/fmradio2/app3/app_config.h"
#include "src/fmradio2/app3/board_config.h"

#endif

#endif