/* Copyright 2019
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
enum layers {
  _BASE = 0,
  _FN1,
  _FN2,
};
enum custom_keycodes {
  DIVIDE_BY_2,
  MULTPL_BY_2,
};
#define KT_UP LCTL(KC_BSPACE)
#define KT_DN LCTL(KC_ENT)
#define RENDER LCTL(KC_P)
#define LRENDER LCTL(LSFT(KC_P))
#define ADD_TO_CAT LALT(KC_C)
#define CTL_B LCTL(KC_B)
// setup Quad Tap Dance
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  X_CTL = 0,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

// End tapdance setup

//Tap Dance Definitions

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}
//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};
void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: layer_move(_BASE); break;
    case DOUBLE_TAP: layer_move(_FN1); break;
    case TRIPLE_TAP: layer_move(_FN2); break;
 }
}
void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: layer_move(_BASE); break;
    case DOUBLE_TAP: layer_move(_FN1); break;
    case TRIPLE_TAP: layer_move(_FN2); break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [X_CTL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};
// End TapDance Setup

// Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x4(
    TD(X_CTL),  MULTPL_BY_2,    KC_KP_PLUS,    KT_UP , \
    KC_VOLU,    DIVIDE_BY_2,    KC_KP_MINUS,   KT_DN, \
    KC_VOLD, KC_VOLU,           CTL_B,         LRENDER, \
    MO(_FN1), ADD_TO_CAT,       LRENDER,       RENDER  \
  ),
  [_FN1] = LAYOUT_ortho_4x4(
    TD(X_CTL),   KC_P7,    RESET,    KC_P9,   \
    KC_TAB,   KC_P4,    KC_P5,    KC_P6,   \
    KC_ENT,   KC_P1,    KC_P2,    KC_P3,   \
    _______,  KC_P0,    KC_P0,    KC_DOT   \
  ),
  [_FN2] = LAYOUT_ortho_4x4(
    TD(X_CTL),  RGB_HUI,  RGB_SAI,  RGB_VAI, \
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD, \
    TD(X_CTL),  _______,  _______,  RESET,   \
    BL_STEP,  RESET,  _______,  _______   \
  )

};

// Common LED indicator
void update_led(void) {
   {
    switch (biton32(layer_state)) {
      case _FN1:
        rgblight_setrgb(RGB_CORAL);
        break;
      case _FN2:
        rgblight_setrgb(RGB_RED);
        break;
      default:
        rgblight_setrgb(RGB_WHITE);
        break;
    }
  }
}
uint32_t layer_state_set_user(uint32_t state) {
  update_led();
  return state;
}
// Macro's
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DIVIDE_BY_2:
      if (record->event.pressed) {
        register_code16(KC_BTN1);
        unregister_code16(KC_BTN1);
        SEND_STRING("/2" SS_TAP(X_ENTER));
      } else {
      }
      break;
    case MULTPL_BY_2:
      if (record->event.pressed) {
        register_code16(KC_BTN1);
        unregister_code16(KC_BTN1);
        SEND_STRING("*2" SS_TAP(X_ENTER));
      } else {
      }
      break;
  }
  return true;
}
