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
#include "tap_dance_setup.c" // Setup Tap Dance
#include "tap_dance_enum.c" // Where Tap Dance enums are stored
#include "scln_coln.c" // Tap dance for ;:
#include "tap_dance_katana.c"
#include "tap_dance_actions.c" // All other Tap Dances
#include "katana_shortcuts.c" // Katana Hotkeys

//Define layers for BDN9
enum BDN9_layers {
    _BROWSE = 0,
    _KATANA,
    _RV,
    _FEEDBIN,
    _UTIL,
    };

//Define custom keycodes for BDN9 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Default Layout -- For general browsing
        __________________________________________________
        | KNB_0: Vol Dn/Up  |       | KNB_1: Scroll      |
        | Press: Mute       |       | Press: Play/Pause  |
        | ----------------- | LAYER | -----------------  |
        | Scroll Left       | Home  | Scroll Right       |
        | Back              | End   | Forward            |
     */
    [_BROWSE] = LAYOUT(
        KC_MUTE ,  MO(_UTIL)  , KC_MPLY,
        KC_WH_L ,  KC_HOME    , KC_WH_R,
        KC_WBAK ,  KC_END     , KC_WFWD
    ),
//----------------------------------------------------------
    /*  Katana Layout -- General Katana Work
        ____________________________________________________
        | KNB_0: Up/Down    |       | KNB_1: Tab/Shift Tab |
        | Press: Enter      |       | Press: Tilde         |
        | ----------------- | LAYER | -----------------    |
        | Control + Shift   | KP +  | Live/Preview Render  |
        | Control + Enter   | KP -  | Control + B          |
     */
    [_KATANA] = LAYOUT(
        KC_ENT  ,  MO(_UTIL)  , KC_GRAVE    ,
        KTNA_UP ,  KC_PLUS , TD(KTNA_RENDER) ,
        KTNA_IN ,  KC_MINS , LCTL(KC_B)
    ),
//------------------------------------------------------------------
    /*  RV Layout -- RV Hotkeys
        ____________________________________________________________
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
//------------------------------------------------------------------
    /*  Feedbin Layout -- Feedbin.me hotkeys
        ____________________________________________________________
        | KNB_0: Next/Previous  |            | KNB_1: Page Up/Down |
        | Press:     Star       |            | Press: Read/Unread  |
        | --------------------- |    LAYER   | -----------------   |
        |     Open Original     | Expand Tag |   Load from link    |
        |         Left          |    Space   |        Right        |
     */
    [_FEEDBIN] = LAYOUT(
        KC_S   , MO(_UTIL) , KC_M,
        KC_V   , KC_E      , KC_C,
        KC_LEFT, KC_SPACE  , KC_RIGHT
    ),
//------------------------------------------------------------------
    /*  Utility Layer for adjusting Layer,LEDs,RESET,Etc
        _________________________________________________
        | KNB_0: LED +/-       |       | KNB_1: LED MODE|
        | Press: Static LED    |       | Press: LED Off |
        | -------------------- | LAYER | -------------- |
        |         RESET        | LED + | Live Render    |
        |        RGB Mode      | LED - | Control + B    |
*/
    [_UTIL] = LAYOUT(
        RGB_MODE_PLAIN  ,  _______      , RGB_TOG     ,
         _______        ,  TO(_BROWSE)  , TO(_KATANA) ,
        TO(_FEEDBIN)    ,  TO(_RV)      ,  _______
    ),   
};

// Rotary Encoder Code

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _BROWSE: // Media Layer Left Rotary Encoder
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
            case _FEEDBIN: // Feedbin Layer Left Rotary Encoder
                if (clockwise) {
                    tap_code(KC_J);
                } else {
                    tap_code(KC_K);
                }
            break; 
            case _UTIL: // Util Layer Left Rotary Encoder
                if (clockwise) {
                    rgblight_decrease_val();
                } else {
                    rgblight_increase_val();
                }
            break;   
        }
    }
    else if (index == 1) {
        switch (biton32(layer_state)) {
            case _BROWSE: // Media Layer Right Rotary Encoder
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
            case _FEEDBIN: // Feedbin Layer Right Right Encoder
                if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
            break;
            case _UTIL: // Util Layer Right Rotary Encoder
                if (clockwise) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
        }
    }
};

// Common LED indicator
/*Layers
    _BROWSE = 0,
    _KATANA,
    _RV,
    _UTIL,
    _FEEDBIN,
*/
void update_led(void) {
   {
    switch (biton32(layer_state)) {
      case _BROWSE:
        rgblight_setrgb(RGB_WHITE); // Browse color.
        break;
      case _KATANA:
        rgblight_setrgb(214,162,0); // Katana color.
        break;
      case _RV:
        rgblight_setrgb(49,170,0); // RV color.
        break;
      case _FEEDBIN:
        rgblight_setrgb(0,64,160); // Feedbin color.
        break;
      case _UTIL:
        rgblight_setrgb(0,175,106); // Util color.
        break;
      default:
        rgblight_setrgb(RGB_WHITE); // 
        break;
    }
  }
}
uint32_t layer_state_set_user(uint32_t state) {
  update_led();
  return state;
}