    
#include QMK_KEYBOARD_H
//Unicode

void eeconfig_init_user(void) {
    set_unicode_input_mode(UC_LNX);
}
enum unicode_names {
    THINK,
    THMUP,
    FPALM,
    PPOPP,
    HUNDP
};

const uint32_t PROGMEM unicode_map[] = {
    [THINK]  = 0x1F914  ,  // 🤔🤔🤔
    [THMUP] = 0x1F44D,  // 👍👍👍
    [FPALM]  = 0x1F926 , // 🤦🤦🤦
    [PPOPP] = 0x1F389 , // 🎉🎉🎉
    [HUNDP] = 0x1F4AF , // 💯💯💯
};
//Setup OS specific input modes.
#define KC_MWC UC_M_WC
#define KC_LNX UC_LNX
//Redifine keycodes for nice clean maps.
#define KC_FPALM X(FPALM)
#define KC_THINK X(THINK)
#define KC_THMUP X(THMUP)
#define KC_PPOPP X(PPOPP)
#define KC_HUNDP X(HUNDP)