#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#include "tap_dance_setup.c" // Setup Tap Dance
#include "tap_dance_enum.c" // Where Tap Dance enums are stored
#include "tap_dance_katana.c" // Katana Tap Dances
#include "tap_dance_copy_paste_cut.c" // Copy Paste Cut Tap Dance
#include "tap_dance_actions.c" // All other Tap Dances
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _RAISE 1
#define _LOWER 2
//#define _ADJUST 3
// Layer Shortcuts
#define SPCRAISE LT(_RAISE, KC_SPACE) // Tap for Space, hold for Raise
#define SPCLOWER LT(_LOWER, KC_SPACE) // Tap for Space, hold for Raise
#define ENRAISE LT(_RAISE, KC_ENT)
/*CleanUp
-----------------------------------------*/
// Mod Taps
//#define CT_MINS LCTL_T(KC_MINS) //Tap for Left Bracket, hold for Control
#define CT_EQL LCTL_T(KC_EQL) //Tap for Right Bracket, hold for GUI/OS
//#define OS_ENT LGUI_T(KC_ENT) //Tap for Enter, hold for GUI/OS
//#define OS_DEL LGUI_T(KC_DEL) //Tap for Delete, hold for GUI/OS
//#define CT_UND LCTL_T(KC_UNDS) //Tap for underscore, hold for Control
#define SFTGRV LSFT_T(KC_GRV) // Tap for grave hold for shift.
#define SFTMIN RSFT_T(KC_MINS)
// Linux Specific Shortcuts
#define TERM LALT(LCTL(LSFT(KC_T))) //Open terminal
#define WSLEFT LCTL(LALT(KC_LEFT)) //Move to workspace left
#define WSUP LCTL(LALT(KC_UP)) //Move to workspace up
#define WSDOWN LCTL(LALT(KC_DOWN)) //Move to workspace down
#define WSRIGHT LCTL(LALT(KC_RIGHT)) //Move to workspace right
//Tap Dance Cleanup
#define C_P_C TD(C_P_C) // Copy Paste Cut Tap Dance
#define TCQT TD(TCK_QUOTE) // Tick/ Quote Tap Dance

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
};

// Shortcut to make keymap more readable

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_MINS ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_ESC  ,                         TERM     ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSLS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                         KC_RBRC  ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,  TCQT  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_RCTL  ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_BSPC ,KC_DOT  ,       KC_PGUP  ,KC_PGDN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_UNDS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_EQL  ,KC_SLSH ,KC_LGUI ,KC_LALT ,     SFTGRV  ,   ENRAISE  ,KC_SPACE,       C_P_C    ,SPCLOWER,     SFTMIN  ,    KC_LEFT  ,KC_DOWN ,KC_UP   ,KC_RGHT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_PLUS ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_INS  ,_______ ,_______ ,_______ ,KC_F2   ,KC_F5   ,KC_LPRN ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_HOME ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_DEL  ,KC_PGDN ,        _______ ,_______ ,_______ ,KC_MPLY ,KC_VOLD ,KC_VOLU ,KC_MUTE ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_ENT  ,KC_ASTR ,KC_SLSH ,KC_PLUS ,     KC_SPACE,    _______ ,KC_ENT  ,        _______ ,_______ ,    _______ ,     WSLEFT  ,WSDOWN  ,WSUP    ,WSRIGHT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                           KC_F6    ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_DEL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CALC ,_______ ,_______ ,_______ ,_______ ,_______ ,RESET   ,                          KC_CAPSLOCK ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_WBAK ,_______ ,KC_UP   ,_______ ,_______ ,_______ ,_______ ,                          KC_RPRN ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_WFWD ,KC_LEFT ,KC_DOWN ,KC_RIGHT,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,KC_MPLY ,KC_VOLD ,KC_VOLU ,KC_MUTE ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,KC_LBRC ,KC_RBRC ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     WSLEFT  ,WSDOWN  ,WSUP    ,WSRIGHT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  
};
