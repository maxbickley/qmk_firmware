/* ===============================================================================================================
 * TKC Candybar Lefty R3 - Max Bickley's Custom Keymap
 * ===============================================================================================================
 *
 * Copyright 2021 Terry Mathews
 * Adapted from Lily58 keymap by Max
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
 *
 * ===============================================================================================================
 * KEYMAP OVERVIEW:
 * ===============================================================================================================
 *
 * This keymap is designed for programming and productivity with the following features:
 *
 * 🌟 KEY FEATURES:
 * - 4 layers: Base (QWERTY), Function (LL1), Desktop Control (LL2), System (LL3)
 * - Combo keys for missing symbols (brackets, backslash, pipe, etc.)
 * - Programming macros (arrows, logic operators, auto-closing brackets)
 * - Extensive mod-tap functionality for efficient typing
 * - Desktop/window switching shortcuts
 * - RGB lighting controls (if available)
 *
 * 🎯 COMBO KEYS (press simultaneously):
 * - J + K = [    │ K + L = ]    │ M + , = \    │ , + . = |
 * - Q + W = ~    │ W + E = =
 *
 * 🔧 CUSTOM MACROS:
 * - Programming arrows: -> (arrow), => (fat arrow), :: (scope)
 * - Logic operators: && (logic and), || (logic or), != (compare)
 * - Auto-closing: [] {} () (cursor positioned inside)
 *
 * 📱 MOD-TAP KEYS:
 * - Many keys act as modifiers when held, regular keys when tapped
 * - Example: GUI/Tab = Tab when tapped, GUI when held
 *
 * ===============================================================================================================
 */

#include QMK_KEYBOARD_H

// Layer definitions
#define _QWERTY 0
#define _LL1 1
#define _LL2 2
#define _LL3 3

// Custom keycodes
enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LL1,
    LL2,
    LL3,
    // Programming macros
    ARROW,      // ->
    FTARW,  // =>
    SCOPE,      // ::
    COMPARE,    // !=
    LOGIC_AND,  // &&
    LOGIC_OR,   // ||
    BRKTS,   // []
    BRACS,     // {}
    PRENS,     // ()
};

// Combo definitions for missing symbols
enum combos {
    COMBO_LBRC,  // [
    COMBO_RBRC,  // ]
    COMBO_BSLS,  // backslash
    COMBO_PIPE,  // |
    COMBO_TILD,  // ~
    COMBO_EQL,   // =
};

