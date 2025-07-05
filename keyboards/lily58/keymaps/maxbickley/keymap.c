#include QMK_KEYBOARD_H
#include "oled_driver.h"
#include "raw_hid.h"

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
 * | BOOT |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VULU |  [   |  UP  |  ]   | PGUP | HOME |                    |      |  UP  |      | PRSC |      | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | VOLD | LEFT | DOWN | RIGHT| PGDN | END  |-------.    ,-------| LEFT | DOWN | RIGHT|INSERT|   )  |   -  |
 * |------+------+------+------+------+------| ENTER |    |  TAB  |------+------+------+------+------+------|
 * |MUT/SF|   -  |  =   |   *  |   /  | BKSPC|-------|    |-------|      |      |      |      |   |  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCLT | LALT |  CMD | /SPACE  /       \SPACE \  |  CMD | LALT |CPTOGG|
47 *                 |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  QK_BOOT, KC_F1  , KC_F2  , KC_F3   , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
  KC_VOLU, KC_LBRC, KC_UP  , KC_RBRC , KC_PGUP, KC_HOME,                   _______, KC_UP  , _______, KC_PSCR, _______, KC_DEL, \
  KC_VOLD, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_END ,                   KC_LEFT,KC_DOWN, KC_RIGHT, KC_INS , _______, _______, \
  KC_LSFT, KC_MINS, KC_EQL , KC_ASTR,  KC_SLSH, KC_BSPC,KC_ENTER,  KC_TAB, _______, _______, _______, _______, KC_BSLS, _______, \
                             _______,  _______, _______, _______,   MO(SHOTS), _______, _______, CW_TOGG\
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
 *                   |CPTOGG| LALT |  CMD | /SPACE  /       \SPACE \  |  CMD | LALT | RCLT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  KC_MUTE, KC_F1  , KC_F2  , KC_F3   , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
  KC_VOLU, KC_LBRC, KC_UP  , KC_RBRC , KC_PGUP, KC_HOME,                   KC_WCLT, KC_UP  , KC_WCRT, KC_PSCR, _______, KC_DEL, \
  KC_VOLD, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, KC_END ,                   KC_LEFT,KC_DOWN, KC_RIGHT, KC_INS , _______, _______, \
  KC_LSFT, KC_MINS, KC_EQL , KC_ASTR,  KC_SLSH, KC_BSPC,KC_TAB,  KC_ENTER, _______, _______, _______, _______, KC_BSLS, _______, \
                             CW_TOGG,  _______, _______, MO(SHOTS),    _______, _______, _______, _______\
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

// Global buffer for storing received system stats
static uint8_t received_data[32];
static bool data_received = false;

// Custom function to fill rectangle (since oled_fill_rect doesn't exist)
void custom_oled_fill_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    for (uint8_t i = y; i < y + height && i < 32; i++) {
        for (uint8_t j = x; j < x + width && j < 128; j++) {
            oled_write_pixel(j, i, on);
        }
    }
}
// NVIDIA logo byte array (paste your generated code here)
static const char PROGMEM nvidia_logo[] = {
    // PASTE YOUR GENERATED BYTE ARRAY HERE FROM image2cpp
    // It will look something like:
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
        0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xc0, 0xe0, 0xf0, 0x70, 0x38, 0x1c, 0x8c, 0xc6, 0xe6, 0x66, 0x22, 0x33, 0x33, 0xcc, 0x8c,
        0x0c, 0x1c, 0x19, 0x39, 0xf1, 0xe3, 0xe3, 0x07, 0x0f, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0x1e, 0x1e,
        0x1e, 0x1e, 0x1e, 0x3c, 0x7c, 0xfc, 0xfc, 0xf8, 0xe0, 0x00, 0x0e, 0x7e, 0xfe, 0xfe, 0xfc, 0xe0,
        0x00, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0xfe, 0xfe, 0x3e, 0x06, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0xfe,
        0x00, 0x00, 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0x1e, 0x1e, 0x1e, 0x1e, 0x1c, 0x3c, 0xfc, 0xfc, 0xf8,
        0xf0, 0x80, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8,
        0xfe, 0xfe, 0x3e, 0x3e, 0xfe, 0xfe, 0xf8, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x01, 0x07, 0x0f, 0x1f, 0x3c, 0x70, 0xe1, 0xc7, 0xcf, 0x9c, 0x98, 0x30, 0x30, 0xdf, 0xdf,
        0xdf, 0xce, 0xce, 0x67, 0x63, 0x71, 0x38, 0x38, 0x1c, 0x0e, 0x8f, 0x87, 0x83, 0xc3, 0xc3, 0xe7,
        0xef, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0x1f, 0xff, 0xff,
        0xfe, 0xf0, 0xf0, 0xfe, 0xff, 0xff, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf0, 0xff, 0xff, 0xff,
        0x7f, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0xff, 0xff, 0x3f,
        0x3f, 0x30, 0x30, 0x30, 0x31, 0x3f, 0x7f, 0xff, 0xff, 0xf8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x1c, 0x1c,
        0x1c, 0x1c, 0x1c, 0x1e, 0x1e, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f,
        0x1f, 0x1f, 0x1f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Function to render the NVIDIA logo
static void render_nvidia_logo(void) {
    oled_write_raw_P(nvidia_logo, sizeof(nvidia_logo));
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
// --- OLED rotation: flip right half ---
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // Flip right OLED 180 degrees
    }
    return rotation;
}

// --- Left OLED (master): Layer visualization (debugged version) ---
bool left_oled_task(void) {
    uint8_t layer = get_highest_layer(layer_state);
    const uint8_t screen_width = 128;
    const uint8_t screen_height = 32;
    const uint8_t split_x = screen_width / 2;  // 64 pixels

    oled_clear();  // This sets everything to black

    switch (layer) {
        case _RAISE:
            // Physical top half = coordinate right half (x=64 to x=127)
            custom_oled_fill_rect(split_x, 0, split_x, screen_height, true);
            break;

        case _LOWER:
            // Physical bottom half = coordinate left half (x=0 to x=63)
            custom_oled_fill_rect(0, 0, split_x, screen_height, true);
            break;

        default:  // _QWERTY or any other layer
            // Entire display stays black (already cleared)
            break;
    }
    return false;
}

// --- Right OLED (slave): Display NVIDIA logo ---
bool right_oled_task(void) {
    oled_clear();
    render_nvidia_logo();
    return false;
}

// --- Main OLED task user ---
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        left_oled_task();   // Layer visualization
    } else {
        right_oled_task();  // System stats
    }
    return false;
}
#endif

// --- Raw HID receive handler: proper callback implementation ---
#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (!is_keyboard_master()) {
        // On slave side, store received data for display
        memcpy(received_data, data, length);
        data_received = true;
    } else {
        // On master side, forward data to slave
        raw_hid_send(data, length);
    }
}
#endif

// --- Process record user (removed keylog call) ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Your other key processing code here
    return true;
}
