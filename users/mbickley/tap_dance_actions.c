// Register the double tap dances:
qk_tap_dance_action_t tap_dance_actions[] = {
//Double Taps
    [EQL_PLUS]  = ACTION_TAP_DANCE_DOUBLE(KC_EQL,  KC_PLUS),
    [SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TCK_QUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),

//Fancy Taps
    [KTNA_RENDER]  = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, katana_render_finished,       katana_render_reset,      DANCING_TERM), // Requires tap_dance_katana
    [C_P_C]  = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, copy_paste_cut_finished,       copy_paste_cut_reset,      DANCING_TERM), // Requires copy_paste_cut

};