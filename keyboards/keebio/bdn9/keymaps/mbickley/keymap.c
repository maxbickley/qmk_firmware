/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
//Define Special Keys 
enum BDN9_Keys {
    U_LAYR = SAFE_RANGE,
    D_LAYR,
    LAYER
};
//Define layers for BDN9
enum BDN9_layers {
    _MEDIA = 0,
    _KATANA,
    _RV,
    _UTIL
    };

//Define custom keycodes for BDN9 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Default Layout -- For general browsing
        | KNB_0: Vol Dn/Up  |       | KNB_1: Scroll      |
        | Press: Mute       |       | Press: Play/Pause  |
        | ----------------- | LAYER | -----------------  |
        | Scroll Left       | Home  | Scroll Right       |
        | Back              | End   | Forward            |
     */
    [_MEDIA] = LAYOUT(
        KC_MUTE ,  MO(_UTIL)  , KC_MPLY,
        KC_WH_L ,  KC_HOME    , KC_WH_R,
        KC_WBAK ,  KC_END     , KC_WFWD
    ),
//----------------------------------------------------------
    /*  Katana Layout -- General Katana Work
        | KNB_0: Up/Down    |       | KNB_1: Tab/Shift Tab |
        | Press: Enter      |       | Press: Tilde         |
        | ----------------- | LAYER | -----------------    |
        | Control + Shift   | KP +  | Live Render          |
        | Control + Enter   | KP -  | Control + B          |
     */
    [_KATANA] = LAYOUT(
        KC_ENT          ,  MO(_UTIL)  , KC_GRAVE         ,
        LCTL(KC_LSFT)   ,  KC_PLUS    , LCTL(LSFT(KC_P)) ,
        LCTL(KC_ENT)    ,  KC_MINS    , LCTL(KC_B)
    ),
//------------------------------------------------------------------
    /*  RV Layout -- RV Hotkeys
        | KNB_0: Scroll Up/Down |            | KNB_1: Page Up/Down |
        | Press: Shift + Home   |            | Press:   \          |
        | --------------------- |    LAYER   | -----------------   |
        |       Alt + Up        | Shift + .  |      Alt + Down     |
        |         [             | Shift + ,  |          ]          |
     */
    [_RV] = LAYOUT(
        LSFT(KC_HOME) , MO(_UTIL)           , KC_BSLASH     ,
        LALT(KC_UP)   , LCTL(LSFT(KC_DOT))  , LALT(KC_DOWN) ,
        KC_LBRC       , LCTL(LSFT(KC_COMM)) , KC_RBRC
    ),
//----------------------------------------------------------
//Utility Layer for adjusting Layer,LEDs,RESET,Etc
/*----------------------------------------------------------
        | KNB_0: Layer Up/Down |       | KNB_1: LED +/- |
        | Press: Default Layer |       | Press: LED Off |
        | -------------------- | LAYER | -------------- |
        |         RESET        | LED + | Live Render    |
        |        RGB Mode      | LED - | Control + B    |
*/
    [_UTIL] = LAYOUT(
        KC_ENT          ,  _______ , KC_GRAVE  ,
        LCTL(KC_LSFT)   ,  TO(_MEDIA)  , TO(_KATANA) ,
        LCTL(KC_ENT)    ,  TO(_RV)     , LCTL(KC_B)
    ),    
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _MEDIA: // Media Layer Left Rotary Encoder
                if (!clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            break;
            case _KATANA: // Katana Layer Left Rotary Encoder 
                if (!clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
            break;
            case _RV: // RV Layer Left Rotary Encoder
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            break;  
        }
    }
    else if (index == 1) {
        switch (biton32(layer_state)) {
            case _MEDIA: // Media Layer Right Rotary Encoder
                if (!clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
            break;
            case _KATANA: // Katana Layer Right Rotary Encoder 
                if (!clockwise) {
                    tap_code(KC_TAB);
                } else {
                    register_mods(MOD_BIT(KC_LSFT));
                    tap_code(KC_TAB);
                }
            break;
            case _RV: // RV Layer Left Right Encoder
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
            break;  
        }
    }
};





/*
// Sets up Layer Moving
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  keypos_t key;
  //Define variables
  uint8_t current_layer;
  uint8_t next_layer;
  switch (keycode) {
  case U_LAYR: //cycles up the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer+1;
      layer_move(next_layer);
    }
    break;
  case D_LAYR: //cycles down the layers
    if (!record->event.pressed) {
      current_layer = layer_switch_get_layer(key);
      next_layer = current_layer-1;
      layer_move(next_layer);
    }
    break;
  }
  return true;
};
    keypos_t key;
    uint8_t current_layer;
    uint8_t next_layer;
                if (clockwise) {
                        current_layer = layer_switch_get_layer(key);
                         next_layer = current_layer+1;
                        layer_move(next_layer);
                } else {
                        current_layer = layer_switch_get_layer(key);
                         next_layer = current_layer-1;
                        layer_move(next_layer);
                }
*/