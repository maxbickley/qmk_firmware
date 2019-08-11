//instanalize an instance of 'tap' for the Copy Paste Cut Tap Dance
static tap copy_paste_cut = { //delcare
    .is_press_action = true,
    .state           = 0
};

void copy_paste_cut_finished(qk_tap_dance_state_t *state, void *user_data) {
    copy_paste_cut.state = current_dance(state);
    switch (copy_paste_cut.state) {
        case SINGLE_TAP: //Copy 
            register_code(KC_LCTL);
            register_code(KC_C);
            break;
        case DOUBLE_TAP: //Paste
            register_code16(KC_LCTL);
            register_code16(KC_V);
            break;
        case TRIPLE_TAP: //Cut
            register_code16(KC_LCTL);
            register_code16(KC_X);
            break;
    }
}

void copy_paste_cut_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (copy_paste_cut.state) {
        case SINGLE_TAP: //Copy
            unregister_code(KC_LCTL);
            unregister_code(KC_C);
            break;
        case DOUBLE_TAP: //Paste
            unregister_code16(KC_LCTL);
            unregister_code16(KC_V);
            break;
        case TRIPLE_TAP: //Cut
            unregister_code16(KC_LCTL);
            unregister_code16(KC_X);
            break;
    }
    copy_paste_cut.state = 0;
}
