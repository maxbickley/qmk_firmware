#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _SHOTS 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  SHOTS,
};
//Max's Custom Keycodes
#define KC_WCLT RGUI(LCTL(KC_LEFT))
#define KC_WCRT RGUI(LCTL(KC_RGHT))
#define ENLW LT(_LOWER,KC_ENT) //Enter when pressed, LOWER when held.
#define SPRS LT(_RAISE,KC_SPACE) //Space when pressed, RAISE when held.
#define SPLW LT(_LOWER,KC_SPACE) //Space when pressed, LOWER when held.
#define GUIDT GUI_T(KC_DOT) // Period when pressed, GUI when held. 
#define GUITK GUI_T(KC_GRV) // Grave when pressed, ` when pressed.
#define ALTSL LALT_T(KC_SLSH) // Slash wheh presed, alt when held.
#define KC_SFTK LSFT_T(KC_GRV) //` when pressed, Shift when held.
#define KC_SFMN RSFT_T(KC_MINS) //- when pressed, Shift when held.
#define KC_GUTK GUI_T(KC_GRV) //` when pressed, GUI when held.
#define KC_CTUN LCTL_T(KC_UNDS) // _ when pressed, CTL when held.
#define KC_CTQU LCTL_T(KC_QUOT) // ' when pressed, CTL when held.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   ~  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BKSPC|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  BKSPC|    | ENTER |------+------+------+------+------+------|
 * | SHIFT|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |SHIFT |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCLT | LALT |  CMD | /SPACE  /       \SPACE \  |  CMD | LALT | SHOTS|
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_ESC,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_SFTK,   KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,KC_BSPC,   KC_ENTER,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFMN, \
                           KC_CTUN,ALTSL ,GUIDT ,SPLW,          SPRS, GUITK,   KC_RALT, KC_RCTL \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VULU |  [   |  UP  |  ]   | PGUP | HOME |                    |      |  UP  |      | PRSC |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VOLD | LEFT | DOWN | RIGHT| PGDN | END  |-------.    ,-------| LEFT | DOWN | RIGHT|INSERT|   )  |   -  |
 * |------+------+------+------+------+------| ENTER |    |  TAB  |------+------+------+------+------+------|
 * |MUT/SF|   -  |  =   |   *  |   /  | BKSPC|-------|    |-------|      |      |      |      |   |  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCLT | LALT |  CMD | /SPACE  /       \SPACE \  |  CMD | LALT | RCTL |
47 *                 |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  QK_BOOT, KC_F1  , KC_F2  , KC_F3   , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
  KC_VOLU, KC_LBRC, KC_UP  , KC_LBRC , KC_PGUP, KC_HOME,                   _______, KC_UP  , _______, KC_PSCR, _______, KC_DEL, \
  KC_VOLD, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_END ,                   KC_LEFT,KC_DOWN, KC_RIGHT, KC_INS , _______, _______, \
  KC_LSFT, KC_MINS, KC_EQL , KC_ASTR,  KC_SLSH, KC_BSPC,KC_ENTER,  KC_TAB, _______, _______, _______, _______, KC_BSLS, _______, \
                             _______,  _______, _______, _______,   MO(SHOTS), _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VULU |  [   |  UP  |  ]   | PGUP | HOME |                    | DSKLT|  UP  | DSKRG| PRSC |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VOLD | LEFT | DOWN | RIGHT| PGDN | END  |-------.    ,-------| LEFT | DOWN | RIGHT|INSERT|   )  |   -  |
 * |------+------+------+------+------+------|  TAB  |    | ENTER |------+------+------+------+------+------|
 * |MUT/SF|   -  |  =   |   *  |   /  | BKSPC|-------|    |-------|      |      |      |      |   |  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCLT | LALT |  CMD | /SPACE  /       \SPACE \  |  CMD | LALT | RCLT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  KC_MUTE, KC_F1  , KC_F2  , KC_F3   , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
  KC_VOLU, KC_LBRC, KC_UP  , KC_LBRC , KC_PGUP, KC_HOME,                   KC_WCLT, KC_UP  , KC_WCRT, KC_PSCR, _______, KC_DEL, \
  KC_VOLD, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_END ,                   KC_LEFT,KC_DOWN, KC_RIGHT, KC_INS , _______, _______, \
  KC_LSFT, KC_MINS, KC_EQL , KC_ASTR,  KC_SLSH, KC_BSPC,KC_TAB,  KC_ENTER, _______, _______, _______, _______, KC_BSLS, _______, \
                             _______,  _______, _______, MO(SHOTS),    _______, _______, _______, _______\
),
/* SHOTS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |BOOT |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_SHOTS] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  QK_BOOT, XXXXXXX, KC_B, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _SHOTS);
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}

