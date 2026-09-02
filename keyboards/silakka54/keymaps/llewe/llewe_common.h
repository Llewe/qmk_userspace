#pragma once

// Keymap implementation for silakka54 "llewe", the non-shared half of the
// keymap. Lives next to keymap.c in the keymap folder because it is used by
// this keymap only; the userspace (users/llewe) holds only code shared with
// the crkbd keymap plus the OS variant implementations os_linux.h and
// os_mac.h.
//
// One firmware supports the Linux and the macOS variant; the active
// variant is a runtime state (mac_mode) and can be toggled by pressing all six
// thumb keys at once. The OS-dependent implementation lives in
// os_linux.h / os_mac.h, so changes for one system stay in one file.
// The actual keymaps (layer arrays) are in keymap.c.
//
// macOS note: the input source must be "German" (Deutsch), NOT
// "German - Standard" (Deutsch Standard), and macOS classifies the
// ortholinear board as ANSI (see os_mac.h).

#include "eeconfig.h"
#include "unicode.h"
#include "os_linux.h"
#include "os_mac.h"

bool mocking_case_active = false;
bool mocking_case_shift_up = false;

// OS variant state. false = Linux, true = macOS. Persisted in bit 0
// of the user EEPROM byte, so each keyboard half remembers the OS it is used
// with across reboots.
bool mac_mode = false;

enum layers{
    // All german layers
    AG1, //ANSI_US_GER
    AG2, //ANSI_US_GER
    GNU, // German number
    GSK, // German special keys & fn
    ANSI_US_GER_4,
    // All english layers
    ANSI_US,

    // Other
    OTH,

    DEFAULT1,
    DEFAULT2
};


enum custom_keycodes {
    LL_LSFT = NEW_KEY_SAFE_RANGE,
    LL_RSFT,
    LL_GRV, //`|~
    LL_2, //2|@
    LL_6, //6|^
    LL_LBRC, //[|{
    LL_RBRC, //]|}
    LL_QUOT, //'|"
    LL_BSLS, //\||
    LL_COMM, //,|<
    LL_DOT, //.|>
    LL_HOME, // line start (Linux) / Cmd+Left (mac)
    LL_END, // line end (Linux) / Cmd+Right (mac)
    LL_PSCR, // screenshot (Linux) / Shift+Cmd+4 (mac)
    LL_T1, // left inner thumb (GUI Linux / Option mac)
    LL_T2, // left middle thumb (Alt Linux / Cmd mac)
    LL_SPECIAL, //'|"
    LL_AR_L, //<= | <-
    LL_AR_R, // =>| ->

    LL_SM_1, //¯\_(ツ)_/¯
    LL_SM_2, //༼ つ ◕_◕ ༽つ
    LL_SM_A, // type ucis name
    LL_T_MO, // toggle mocking case
    LL_OS // toggle Linux vs macOS variant, fired by the six-thumb chord
};

const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop", 0x1F4A9),                // 💩
    UCIS_SYM("rofl", 0x1F923),                 // 🤣
    UCIS_SYM("lol", 0x1F602),
    UCIS_SYM("melting", 0x1FAE0),
    UCIS_SYM("cuba", 0x1F1E8, 0x1F1FA),       // 🇨🇺
    UCIS_SYM("look", 0x0CA0, 0x005F, 0x0CA0),  // ಠ_ಠ
    UCIS_SYM("wink", 0x1F609),
    UCIS_SYM("winkt", 0x1F61C),
    UCIS_SYM("y", 0x1F44D),
    UCIS_SYM("n", 0x1F44E),
    UCIS_SYM("clown", 0x1F921)
);

// Pressing all six thumb keys at once toggles the OS variant. The thumb keys
// are combo members, so while the chord is incomplete their events are
// buffered and a completed chord never types space/enter, never holds
// GUI/Alt and never engages the momentary layers.
enum silakka_combos {
    CB_OS_TOGGLE,
};

const uint16_t PROGMEM os_toggle_combo[] = {LL_T1, LL_T2, KC_SPC, KC_ENT, MO(GNU), MO(GSK), COMBO_END};

combo_t key_combos[] = {
    [CB_OS_TOGGLE] = COMBO(os_toggle_combo, LL_OS),
};

// Toggle between the Linux and macOS variants and keep the Unicode
// input mode in sync.
void os_toggle(void) {
    mac_mode = !mac_mode;
    uint32_t user = eeconfig_read_user();
    eeconfig_update_user(mac_mode ? (user | 1) : (user & ~1u));
    set_unicode_input_mode(mac_mode ? UNICODE_MODE_MACOS : UNICODE_MODE_LINUX);
}

