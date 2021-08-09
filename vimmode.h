#pragma once

#include QMK_KEYBOARD_H
#include <stdint.h>

#define SHIFT_HELD (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
#define CTRL_HELD  (get_mods() & (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL)))
#define GUI_HELD   (get_mods() & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)))

#undef TAPPING_TERM
#define TAPPING_TERM 250

bool process_vim_key(uint16_t keycode, keyrecord_t* record);
void mod_type(uint16_t modcode, uint16_t keycode);
