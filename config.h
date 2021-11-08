#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG         SONG(WORKMAN_SOUND)
#define AUDIO_DAC_SAMPLE_MAX 1023U

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

#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 14

#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 120

#undef MOUSEKEY_WHEEL_TIME_TO_MAX
#define MOUSEKEY_WHEEL_TIME_TO_MAX 80

#define TAPPING_FORCE_HOLD

#define PLANCK_EZ_USER_LEDS
