#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1
#define _TL 2
#define _______ KC_TRNS
#define FN_CAPS LT(_FL, KC_DEL) // Tap for Delete, Hold for Function Layer
//Tap Dance Declarations
enum {
  TD_ESC_CAPS = 0
  };
enum keycodes {
  DYNAMIC_MACRO_RANGE
};
#include "dynamic_macro.h"

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
};
//turn on macro record
//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (!process_record_dynamic_macro(keycode, record)) {
 //       return false;
 //   }
 //   return true;
//}

// Begin Keymap
//
//
//

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer

   * ,----------------------------------------------------------------.
   * |ESC/CAPS|1|2| 3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |LT(FL)/Del| A| S| D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |SFT/ENT |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Alt |CMD |        Space          |CMD |FN |Alt|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = LAYOUT_ansi(
  (TD_ESC_CAPS),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL, \
  FN_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,  \
  KC_LSHIFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSFT,KC_UP,KC_PGDN, \
  KC_LCTL, KC_LALT,KC_LGUI,                KC_SPC,                        KC_RGUI,MO(_FL),KC_RALT, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |    |
   * |----------------------------------------------------------------|
   * |(TL) |   |Up |   |   |   |   |   |Up |  |REC1|STP|PL1|     |Ins |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|MSBTN_1|  |  |<- |Dn | ->|  |  |        |Hme |
   * |----------------------------------------------------------------|
   * |        |VU-|VU+|MUT|   |   |   |   |BL-|BL+|BL |CAPS  |   |End |
   * |----------------------------------------------------------------|
   * |    |    |    |   PLAY/PAUSE          |   |   |    |<< |>|| | >>|
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, _______,  \
  TG(_TL),_______,KC_UP,_______,_______, _______,_______,_______,KC_UP,_______,_______,_______,_______, _______,KC_INS , \
  _______,KC_LEFT,KC_DOWN,KC_RIGHT,KC_MS_BTN1,_______,_______,KC_LEFT,KC_DOWN,KC_RIGHT,_______,_______,        _______,KC_HOME, \
  _______,KC_VOLD, KC_VOLU, KC_MUTE, _______,_______, _______,  _______,BL_DEC, BL_INC, BL_TOGG,KC_CAPS,_______,KC_END, \
  _______,_______,_______,                 KC_MPLY,               _______,_______,_______,KC_MRWD, KC_MPLY, KC_MFFD),
  /* Keymap _TL: NumPad Layer
   * ,----------------------------------------------------------------.
   * |   |  |   |   |   |   |NLCK| P/ | P*| P-| P+| P.|P=|       |    |
   * |----------------------------------------------------------------|
   * |     |   |   |   |   |   |   | P1| P2| P3|   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |   |   |   |   |   |   | P4| P5| P6|   |   |        |    |
   * |----------------------------------------------------------------|
   * |        |   |   |   |   |   |   | P7| P8| P9|   |      |   |    |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |    |   |
   * `----------------------------------------------------------------'
   */
[_TL] = LAYOUT_ansi(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_PDOT, KC_PEQL, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4, KC_P5, KC_P6, KC_TRNS, KC_TRNS, KC_PENT, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS                     , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

