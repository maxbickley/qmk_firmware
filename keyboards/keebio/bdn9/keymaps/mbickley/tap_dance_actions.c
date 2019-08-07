// Register the double tap dances:
qk_tap_dance_action_t tap_dance_actions[] = {
    [EQL_PLUS]  = ACTION_TAP_DANCE_DOUBLE(KC_EQL,  KC_PLUS),
    [SCLN_COLN] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, scln_coln_finished,       scln_coln_reset,      DANCING_TERM), // Requires scln_coln
    [KTNA_RENDER]  = ACTION_TAP_DANCE_DOUBLE(LCTL(LSFT(KC_P)), LCTL(KC_P)), // Tap once for Live Render, twice for Preview Render
};