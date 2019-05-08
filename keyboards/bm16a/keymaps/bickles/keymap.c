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
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
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
   // case DOUBLE_HOLD: register_code(KC_LALT); break;
  //  case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}



void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: layer_move(_BASE); break;
    case DOUBLE_TAP: layer_move(_FN1); break;
    case TRIPLE_TAP: layer_move(_FN2); break;
 //   case DOUBLE_HOLD: unregister_code(KC_LALT);
//    case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [X_CTL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset)
};





// Defines the keycodes used by our macros in process_record_user
/*enum custom_keycodes {
  KT_UP
};
*/
#define KT_UP LCTL(KC_BSPACE)
#define KT_DN LCTL(KC_KP_ENTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x4(
    TD(X_CTL),  KC_HOME,  KC_KP_PLUS,    KT_UP , \
    KC_PGDN,  KC_LEFT,  KC_KP_MINUS,  KT_DN, \
    MO(_FN2), KC_VOLU,  KC_MPLY,  KC_MPRV, \
    MO(_FN1), KC_VOLD,  KC_MUTE,  KC_MNXT  \
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
  // Capslock priority
   {
    // look layer...
    switch (biton32(layer_state)) {
      case _FN1:
        rgblight_setrgb(RGB_CORAL);
        break;
      case _FN2:
        rgblight_setrgb(RGB_GOLD);
        break;
      default:
        rgblight_setrgb(RGB_WHITE);
        break;
    }
  }
}

void led_set_user(uint8_t usb_led) {
  // must be trigger to
  // - activate capslock color
  // - go back to the proper layer color if needed when quitting capslock
  update_led();
}

uint32_t layer_state_set_user(uint32_t state) {
  // must be trigger to
  // - activate a layer color
  // - de-activate a layer color
  update_led();
  return state;
}
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KT_UP:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;

  }
  return true;
}
*/