// Key combinations for combos
const uint16_t PROGMEM combo_lbrc[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_bsls[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_tild[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_eql[] = {KC_W, KC_E, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_LBRC] = COMBO(combo_lbrc, KC_LBRC),
    [COMBO_RBRC] = COMBO(combo_rbrc, KC_RBRC),
    [COMBO_BSLS] = COMBO(combo_bsls, KC_BSLS),
    [COMBO_PIPE] = COMBO(combo_pipe, KC_PIPE),
    [COMBO_TILD] = COMBO(combo_tild, KC_TILD),
    [COMBO_EQL] = COMBO(combo_eql, KC_EQL),
};

// Max's Custom Keycodes (from Lily58)
#define KC_WCLT RGUI(LCTL(KC_LEFT))
#define KC_WCRT RGUI(LCTL(KC_RGHT))

// Enhanced Mod Taps from Lily58
#define ENLW LT(_LL1,KC_ENT)       // Enter when pressed, LL1 when held
#define SPRS LT(_LL2,KC_SPACE)     // Space when pressed, LL2 when held
#define SPLW LT(_LL1,KC_SPACE)     // Space when pressed, LL1 when held
#define GUIDT GUI_T(KC_DOT)        // Period when pressed, GUI when held
#define GUITK GUI_T(KC_GRV)        // Grave when pressed, GUI when held
#define ALTSL LALT_T(KC_SLSH)      // Slash when pressed, alt when held
#define KC_SFTK LSFT_T(KC_GRV)     // ` when pressed, Shift when held
#define KC_SFMN RSFT_T(KC_MINS)    // - when pressed, Shift when held
#define KC_GUTK GUI_T(KC_GRV)      // ` when pressed, GUI when held
#define KC_CTUN LCTL_T(KC_UNDS)    // _ when pressed, CTL when held
#define KC_CTQU LCTL_T(KC_QUOT)    // ' when pressed, CTL when held

// Candybar-specific (from candy.c)
#define KC_TBOS GUI_T(KC_TAB)      // Tab when pressed, GUI when held
#define KC_SPL1 LT(_LL1,KC_SPACE)  // Space when pressed, LL1 when held
#define KC_SPL2 LT(_LL2,KC_SPACE)  // Space when pressed, LL2 when held
#define KC_LL3 MO(_LL3)            // Momentary LL3 layer

#define ______ KC_TRNS

// Custom macro processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;
        case FTARW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
        case SCOPE:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            break;
        case COMPARE:
            if (record->event.pressed) {
                SEND_STRING("!=");
            }
            break;
        case LOGIC_AND:
            if (record->event.pressed) {
                SEND_STRING("&&");
            }
            break;
        case LOGIC_OR:
            if (record->event.pressed) {
                SEND_STRING("||");
            }
            break;
        case BRKTS:
            if (record->event.pressed) {
                SEND_STRING("[]" SS_TAP(X_LEFT));
            }
            break;
        case BRACS:
            if (record->event.pressed) {
                SEND_STRING("{}" SS_TAP(X_LEFT));
            }
            break;
        case PRENS:
            if (record->event.pressed) {
                SEND_STRING("()" SS_TAP(X_LEFT));
            }
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ===============================================================================================================
 * Layer 0: QWERTY (Base Layer)
 * ===============================================================================================================
 *
 * Physical Layout:
 * ┌─────────────────────┐ ┌─────────────────────────────────────────────────────────────────────────────┐
 * │    Left Numpad      │ │                    Main Keyboard                                            │
 * └─────────────────────┘ └─────────────────────────────────────────────────────────────────────────────┘
 */
[_QWERTY] = LAYOUT(
//      ┌─────────────────NUMPAD─────────────────┐ ┌─────────────────────────────MAIN KEYBOARD──────────────────────────────────────────────────────────────────────────────────────────────┐
//      │  1   │  2   │  3     │  DEL   │         │ │ Esc   │  Q   │  W   │  E   │  R   │  T   │  Y   │  U   │  I   │  O   │  P    │  \     │ Bksp   │
        KC_1,    KC_2,    KC_3,   KC_DEL,           QK_GESC,KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,   KC_SLSH, KC_BSPC,   \
//      ├────-─┼──────┼──────--┼────────┤         │ ├─---───-─┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼───────┼───────--──────┤
//      │  4   │  5   │  6     │ PgDn   │         │ │GUI/Tab  │  A   │  S   │  D   │  F   │  G   │  H   │  J   │  K   │  L   │  ;    │    Enter      │
        KC_4,    KC_5,    KC_6,  KC_PGUP,           KC_TBOS,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J, KC_K,  KC_L,  KC_SCLN,     KC_ENT,       \
//      ├──────┼──────┼─────--─┼────────┤         │ ├─────-──────┼──────┼──────┼──────┼──────┼──────┼──────┼─────┼─────--─┼───────-┼───────---┼──────┤
//      │  7   │  8   │  9     │ PgDn   │         │ │     Sft/   │  Z   │  X   │  C   │  V   │  B   │  N   │  M  │   ,    │GUI/.   │Alt//    │Sft/-  │
        KC_7,    KC_8,    KC_9,  KC_PGDN,           KC_SFMN,      KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M, KC_COMM, GUIDT,   ALTSL,    KC_SFMN, \
//      ├──────┼──────┼──────--┼──-─────┤         │ ├──-───--──────┼──--────┼─-─────-──────-────┼────────────────┼─────--─┼─────-──┼────-─--─┼------─┼
//      │ Enter│   0  │    .   │  LL3   │         │ │Ctl/' │  Alt  │ GUI/ ` │    L1/Spc         │    L2/Spc      │ GUI    │   Alt  │ Ctl/_   │ Rght  │
        KC_ENT,  KC_P0, KC_PDOT,KC_LL3,             KC_CTQU,KC_LALT,KC_GUTK,    KC_SPL1,KC_NO,      KC_SPL2,      KC_RGUI, KC_RALT, KC_CTUN, KC_RGHT),
//      └──────┴──────┴────-──┴──--───-─┘         │ └──────┴───────┴───-────┴───────------──────┘----─────────--─┴───────-┴───────-┴─────---─┴──────-┘
//                                                │
//                                                └─ Main keyboard area with standard layout

/* ===============================================================================================================
 * Layer 1: LL1 (Function Layer - Numbers, Symbols, Navigation)
 * ===============================================================================================================
 *
 * This layer provides:
 * - Number row (1-0) and symbols
 * - Arrow key navigation
 * - Function keys (F2, F5)
 * - Programming symbols: [], {}, (), ->, =>, ::, !=
 * - Home/End navigation
 */
[_LL1] = LAYOUT(
//      ┌─────────────────NUMPAD────────┐         ┌──-─────────-───────────-──────-─MAIN KEYBOARD───────────────────────────────────────────────────--───--─┐
//      │ ---  │ ---  │ ---    │   Mute │         │ │   `  │   [   │  ↑    │  ]     │  PgUp  │ Home   │  6   │  7   │  8   │  9   │  0    │  :      │  Del  │
        _______, _______, _______, KC_MUTE,         KC_GRV,KC_LBRC, KC_UP, KC_RBRC,  KC_PGUP,KC_HOME, KC_6,  KC_7,  KC_8,  KC_9,  KC_0,   KC_COLN,  KC_DEL,   \
//      ├──────┼──────┼────────┼────────┤         │ ├─────-──┼──-────┼──────-┼──────--┼─────-─┼─────-─┼──-────┼────-──┼───-───┼────-──┼───────┼───-────--───┤
//      │ ---  │ ---  │ ---    │  VolUp │         │ │   \    │   ←   │  ↓    │  →     │  PgDn │ End   │ ---   │  ---  │  ---  │  ---  │  "    │     Enter   │
        _______, _______, _______, KC_VOLU,         KC_BSLS, KC_LEFT,KC_DOWN,KC_RIGHT,KC_PGDN,KC_END, _______,_______,_______,_______,KC_DQUO,     KC_ENT,    \
//      ├──────┼──────┼────────┼────────┤         │ ├───────--─--┼───-───┼─────-─┼──────--┼─────-─┼────-─┼─────-─┼───--─┼──────┼──────┼───────┼───-───-─────┤
//      │ ---  │ ---  │ ---    │  VolDn │         │ │  MUT/SF    |   -   |  =    |   *    |   /   │ Tab  │ ---   │  []  │  {}  │  ()  │ ---   │        ---  │
        _______, _______, _______, KC_VOLD,         KC_LSFT,     KC_MINS,KC_EQL, KC_ASTR, KC_SLSH,KC_TAB,_______,BRKTS, BRACS, PRENS, _______,_______,        \
//      ├──────┼──────┼──────--┼──-─────┤         │ ├──-───--──────┼──--────┼─-─────-──────----────┼──----──────────────┼────--─┼─────-─-─┼────-─--─┼------─┼
//      │ Enter│   0  │    .   │  LL3   │         │ │Ctl/' │  Alt  │ GUI/ ` │    L1/Spc            │        L2/Spc      │   ->  │   =>    │   ::    │  !=   │
        KC_ENT, KC_P0, KC_PDOT,KC_LL3,              KC_CTQU,KC_LALT,KC_GUTK,    _______,KC_NO,      MO(_LL3),           ARROW,  FTARW,    SCOPE,    COMPARE),
//      └──────┴──────┴────-──┴──--───-─┘         │ └──────┴───────┴───-────┴───────------─────---─┘----──----───────--─┴──────-┴───────--┴─────---─┴──────-┘
//                                                │
//                                                └─ Programming macros and navigation

/* ===============================================================================================================
 * Layer 2: LL2 (Desktop Control Layer - Window Management & Logic Ops)
 * ===============================================================================================================
 *
 * This layer provides:
 * - Keypad numbers (1-9, 0) on the left side
 * - Desktop/window switching (Cmd+Ctrl+Left/Right)
 * - Arrow key navigation
 * - Logic operators: && (AND), || (OR)
 * - Caps Word toggle
 */
[_LL2] = LAYOUT(
//      ┌───────────────NUMPAD─────────┐         ┌─────────────────────────----------────MAIN KEYBOARD─────────────────────────────────────────────────────┐
//      │ F1   │   F2  │  F3  │  Mute  │         │ │  ---   │  1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │  0    │  :    │  Del  │
        KC_F1,  KC_F2,  KC_F3,  KC_MUTE,           _______, KC_1,   KC_2,  KC_3,   KC_4,   KC_5,   KC_6,  KC_7,   KC_8,   KC_9,   KC_0,    KC_COLN,KC_DEL,  \
//      ├──────┼───────┼──────┼────────┤         │ ├────────┼──────┼─-─────┼─-─────┼──-────┼──-────┼──-────┼──-────┼─-─────┼──-────┼───────┼───────┼───────┤
//      │   F4 │   F5  │  F6  │  VolUp │         │ │  ---   │DeskL │  ↑    │ DeskR │  ---  │  ---  │  ---  │  ---  │  ---  │  ---  │  "    │   Enter       │
        KC_F4,  KC_F5,  KC_F6,  KC_VOLU,           _______, KC_WCLT, KC_UP,KC_WCRT,_______,_______,_______,_______,_______,_______,KC_DQUO, KC_ENT,         \
//      ├──────┼───────┼──────┼────────┤         │ ├───────┼──-────┼───-───┼──-────┼───-───┼──────-┼─-─────┼─-─────┼-──────┼-──────┼───────┼───────┼───────┤
//      │ F7   │   F8  │  F9  │  VolDn │         │ │  ---  │ ---   │  ←    │  ↓    │  →    │ ---   │ ---   │ ---   │  &&   │  ||   │  ---  │   \   │ ---   │
        KC_F7,  KC_F8,  KC_F9,  KC_VOLD,           _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
//      ├──────┼─────-─┼──────-┼──-────┤         │ ├──--───┼--──────┼──--────┼─-─────-──-────-────┼────-────--────────┼───-----─┼───-──-──┼─────--─┼------─┼
//      │ ---  │  F10  │ F11  │  F12   │         │ │Ctl/'  │  Alt   │ GUI/ ` │     L1/Spc         │      L2/Spc       │    ->   │   =>    │   ::   │  !=   │
        _______,KC_F10, KC_F11, KC_F12,            CW_TOGG,_______, _______,     MO(_LL3),         _______,          _______,  _______,  _______, _______),
//      └──────┴───────┴──────┴──-─────┘         │ └──────┴─────--──┴───-────┴──────-------------─┘─────-─--───────-──┴────---──┴───--────┴───-----┴-─--───┘
//                                                │
//                                                └─ Desktop switching: DeskL/DeskR = Desktop Left/Right

/* ===============================================================================================================
 * Layer 3: LL3 (System Control Layer - RGB, Audio, Reset)
 * ===============================================================================================================
 *
 * This layer provides:
 * - RGB lighting controls (if available)
 * - Audio volume controls
 * - System reset/bootloader access
 * - Desktop switching shortcuts
 * - This is the "meta" layer for system-level functions
 */
[_LL3] = LAYOUT(
//      ┌────────────NUMPAD─--──-────-─┐         ┌───────────────────────--──────MAIN KEYBOARD─────────────────────────────────────────────────────────────┐
//      │DeskL │  ↑    │DeskR │  End   │         │ │ RESET  │  1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │  0    │  :    │  Del  │
        KC_WCLT, KC_UP,KC_WCRT, KC_END,           QK_BOOT, KC_1,   KC_2,  KC_3,   KC_4,   KC_5,   KC_6,  KC_7,   KC_8,   KC_9,   KC_0,    KC_COLN,KC_DEL,  \
//      ├──────┼───────┼──────┼────────┤         │ ├────────┼──────┼─-─────┼─-─────┼──-────┼──-────┼──-────┼──-────┼─-─────┼──-────┼───────┼───────┼───────┤
//      │  ←   │  ↓    │  →   │  VolUp │         │ │  ---   │ ---  │ ---  │ ---  │ ---  │ ---  │ ---  │ ---  │ ---  │ ---  │ ---   │ ---   │       │
        KC_LEFT,KC_DOWN,KC_RGHT,KC_PGUP,           _______, KC_WCLT, KC_UP,KC_WCRT,_______,_______,_______,_______,_______,_______,KC_DQUO, KC_ENT,         \
//      ├──────┼───────┼──────┼────────┤         │ ├───────┼──-────┼───-───┼──-────┼───-───┼──────-┼─-─────┼─-─────┼-──────┼-──────┼───────┼───────┼───────┤
//      │ F7   │   F8  │  F9  │  VolDn │         │ │  ---  │ ---   │  ←    │  ↓    │  →    │ ---   │ ---   │ ---   │  &&   │  ||   │  ---  │   \   │ ---   │
        KC_F7,  KC_F8,  KC_F9,  KC_PGDN,           _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______, \
//      ├──────┼─────-─┼──────-┼──-────┤         │ ├──--───┼--──────┼──--────┼─-─────-──-────-────┼────-────--────────┼───-----─┼───-──-──┼─────--─┼------─┼
//      │ ---  │  F10  │ F11   │  ---  │         │ │Ctl/'  │  Alt   │ GUI/ ` │     L1/Spc         │      L2/Spc       │    ->   │   =>    │   ::   │  !=   │
        _______,KC_F10, KC_F11, _______,            CW_TOGG,_______, _______,     MO(_LL3),         _______,          _______,  _______,  _______, _______),
//      └──────┴───────┴─────-─┴──-────┘         │ └──────┴─────--──┴───-────┴──────-------------─┘─────-─--───────-──┴────---──┴───--────┴───-----┴-─--───┘
//                                                │
//                                                └─ RGB: H=Hue, S=Saturation, V=Value/Brightness, +/- = increase/decrease
};
