
//instanalize an instance of 'tap' for the Katana Preview/Live Render Tap Dance.
static tap katana_render = { //delcare
    .is_press_action = true,
    .state           = 0
};

void katana_render_finished(qk_tap_dance_state_t *state, void *user_data) {
    katana_render.state = current_dance(state);_
    switch (katana_render.state) {
        case SINGLE_TAP: //Live Render Hotkey
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_P);
            break;

        case DOUBLE_TAP: //Preview Render Hotkey
            register_code16(KC_LCTL);
            register_code16(KC_P);
            break;
    }
}

void katana_render_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (katana_render.state) {
        case SINGLE_TAP: //Live Render Hotkey
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            register_code(KC_P);
            break;

        case DOUBLE_TAP: //Preview Render Hotkey
            register_code16(KC_LCTL);
            register_code16(KC_P);
            break;
    }
    katana_render.state = 0;
}