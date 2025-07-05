#pragma once

// Remove this line completely:
// #include "config_common.h"  <-- DELETE THIS LINE

// Combo configuration
#define COMBO_COUNT 6           // Number of combos defined in keymap
#define COMBO_TERM 50          // Combo timeout in milliseconds (adjust as needed)

// One-shot modifier configuration
#define ONESHOT_TAP_TOGGLE 3   // Tapping this many times holds the key until tapped again
#define ONESHOT_TIMEOUT 5000   // Time (in ms) before oneshot key is released

// Optional: Extend combo term for modifier keys
#define COMBO_MOD_TERM 200     // Longer timeout when combo includes modifiers

// Tapping term for mod-tap keys (adjust to your preference)
#define TAPPING_TERM 200       // Time window for tap vs hold detection

// Optional: Prevent accidental mod-tap activation
#define TAPPING_FORCE_HOLD
