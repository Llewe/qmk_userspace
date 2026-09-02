#pragma once

// macOS implementation of the OS-dependent keys, used by llewe_common.h when
// the keyboard runs in mac mode (mac_mode == true).
//
// Everything OS-specific for this variant lives in this file: the Option/AltGr
// plane, dead-key escapes, the Cmd-based Home/End/PrtSc, the thumb modifier
// keys and the arrow string output. The matching Linux implementation
// is os_linux.h.
//
// IMPORTANT: the host must use the macOS input source "German" (Deutsch), NOT
// "German - Standard" (Deutsch Standard). The latter puts @ { } etc. on the
// PC AltGr positions (Opt+Q, Opt+7, Opt+0 ...) which this file does not
// follow. macOS additionally classifies the ortholinear board as ANSI, so on
// this layout < and > live on KC_GRV (the key left of 1) and ^ and ° on
// KC_NUBS - unlike the Linux German layout where they are swapped.

// Helper macros for the macOS Option plane. KC_ALGR (right alt) is used as
// Option so the left thumb Option key stays free for normal shortcuts. All
// expand to full statements (including `return false;`) and must only be used
// inside process_record_keymap().

// Option + kc, ignoring the physical shift state
#define MAC_OPT(kc)                                                                             \
    unregister_code(KC_LSFT);                                                                   \
    register_code(KC_ALGR);                                                                     \
    unregister_code(kc);                                                                        \
    register_code(kc);                                                                          \
    unregister_code(kc);                                                                        \
    unregister_code(KC_ALGR);

// Shift + Option + kc
#define MAC_SOPT(kc)                                                                            \
    register_code(KC_LSFT);                                                                     \
    register_code(KC_ALGR);                                                                     \
    unregister_code(kc);                                                                        \
    register_code(kc);                                                                          \
    unregister_code(kc);                                                                        \
    unregister_code(KC_ALGR);                                                                   \
    unregister_code(KC_LSFT);

// Shift + kc, ignoring the physical shift state
#define MAC_SFT(kc)                                                                             \
    register_code(KC_LSFT);                                                                     \
    unregister_code(kc);                                                                        \
    register_code(kc);                                                                          \
    unregister_code(kc);                                                                        \
    unregister_code(KC_LSFT);

// Resolves a dead key by typing a space after it
#define MAC_DEAD_ESC()                                                                          \
    register_code(KC_SPC);                                                                      \
    unregister_code(KC_SPC);

// Puts KC_LSFT back into the state the physical shift keys are in
#define MAC_RESTORE_SFT()                                                                       \
    if (lshift || rshift)                                                                       \
        register_code(KC_LSFT);                                                                 \
    else                                                                                        \
        unregister_code(KC_LSFT);

// Option+kc1 unshifted, Option+kc2 shifted
#define MAC_OPT_OPT(kc1, kc2)                                                                   \
    if (record->event.pressed) {                                                                \
        timer_timeout();                                                                        \
        if (lshift || rshift) {                                                                 \
            MAC_OPT(kc2)                                                                        \
        } else {                                                                                \
            MAC_OPT(kc1)                                                                        \
        }                                                                                       \
        MAC_RESTORE_SFT()                                                                       \
    }                                                                                           \
    return false;

// Plain kc1 unshifted, Option+kc2 shifted
#define MAC_NORM_OPT(kc1, kc2)                                                                  \
    if (record->event.pressed) {                                                                \
        timer_timeout();                                                                        \
        if (lshift || rshift) {                                                                 \
            MAC_OPT(kc2)                                                                        \
            MAC_RESTORE_SFT()                                                                   \
        } else {                                                                                \
            unregister_code(KC_LSFT);                                                           \
            unregister_code(kc1);                                                               \
            register_code(kc1);                                                                 \
        }                                                                                       \
    } else {                                                                                    \
        unregister_code(kc1);                                                                   \
    }                                                                                           \
    return false;

// Key handlers (one macro per LL_* keycode, called from llewe_common.h).
// Each macro expands to the full case body, including `return false;`.

// ` is Shift+acute, ~ is Opt+N - both are dead keys on macOS and need the
// escape.
#define LL_GRV_MAC()                                                                            \
    if (record->event.pressed) {                                                                \
        timer_timeout();                                                                        \
        if (lshift || rshift) {                                                                 \
            MAC_OPT(DE_N)                                                                       \
        } else {                                                                                \
            MAC_SFT(DE_ACUT)                                                                    \
        }                                                                                       \
        MAC_DEAD_ESC()                                                                          \
        MAC_RESTORE_SFT()                                                                       \
    }                                                                                           \
    return false;

