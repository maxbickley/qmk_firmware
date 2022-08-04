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
// Add Layers Here
enum layers {
  _BASE = 0,
  _GAME,
  _OBS,
  _SKETCHUP,
  _NUM,
  _UTIL
};
//Advance Layers Macro
#define HIGHEST_LAYER _SKETCHUP //replace X with your highest layer

static uint8_t current_layer = 0;

enum custom_keycodes {
    KC_LUP = SAFE_RANGE, //cycle layers in up direction
    KC_LDN //cycle layers in down direction
#define ENUT LT(_UTIL,KC_ENT) //Enter/Until Combo key
//#define ENUT TG(_UTIL) //Enter/Until Combo key

#define BASE TO(_BASE) //Set Base Layer
#define GAME TO(_GAME) //Set Game Layer
#define OBS TO(_OBS) //Set OBS Layer
#define SKTU TO(_SKETCHUP) //Set SketchUp Layer
//Windows Hotkeys
#define NXDS LGUI(LCTL(KC_RIGHT)) //Next Desktop
#define PVDS LGUI(LCTL(KC_LEFT)) //Previous Desktop
//OBS Hotykeys
#define OB_ST LCTL(LALT(LSFT(KC_L)))
#define OB_TS LCTL(LALT(LSFT(KC_K)))
#define OB_HM LCTL(LALT(LSFT(KC_J)))
#define OB_MC LCTL(LALT(LSFT(KC_M)))
#define OB_1 LCTL(LSFT(1))
#define OB_2 LCTL(LSFT(2))
#define OB_3 LCTL(LSFT(3))
#define OB_4 LCTL(LSFT(4))
#define OB_5 LCTL(LSFT(5))
#define OB_6 LCTL(LSFT(6))
#define OB_7 LCTL(LSFT(7))
#define OB_8 LCTL(LSFT(8))
};
// Common LED indicator
void update_led(void) {
   {
    switch (biton32(layer_state)) {
      case _BASE:
        rgblight_setrgb(RGB_WHITE);
        break;
      case _GAME:
        rgblight_setrgb(RGB_BLUE);
        break;
      case _OBS:
        rgblight_setrgb(RGB_GREEN);
        break;
      case _SKETCHUP:
        rgblight_setrgb(RGB_ORANGE);
        break;
    }
  }
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LUP:
    if(record->event.pressed) {
      if (current_layer == HIGHEST_LAYER){
        for (int i=1; i<=HIGHEST_LAYER; i++){
          layer_off(i);
        }
        current_layer=0;
      } else { 
        current_layer++;
        layer_on(current_layer);
      }
    }
    update_led();
    return false;

  case KC_LDN:
    if(record->event.pressed) {
      if (current_layer == 0){
        for (int i=1; i<=HIGHEST_LAYER; i++){
          layer_on(i);
        }
        current_layer=HIGHEST_LAYER;
      } else {
        layer_off(current_layer);
        current_layer--;
      }
    }
    update_led();
    return false;
  default:
    return true;
  }

}   

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* BASE //WHITE
   * ,---------------------------.
   * |   1  |   2  |   3  |   4  |
   * |------+------+------+------|
   * |   5  |   6  |   7  |   8  |
   * |------+------+------+------|
   * | LEFT |   9  |   0  | RIGHT|
   * |------+------+------+------|
   * | BKSP |   ,  |   .  |EN/UT |
   * `---------------------------'
   */
  [_BASE] = LAYOUT_ortho_4x4(
    KC_1,KC_2,KC_3,KC_4, \
    KC_5,KC_6,KC_7,KC_8, \
    KC_LEFT,KC_9,KC_0,KC_RIGHT, \
    KC_BSPC,KC_COMM,KC_DOT,ENUT  \
  ),
      /* UTIL
   * ,---------------------------.
   * | BASE | GAME | OBS  | SKTU |
   * |------+------+------+------|
   * | PVDS | ____ | ____ | NXDS |
   * |------+------+------+------|
   * | PVLY | RGBU | ____ | NXLY |
   * |------+------+------+------|
   * | RSET | RGBD | ____ | ____ |
   * `---------------------------'
   */
  [_UTIL] = LAYOUT_ortho_4x4(
    BASE, GAME, OBS, SKTU , \
    PVDS, _______, _______, NXDS, \
    KC_LDN, RGB_VAI, _______, KC_LUP, \
    RESET, RGB_VAD, _______, ENUT  \
  ),
  /* GAME //BLUE
   * ,---------------------------.
   * |   1  |   2  |   3  |   4  |
   * |------+------+------+------|
   * |   5  |   6  |   7  |   8  |
   * |------+------+------+------|
   * |   ~  |   9  |   0  | ____ |
   * |------+------+------+------|
   * | GUI  | ____ | ____ |EN/UT |
   * `---------------------------'
   */
  [_GAME] = LAYOUT_ortho_4x4(
    KC_1   ,KC_2    ,KC_3    ,KC_4, \
    KC_5   ,KC_6    ,KC_7    ,KC_8, \
    KC_GRV ,KC_9    ,KC_0    ,_______, \
    KC_LGUI, _______, _______, ENUT  \
  ),
  /* OBS //GREEN
   * ,---------------------------.
   * | OBS1 | OBS2 | OBS3 | OBS4 |
   * |------+------+------+------|
   * | OBS5 | OBS6 | OBS7 | OBS8 |
   * |------+------+------+------|
   * | DEFT |START | PTT  | TRAN |
   * |------+------+------+------|
   * | ____ | ____ | ____ |EN/UT |
   * `---------------------------'
   */
  [_OBS] = LAYOUT_ortho_4x4(
    OB_1   ,OB_2    ,OB_3    ,OB_4, \
    OB_5   ,OB_6    ,OB_7    ,OB_8, \
    OB_HM  ,OB_ST   ,OB_MC   ,OB_TS, \
    KC_LGUI, _______, _______, ENUT  \
  ),
  /* SKETCHUP //YELLOW
   * ,---------------------------.
   * | SPACE|   M  |   P  |   T  |
   * |------+------+------+------|
   * |  Z   |   Q  |   R  |   B  |
   * |------+------+------+------|
   * | LEFT | ____ | ____ | RIGHT|
   * |------+------+------+------|
   * |  ESC | ____ | NUM  |EN/UT |
   * `---------------------------'
   */
  [_SKETCHUP] = LAYOUT_ortho_4x4(
    KC_SPACE ,KC_M   ,KC_P    ,KC_T , \
    KC_Z     ,KC_Q   ,KC_R    ,KC_B   , \
    KC_LEFT  ,_______,_______ ,KC_RIGHT, \
    KC_ESC   ,_______,MO(_NUM),ENUT  \
  ),
  /* NUM 
   * ,---------------------------.
   * |   1  |   2  |   3  |   4  |
   * |------+------+------+------|
   * |   5  |   6  |   7  |   8  |
   * |------+------+------+------|
   * |   ,  |   9  |   0  |   .  |
   * |------+------+------+------|
   * |  TAB | ____ | ____ |EN/UT |
   * `---------------------------'
   */
  [_NUM] = LAYOUT_ortho_4x4(
    KC_1   ,KC_2   ,KC_3   ,KC_4, \
    KC_5   ,KC_6   ,KC_7   ,KC_8, \
    KC_COMM,KC_9   ,KC_0    ,KC_DOT, \
    KC_TAB ,KC_MINS,_______,ENUT  \
  )
};


uint32_t layer_state_set_user(uint32_t state) {
  update_led();
  return state;
} 

uint32_t layer_state_set_kb(uint32_t state) {
  update_led();
  return state;
} 
