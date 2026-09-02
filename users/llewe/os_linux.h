#pragma once

// Linux implementation of the OS-dependent keys, used by the silakka54 "llewe"
// keymap (see llewe_common.h in the keymap folder) when the keyboard runs in
// Linux mode (mac_mode == false).
//
// Everything OS-specific for this variant lives in this file: the symbol
// handlers, the Home/End/PrtSc aliases, the thumb modifier keys and the arrow
// string output. The matching macOS implementation is os_mac.h.

// Helpers for the German PC layout AltGr plane (used on Linux). Both expand to
// full statements (including `return false;`) and must only be used inside
// process_record_keymap().

// Shift & AltGr: plain kc1 with shift, AltGr+kc2 without
#define SHIFT_AND_ALGR(kc1, kc2)                                                               \
    if (record->event.pressed) {                                                               \
        timer_timeout();                                                                       \
        if (lshift || rshift) {                                                                \
            unregister_code(KC_LSFT);                                                          \
            register_code(KC_ALGR);                                                            \
            unregister_code(kc2);                                                              \
            register_code(kc2);                                                                \
            unregister_code(kc2);                                                              \
            unregister_code(KC_ALGR);                                                          \
            register_code(KC_LSFT);                                                            \
            add_to_prev(kc2);                                                                  \
        } else {                                                                               \
            register_code(KC_LSFT);                                                            \
            unregister_code(kc1);                                                              \
            register_code(kc1);                                                                \
            add_to_prev(kc1);                                                                  \
        }                                                                                      \
    } else {                                                                                   \
        unregister_code(kc1);                                                                  \
        unregister_code(kc2);                                                                  \
        unreg_prev();                                                                          \
        if (lshift || rshift)                                                                  \
            register_code(KC_LSFT);                                                            \
        else                                                                                   \
            unregister_code(KC_LSFT);                                                          \
    }                                                                                          \
    return false;

// Normal & AltGr: plain kc1, AltGr+kc2 with shift
#define NORMAL_AND_ALGR(kc1, kc2)                                                              \
    if (record->event.pressed) {                                                               \
        timer_timeout();                                                                       \
        if (lshift || rshift) {                                                                \
            unregister_code(KC_LSFT);                                                          \
            register_code(KC_ALGR);                                                            \
            unregister_code(kc2);                                                              \
            register_code(kc2);                                                                \
            unregister_code(kc2);                                                              \
            register_code(KC_LSFT);                                                            \
            unregister_code(KC_ALGR);                                                          \
        } else {                                                                               \
            unregister_code(kc1);                                                              \
            register_code(kc1);                                                                \
            unregister_code(kc1);                                                              \
        }                                                                                      \
    }                                                                                          \
    return false;

// Key handlers (one macro per LL_* keycode, called from llewe_common.h).
// Each macro expands to the full case body, including `return false;`.

// ` | ~  (DE_CIRC = KC_GRV holds ^ on the German layout)
#define LL_GRV_LINUX() SHIFT_AND_ALGR(KC_EQL, DE_PLUS)
// 2 | @  (@ is AltGr+Q)
#define LL_2_LINUX() NORMAL_AND_ALGR(DE_2, DE_Q)
// 6 | ^
#define LL_6_LINUX() SHIFT_NO(DE_6, DE_CIRC)
// [ | {  (DE_LBRC is AltGr+8)
#define LL_LBRC_LINUX() SHIFT_ALGR(DE_8, DE_7)
// ] | }  (DE_RBRC is AltGr+9)
#define LL_RBRC_LINUX() SHIFT_ALGR(DE_9, DE_0)
// \ | |  (DE_BSLS is AltGr+ß)
#define LL_BSLS_LINUX() SHIFT_ALGR(DE_SS, DE_LABK)
// ° (on DE_CIRC, i.e. Shift+KC_GRV)
#define LL_SPECIAL_LINUX() SHIFT_NORM(KC_KP_0, DE_CIRC)
// , | <  (< is KC_NUBS unshifted on the German layout)
#define LL_COMM_LINUX() SHIFT_NO(DE_COMM, DE_LABK)
// . | >  (> is Shift+KC_NUBS)
#define LL_DOT_LINUX() SHIFT_NORM(DE_DOT, DE_LABK)

// Home / End / PrtSc are plain keys on Linux.
#define LL_HOME_LINUX_PRESS() register_code(KC_HOME)
#define LL_HOME_LINUX_RELEASE() unregister_code(KC_HOME)
#define LL_END_LINUX_PRESS() register_code(KC_END)
#define LL_END_LINUX_RELEASE() unregister_code(KC_END)
#define LL_PSCR_LINUX_PRESS() register_code(KC_PSCR)
#define LL_PSCR_LINUX_RELEASE() unregister_code(KC_PSCR)

// Thumb modifiers: left inner thumb is GUI, next one is Alt.
#define LL_T1_LINUX() KC_LGUI
#define LL_T2_LINUX() KC_LALT

// Arrow strings. SEND_STRING uses sendstring_german.h, the correct LUT for the
// German layout on Linux (< and > live on KC_NUBS).
#define LL_AR_L_LINUX_SHIFTED() SEND_STRING("<-")
#define LL_AR_L_LINUX() SEND_STRING("<=")
#define LL_AR_R_LINUX_SHIFTED() SEND_STRING("->")
#define LL_AR_R_LINUX() SEND_STRING("=>")