// 2 | @  (@ is Opt+L)
#define LL_2_MAC() MAC_NORM_OPT(DE_2, DE_L)
// 6 | ^  (^ is a dead key on macOS as well and sits on KC_NUBS here)
#define LL_6_MAC()                                                                              \
    if (record->event.pressed) {                                                                \
        timer_timeout();                                                                        \
        unregister_code(KC_LSFT);                                                               \
        if (lshift || rshift) {                                                                 \
            unregister_code(KC_NUBS);                                                           \
            register_code(KC_NUBS);                                                             \
            unregister_code(KC_NUBS);                                                           \
            MAC_DEAD_ESC()                                                                      \
            register_code(KC_LSFT);                                                             \
        } else {                                                                                \
            register_code(DE_6);                                                                \
        }                                                                                       \
    } else {                                                                                    \
        unregister_code(DE_6);                                                                  \
    }                                                                                           \
    return false;

// [ | {  ([ is Opt+5, { is Opt+8)
#define LL_LBRC_MAC() MAC_OPT_OPT(DE_5, DE_8)
// ] | }  (] is Opt+6, } is Opt+9)
#define LL_RBRC_MAC() MAC_OPT_OPT(DE_6, DE_9)
// \ | |  (\ is Shift+Opt+7, | is Opt+7)
#define LL_BSLS_MAC()                                                                           \
    if (record->event.pressed) {                                                                \
        timer_timeout();                                                                        \
        if (lshift || rshift) {                                                                 \
            MAC_OPT(DE_7)                                                                       \
        } else {                                                                                \
            MAC_SOPT(DE_7)                                                                      \
        }                                                                                       \
        MAC_RESTORE_SFT()                                                                       \
    }                                                                                           \
    return false;

// ° (on KC_NUBS, i.e. Shift+KC_NUBS)
#define LL_SPECIAL_MAC() SHIFT_NORM(KC_KP_0, KC_NUBS)
// , | <  (< is KC_GRV unshifted here because macOS sees the board as ANSI)
#define LL_COMM_MAC() SHIFT_NO(DE_COMM, KC_GRV)
// . | >  (> is Shift+KC_GRV)
#define LL_DOT_MAC() SHIFT_NORM(DE_DOT, KC_GRV)

// Home / End / PrtSc are Cmd/Shift+Cmd based on macOS.
#define LL_HOME_MAC_PRESS()                                                                     \
    register_code(KC_LGUI);                                                                     \
    register_code(KC_LEFT);
#define LL_HOME_MAC_RELEASE()                                                                   \
    unregister_code(KC_LGUI);                                                                   \
    unregister_code(KC_LEFT);
#define LL_END_MAC_PRESS()                                                                      \
    register_code(KC_LGUI);                                                                     \
    register_code(KC_RGHT);
#define LL_END_MAC_RELEASE()                                                                    \
    unregister_code(KC_LGUI);                                                                   \
    unregister_code(KC_RGHT);
#define LL_PSCR_MAC_PRESS()                                                                     \
    register_code(KC_LSFT);                                                                     \
    register_code(KC_LGUI);                                                                     \
    register_code(KC_4);
#define LL_PSCR_MAC_RELEASE()                                                                   \
    unregister_code(KC_LSFT);                                                                   \
    unregister_code(KC_LGUI);                                                                   \
    unregister_code(KC_4);

// Thumb modifiers: left inner thumb is Option, next one is Cmd.
#define LL_T1_MAC() KC_LALT
#define LL_T2_MAC() KC_LGUI

// Arrow strings. SEND_STRING is not usable here (its LUT is compiled for the
// Linux German layout), so the characters are emitted with explicit keycodes.
// < and > live on KC_GRV, - on KC_SLSH, = is Shift+0 - identical base key
// positions to Linux, only the angle key differs.

// Tap kc without modifiers
#define MAC_TAP(kc)                                                                             \
    do {                                                                                        \
        register_code(kc);                                                                      \
        unregister_code(kc);                                                                    \
    } while (0)
// Tap kc with left shift
#define MAC_TAP_SHIFTED(kc)                                                                     \
    do {                                                                                        \
        register_code(KC_LSFT);                                                                 \
        register_code(kc);                                                                      \
        unregister_code(kc);                                                                    \
        unregister_code(KC_LSFT);                                                               \
    } while (0)

#define LL_AR_L_MAC_SHIFTED()                                                                   \
    do {                                                                                        \
        MAC_TAP(KC_GRV);                                                                        \
        MAC_TAP(KC_SLSH);                                                                       \
    } while (0) // <-
#define LL_AR_L_MAC()                                                                           \
    do {                                                                                        \
        MAC_TAP(KC_GRV);                                                                        \
        MAC_TAP_SHIFTED(KC_0);                                                                  \
    } while (0) // <=
#define LL_AR_R_MAC_SHIFTED()                                                                   \
    do {                                                                                        \
        MAC_TAP(KC_SLSH);                                                                       \
        MAC_TAP_SHIFTED(KC_GRV);                                                                \
    } while (0) // ->
#define LL_AR_R_MAC()                                                                           \
    do {                                                                                        \
        MAC_TAP_SHIFTED(KC_0);                                                                  \
        MAC_TAP_SHIFTED(KC_GRV);                                                                \
    } while (0) // =>
