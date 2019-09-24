#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Define Layers

//------------------------------
#define _QWERTY 0
#define _GAMING 1
#define _LOWER 2
#define _RAISE 3
#define _SHOTS 4
#define _ADJUST 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  SHOTS,
  ADJUST,
  BACKLIT,
  GAMING,
  RGBRST
};

#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include "oled.c"
#endif

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


//Unicode

#include "emoji.c"
//------------------------------
//Shortcuts
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
//Layer toggles.
#define KC_SHOTS OSL(_SHOTS) //One shot SHOTS layer.
#define KC_HSHOTS MO(_SHOTS) //Old SHOTS layer.
#define KC_TGADJST TO(_ADJUST) //Activate ADJUST
#define KC_TGQWT TO(_QWERTY) //Activate QWERTY
#define KC_GAME TG(_GAMING) //Toggle GAMING
#define KC_QWERTY TG(_QWERTY) //Toggle QWERTY
// Mod Taps
#define KC_TBOS GUI_T(KC_TAB) //Tab when pressed, GUI when held.
#define KC_ENLW LT(_LOWER,KC_ENT) //Enter when pressed, LOWER when held.
#define KC_SPRS LT(_RAISE,KC_SPACE) //Space when pressed, RAISE when held.
#define KC_ENDSFT LSFT_T(KC_END) //End when pressed, Shift when held.
#define KC_SFTK LSFT_T(KC_GRV) //` when pressed, Shift when held.
#define KC_SFMIN RSFT_T(KC_MINS) //- when pressed, Shift when held.
//------------------------------


// Keymaps:
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       GESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TBOS,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  UNDS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LALT , SFTK ,  ENLW,    SPRS, SFMIN , SHOTS \
                              //`--------------------'  `--------------------'
  ),
  [_GAMING] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
       ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       TAB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  ENT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LALT , LSFT , SPACE,    RAISE, SFMIN , SHOTS \
                              //`--------------------'  `--------------------'
  ),
  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        GRV,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       HOME,  LBRC,    UP,  RBRC,    F2,    F5,                  THMUP, THINK, FPALM, PPOPP, HUNDP, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     ENDSFT,  LEFT,  DOWN, RIGHT,  PGUP,  PGDN,                    MWC,   LNX, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   BSPC, SPACE, _____,    _____, _____, HSHOTS \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      TILD,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,    DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____,    UP, _____, _____, _____,                   ASTR,  PLUS, _____, _____,  BSLS,   ENT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LEFT,  DOWN, RIGHT, _____, _____,                   MINS,   EQL,  VOLU,  VOLD,  MUTE,  RSFT,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____,  GAME,    _____, SPACE, HSHOTS \
                              //`--------------------'  `--------------------'
  ),
  [_SHOTS] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,TGADJST,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____,  NLCK,   INS,  CAPS,                     F1,    F2,    F3,    F4,    F5,    F6,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, _____, _____, _____,  PSCR, _____,                     F7,    F8,    F9,   F10,   F11,   F12,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                QWERTY, GAME ,  ENLW,    SPACE, RSFT , _____ \
                              //`--------------------'  `--------------------'
  ),
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, _____, _____, _____, _____,                  _____, _____, _____, _____, _____, TGQWT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, _____, _____,                  _____, _____, _____, _____, _____, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, LOWER,   SPC,      ENT, RAISE, _____ \
                              //`--------------------'  `--------------------'
  )

};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  return rotation;
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
    oled_write_ln("", false);
    oled_write_ln("", false);
    //render_logo();
  } else {
    render_status();
    oled_write_ln("", false);
    oled_write_ln("", false);
    //render_logo();
  }
}

#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}
//RGB Lighting Code:

  //,-----------------------------------------.                ,-----------------------------------------.
  //     24,    23,    18,    17,    10,    09,                     09,    10,    17,    18,    23,    24,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //     25,    22,    19,    16,    11,    08,                     08,    11,    16,    19,    22,    25,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
  //     26,    21,    20,    15,    12,    07,                     07,    12,    15,    20,    21,    26,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
  //                                 14,    13,   06,        06,    13,    14 
                              //`--------------------'  `--------------------'
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _LOWER:
        if(isLeftHand) {
          //WASD
          rgblight_setrgb_at(50,50,50, 15); // sets LED number 13 (lower) to purple on left hand
          rgblight_setrgb_at(50,50,50, 19); // sets LED number 13 (lower) to purple on left hand
          rgblight_setrgb_at(50,50,50, 20); // sets LED number 13 (lower) to purple on left hand
          rgblight_setrgb_at(50,50,50, 21); // sets LED number 13 (lower) to purple on left hand
          //Raise Key
          rgblight_setrgb_at(182,126,62, 06);
        }
        else {
          rgblight_setrgb_at(50,0,0, 24);
        }
        break;
    case _RAISE:

        if(!isLeftHand) {
          rgblight_setrgb_at(182,126,62, 06);

        }

        break;
    case _ADJUST:
      if(isLeftHand){
        rgblight_setrgb_at(148,0,211, 26); // control purple, ZXCV cyan.
        rgblight_setrgb_at(0,255,150,21);
        rgblight_setrgb_at(0,255,150,20);
        rgblight_setrgb_at(0,255,150,15);
        rgblight_setrgb_at(0,255,150,12);
      }
      break;
    case _GAMING:
        if(isLeftHand) {
          //Bottom Row
          rgblight_setrgb_at(50,0,0, 13);
          rgblight_setrgb_at(50,0,0, 6); 
          rgblight_setrgb_at(50,0,0, 14);
        }
        else {
          //Bottom Row
          rgblight_setrgb_at(50,0,0, 6); 
          rgblight_setrgb_at(50,0,0, 13); 
          rgblight_setrgb_at(50,0,0, 14); 
        }
        break;
    default:
        rgblight_enable();
        if(isLeftHand) {                        // this sets the underside LEDs (1-6) to cyan on both sides and does nothing with the rest.
          for(int i=0; i < 6; i ++) {           // this also means that if I manually change LED color to red, the bottom 6 LEDS will ALWAYS be cyan.
            rgblight_setrgb_at(25,0,0, i); // it's the only way I found to make it switch back to underglow LEDs after I've used another layer.
          }
        } else {
          for(int j=0; j < 6; j ++) {
            rgblight_setrgb_at(25,0,0, j);
          }
        }
        break;
    }
  return state;
}
