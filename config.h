#pragma once

#ifdef AUDIO_ENABLE
#include "song_list.h"
#define STARTUP_SONG   SONG(WORKMAN_SOUND)
#define DAC_SAMPLE_MAX 1023U

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4
#endif

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#undef DEBOUNCE
#define DEBOUNCE 5

#define ONESHOT_TAP_TOGGLE 2

#define PERMISSIVE_HOLD

#undef IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_FORCE_HOLD