void keyboard_post_init_user(void) {
    uint32_t user = eeconfig_read_user();
    mac_mode = (user == 1);
    if (user != 0 && user != 1) {
        eeconfig_update_user(0);
    }
    set_unicode_input_mode(mac_mode ? UNICODE_MODE_MACOS : UNICODE_MODE_LINUX);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LL_LSFT:
    if(record->event.pressed) {
      lshiftp = true;
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      lshift = true;
    } else {
        unreg_prev();
      if (!rshift)
        unregister_code(KC_LSFT);
      lshift = false;
    }
    return false;
  case LL_RSFT:
    if(record->event.pressed) {
      rshiftp = true;
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      rshift = true;
    } else {
      unreg_prev();
      if (!lshift)
        unregister_code(KC_LSFT);
      rshift = false;
    }
    return false;

  case LL_GRV: //`|~
    if (mac_mode) { LL_GRV_MAC(); } else { LL_GRV_LINUX(); }
  case LL_2: //2|@
    if (mac_mode) { LL_2_MAC(); } else { LL_2_LINUX(); }
  case LL_6: //6|^
    if (mac_mode) { LL_6_MAC(); } else { LL_6_LINUX(); }
  case LL_QUOT: //'|"
      SHIFT_ALL(DE_HASH, DE_2)
  case LL_LBRC://[|{
    if (mac_mode) { LL_LBRC_MAC(); } else { LL_LBRC_LINUX(); }
  case LL_RBRC://]|}
    if (mac_mode) { LL_RBRC_MAC(); } else { LL_RBRC_LINUX(); }
  case LL_BSLS: //\||
    if (mac_mode) { LL_BSLS_MAC(); } else { LL_BSLS_LINUX(); }
  case LL_COMM: //,|<
    if (mac_mode) { LL_COMM_MAC(); } else { LL_COMM_LINUX(); }
  case LL_DOT: //.|>
    if (mac_mode) { LL_DOT_MAC(); } else { LL_DOT_LINUX(); }
  case LL_SPECIAL:// °|unset/can be used for whatever
    if (mac_mode) { LL_SPECIAL_MAC(); } else { LL_SPECIAL_LINUX(); }
  case LL_HOME: // line start, Cmd+Left on mac
    if (record->event.pressed) {
      if (mac_mode) { LL_HOME_MAC_PRESS(); } else { LL_HOME_LINUX_PRESS(); }
    } else {
      if (mac_mode) { LL_HOME_MAC_RELEASE(); } else { LL_HOME_LINUX_RELEASE(); }
    }
    return false;
  case LL_END: // line end, Cmd+Right on mac
    if (record->event.pressed) {
      if (mac_mode) { LL_END_MAC_PRESS(); } else { LL_END_LINUX_PRESS(); }
    } else {
      if (mac_mode) { LL_END_MAC_RELEASE(); } else { LL_END_LINUX_RELEASE(); }
    }
    return false;
  case LL_PSCR: // screenshot, Shift+Cmd+4 on mac
    if (record->event.pressed) {
      if (mac_mode) { LL_PSCR_MAC_PRESS(); } else { LL_PSCR_LINUX_PRESS(); }
    } else {
      if (mac_mode) { LL_PSCR_MAC_RELEASE(); } else { LL_PSCR_LINUX_RELEASE(); }
    }
    return false;
  case LL_T1: // left inner thumb
    if (record->event.pressed) {
      register_code(mac_mode ? LL_T1_MAC() : LL_T1_LINUX());
    } else {
      unregister_code(mac_mode ? LL_T1_MAC() : LL_T1_LINUX());
    }
    return false;
  case LL_T2: // left middle thumb
    if (record->event.pressed) {
      register_code(mac_mode ? LL_T2_MAC() : LL_T2_LINUX());
    } else {
      unregister_code(mac_mode ? LL_T2_MAC() : LL_T2_LINUX());
    }
    return false;
  case LL_OS: // toggled by the six-thumb chord
    if (record->event.pressed) {
      os_toggle();
    }
    return false;
  case LL_AR_L://<= | <-
    if(record->event.pressed) {
        unregister_code(KC_LSFT);
        if (lshift){
            if (mac_mode) { LL_AR_L_MAC_SHIFTED(); } else { LL_AR_L_LINUX_SHIFTED(); }
        }else{
            if (mac_mode) { LL_AR_L_MAC(); } else { LL_AR_L_LINUX(); }
        }
        if (lshift){
            register_code(KC_LSFT);
        }
    }
    return false;
  case LL_AR_R: // =>| ->
    if(record->event.pressed) {
        unregister_code(KC_LSFT);
        if (lshift){
            if (mac_mode) { LL_AR_R_MAC_SHIFTED(); } else { LL_AR_R_LINUX_SHIFTED(); }
        }else{
            if (mac_mode) { LL_AR_R_MAC(); } else { LL_AR_R_LINUX(); }
        }
        if (lshift){
            register_code(KC_LSFT);
        }
    }
    return false;
  case LL_SM_1:
    if(record->event.pressed) {

      send_unicode_string("¯\\_(ツ)_/¯");
    }
    return false;
  case LL_SM_2:
    if(record->event.pressed) {
      send_unicode_string("༼ つ ◕_◕ ༽つ");
    }
    return false;
  case LL_SM_A:
    if(record->event.pressed) {
      ucis_start();
    }
    return false;
  case LL_T_MO:
    if(record->event.pressed) {

    mocking_case_active = !mocking_case_active;
    }

case DE_A ... DE_Z:{
    if (mocking_case_active && record->event.pressed) {
        if (mocking_case_shift_up) {
            register_code(KC_LSFT);
        }
        mocking_case_shift_up = !mocking_case_shift_up;
    }
}
  default:
    return true;
  }
}



void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DE_A ... DE_Z:{
            if (mocking_case_active && record->event.pressed) {
                                 unregister_code(KC_LSFT);
                       }
        }
    }

}
