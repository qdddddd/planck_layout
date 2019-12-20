#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "ez.h"
#include "layers.h"
#include "vimmode.h"

enum planck_keycodes {
    RGB_SLD = EZ_SAFE_RANGE,
    DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define KC_CMD KC_LGUI

// Shorter keycodes
#define DYN_STT1 DYN_REC_START1
#define DYN_STT2 DYN_REC_START2
#define DYN_STOP DYN_REC_STOP
#define DYN_PLY1 DYN_MACRO_PLAY1
#define DYN_PLY2 DYN_MACRO_PLAY2
#define SLEEP    C(S(KC_EJCT))
#define HOME     G(KC_LEFT)
#define BOTTOM   G(KC_DOWN)
#define TOP      G(KC_UP)
#define END      G(KC_RGHT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off

    /* Base layer (Qwerty)
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │  ⇥  │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  BS │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *   Tap for Esc --│  ⌃  │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *    Tap for ( -- │  ⇧  │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │  ⇧  │ -- Tap for Enter
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │ NUM │ NAV │  ⌘  │  ⌥  │LOWER│Space│Space│RAISE│  ⬅  │  ⬇  │  ⬆  │  ➡  │ -- Tap for ]
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_BASE]   = LAYOUT_planck_grid(
        KC_TAB,        KC_Q,     KC_W,   KC_E,    KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_T(KC_ESC), KC_A,     KC_S,   KC_D,    KC_F,  KC_G,   KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOTE,
        KC_LSPO,       KC_Z,     KC_X,   KC_C,    KC_V,  KC_B,   KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
        TT(_NUMPAD),   TT(_NAV), KC_CMD, KC_LALT, LOWER, KC_SPC, KC_NO, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    /* Lower layer
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │  ~  │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  (  │  )  │ Del │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │ VIM │ ⌘ A │ ⌘ S │ ⌘ D │ ⌘ F │     │     │  -  │  =  │  {  │  }  │  |  │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │  ⇧  │ ⌘ Z │ ⌘ X │ ⌘ C │ ⌘ V │     │ ⌘ N │     │  <  │  >  │  \  │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │     │     │     │Caps │     │     │ ⌘ ⬅ │ ⌘ ⬇ │ ⌘ ⬆ │ ⌘ ➡ │
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_LOWER]  = LAYOUT_planck_grid(
        KC_TILD,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        TO(_VIM), G(KC_A), G(KC_S), G(KC_D), G(KC_F), _______, _______, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE,
        KC_LSFT,   G(KC_Z), G(KC_X), G(KC_C), G(KC_V), _______, G(KC_N), _______, KC_LABK, KC_RABK, KC_BSLS, _______,
        _______,   _______, _______, _______, _______, KC_CAPS, KC_NO,   _______, HOME,    BOTTOM,  TOP,     END
    ),

    /* Raise layer
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │  `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │ ⌘ BS│
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │ Del │     │     │     │     │     │     │  _  │  +  │  [  │  ]  │  \  │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │  ⇧  │     │     │     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │     │     │     │     │     │     │Home │PgDn │PgUp │ End │
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_RAISE]  = LAYOUT_planck_grid(
        KC_GRAVE,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    G(KC_BSPC),
        KC_DELETE, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_RSHIFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   _______, _______, _______, _______, _______, KC_NO,   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    /* Adjust layer (pressing both LOWER and RAISE)
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │     │Mac1R│Mac2R│     │Reset│     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │ Del │     │MacSR│     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │Mac1P│Mac2P│     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │     │     │     │Sleep│     │     │     │     │     │     │
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, DYN_STT1, DYN_STT2, _______, RESET,   _______, _______, _______, _______, _______, _______, _______,
        KC_DEL,  _______,  DYN_STOP, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, DYN_PLY1, DYN_PLY2, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______,  _______, _______, SLEEP,   KC_NO,   _______, _______, _______, _______, _______
    ),

    /* Numpad layer
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │     │ F9  │ F10 │ F11 │ F12 │     │     │  7  │  8  │  9  │  -  │ BS  │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │ F5  │ F6  │ F7  │ F8  │     │  ^  │  4  │  5  │  6  │  +  │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │ F1  │ F2  │ F3  │ F4  │     │  %  │  1  │  2  │  3  │  /  │Enter│
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │BASE │     │     │     │     │     │     │  0  │  0  │  .  │  *  │     │
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_NUMPAD] = LAYOUT_planck_grid(
        _______,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_BSPC,
        _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, KC_CIRC, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_PERC, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS, KC_PENT,
        TO(_BASE), _______, _______, _______, _______, _______, KC_NO,   KC_KP_0, KC_KP_0, KC_PDOT, KC_PAST, _______
    ),

    /* Navigation layer
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │     │     │     │     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │     │     │     │     │  ⬅  │  ⬇  │  ⬆  │  ➡  │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │MidCk│     │     │     │     │     │Prev │Next │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │BASE │     │     │Vol- │Play │     │Vol+ │     │Brig-│Brig+│     │
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_NAV]    = LAYOUT_planck_grid(
        _______, _______,   _______,    _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______,   _______,    _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
        _______, _______,   KC_MS_BTN3, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT,  _______, _______,
        _______, TO(_BASE), _______,    _______, KC_VOLD, KC_MPLY, KC_NO,   KC_VOLU, _______, KC_F14,   KC_F15,  _______
    ),

    /* Vim layer as a placeholder
     *                 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     *                 │     │     │     │     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │     │     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │  ⇧  │     │     │     │     │     │     │     │     │     │     │     │
     *                 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     *                 │     │     │     │     │     │     │     │     │     │     │     │     │
     *                 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
    [_VIM] = LAYOUT_planck_grid(
        XXXXXXX,  _______, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX,
        KC_LCTRL, _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX,
        KC_LSFT,  XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______,
        XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )

    // clang-format on
};

void keyboard_post_init_user(void) {
    keyboard_config.led_level = 1;
    debug_enable              = true;
    debug_keyboard            = true;
}

#include <print.h>

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (IS_LAYER_ON(_VIM) && process_vim_key(keycode, record)) {
        return false;
    }

    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

    /*switch (keycode) {*/
    /*case:*/
    /*break;*/
    /*}*/

    return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode         = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter  = 0;
uint8_t muse_offset    = 70;
uint16_t muse_tempo    = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo += 1;
            } else {
                muse_tempo -= 1;
            }
        }
    } else {
        if (clockwise) {
#ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
#else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
#endif
        } else {
#ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
#else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
#endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    switch (get_highest_layer(state)) {
        case _NUMPAD:
            planck_ez_left_led_on();
            break;

        case _NAV:
            planck_ez_right_led_on();
            break;

        case _VIM:
            planck_ez_left_led_on();
            planck_ez_right_led_on();
            break;
        default:
            break;
    }

    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
