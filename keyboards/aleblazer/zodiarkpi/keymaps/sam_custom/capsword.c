#include "layers.h"
#include "keymap.h"
#include "transactions.h"
#include "rgb_matrix_user.h"

// Idea from:
// https://www.reddit.com/r/olkb/comments/1033bz0/competely_disabling_oleds_with_a_custom_key_in_qmk/
// The sync handler takes care of synchronizing the capsword state across halves
bool is_capsword_enabled = false;

void capsword_sync_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    memcpy(&is_capsword_enabled, in_data, in_buflen);
}

void caps_word_set_user(bool active) {
    is_capsword_enabled = active ? true : false;
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
};

