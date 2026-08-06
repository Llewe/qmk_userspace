// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*
macOS variant of the "llewe" keymap.

The host is expected to run the German (ISO) macOS layout. The base key
positions of the German macOS layout are identical to the German PC layout,
so keymap_german.h (pulled in by the userspace) still describes them
correctly. Only the Option/AltGr plane differs:

    char   Win/Linux DE   macOS DE
    @      AltGr+Q        Opt+L
    ~      AltGr++        Opt+N   (dead key)
    \      AltGr+ss       Shift+Opt+7
    |      AltGr+<        Opt+7
    {      AltGr+7        Opt+8
    }      AltGr+0        Opt+9
    [      AltGr+8        Opt+5
    ]      AltGr+9        Opt+6

< and > stay on KC_NUBS on macOS as well. If they do not work, macOS has
identified the keyboard as ANSI - see readme.md.

Because the userspace hardcodes the PC sequences for CU_BSLS, this keymap
uses its own LL_BSLS instead.
*/

#include QMK_KEYBOARD_H

#include "keymap_german.h"
#include "sendstring_german.h"
#include "spacebarracecar.h"


bool mocking_case_active = false;
bool mocking_case_shift_up = false;

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
    LL_BSLS, //\||
    LL_QUOT, //'|"
    LL_SPECIAL, //'|"
    LL_AR_L, //<= | <-
    LL_AR_R, // =>| ->

    LL_SM_1, //¯\_(ツ)_/¯
    LL_SM_2, //༼ つ ◕_◕ ༽つ
    LL_SM_A, // type ucis name
    LL_T_MO // toggle mocking case
};

// macOS equivalents of the keys that behave differently than on Win/Linux
#define MAC_HOME LGUI(KC_LEFT)
#define MAC_END  LGUI(KC_RGHT)
#define MAC_PSCR SGUI(KC_4)     // screenshot selection

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [AG1] = LAYOUT(
        KC_ESC,  DE_1,    LL_2,    CU_3,    DE_4,    DE_5,                                 LL_6,    CU_7,    CU_8,    CU_9,    CU_0,    KC_BSPC,
        KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                                 DE_Y,    DE_U,    DE_I,    DE_O,    DE_P,    MAC_HOME,
        LL_LSFT, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                                 DE_H,    DE_J,    DE_K,    DE_L,    CU_SCLN, KC_PGUP,
        KC_LCTL, DE_Z,    DE_X,    DE_C,    DE_V,    DE_B,                                 DE_N,    DE_M,    CU_COMM, CU_DOT,  CU_SLSH, LL_BSLS,
                                            KC_LALT, KC_LGUI, KC_SPC,           KC_ENT, MO(GNU), MO(GSK)
    ),
    [GNU] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, LL_LBRC, LL_RBRC,  KC_DEL,
        LL_GRV,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, DE_MINS,  CU_EQL, MAC_END,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, LL_QUOT, KC_PGDN,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, LL_AR_L, LL_AR_R, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_INSERT, KC_TRNS, KC_TRNS
    ),

    [GSK] = LAYOUT(
        KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, MAC_PSCR,
        KC_TRNS,  KC_F11,  KC_F12, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,   CU_UE, KC_TRNS,   CU_OE, KC_TRNS, KC_TRNS,
        KC_TRNS,   CU_AE,   CU_SS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_MPLY, MO(OTH), KC_TRNS
    ),

    [OTH] = LAYOUT(
        KC_TRNS, LL_SM_1, LL_SM_2, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LL_T_MO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          LL_SM_A, KC_TRNS, KC_TRNS
    )

};

enum layers current_active_base_layer = AG1;


/*
Building blocks for the macOS Option plane. KC_ALGR (right alt) is used as
Option so the left thumb Option key stays free for normal shortcuts.
*/

// Option + kc, ignoring the physical shift state
#define MAC_OPT(kc) \
  unregister_code(KC_LSFT); \
  register_code(KC_ALGR); \
  unregister_code(kc); \
  register_code(kc); \
  unregister_code(kc); \
  unregister_code(KC_ALGR);

// Shift + Option + kc
#define MAC_SOPT(kc) \
  register_code(KC_LSFT); \
  register_code(KC_ALGR); \
  unregister_code(kc); \
  register_code(kc); \
  unregister_code(kc); \
  unregister_code(KC_ALGR); \
  unregister_code(KC_LSFT);

// Shift + kc, ignoring the physical shift state
#define MAC_SFT(kc) \
  register_code(KC_LSFT); \
  unregister_code(kc); \
  register_code(kc); \
  unregister_code(kc); \
  unregister_code(KC_LSFT);

// Resolves a dead key by typing a space after it
#define MAC_DEAD_ESC() \
  register_code(KC_SPC); \
  unregister_code(KC_SPC);

// Puts KC_LSFT back into the state the physical shift keys are in
#define MAC_RESTORE_SFT() \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT);

// Option+kc1 unshifted, Option+kc2 shifted
#define MAC_OPT_OPT(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    MAC_OPT(kc2) \
  } else { \
    MAC_OPT(kc1) \
  } \
  MAC_RESTORE_SFT() \
} \
return false;

// Plain kc1 unshifted, Option+kc2 shifted
#define MAC_NORM_OPT(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    MAC_OPT(kc2) \
    MAC_RESTORE_SFT() \
  } else { \
    unregister_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
} \
return false;


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
    // ` is Shift+acute, ~ is Opt+N - both are dead keys and need the escape
    if(record->event.pressed) {
      timer_timeout();
      if (lshift || rshift) {
        MAC_OPT(DE_N)
      } else {
        MAC_SFT(DE_ACUT)
      }
      MAC_DEAD_ESC()
      MAC_RESTORE_SFT()
    }
    return false;
  case LL_2: //2|@
      MAC_NORM_OPT(DE_2, DE_L)
  case LL_6: //6|^
    // ^ is a dead key on macOS as well
    if(record->event.pressed) {
      timer_timeout();
      unregister_code(KC_LSFT);
      if (lshift || rshift) {
        unregister_code(DE_CIRC);
        register_code(DE_CIRC);
        unregister_code(DE_CIRC);
        MAC_DEAD_ESC()
        register_code(KC_LSFT);
      } else {
        register_code(DE_6);
      }
    } else {
      unregister_code(DE_6);
    }
    return false;
  case LL_QUOT: //'|"
      SHIFT_ALL(DE_HASH, DE_2)
  case LL_LBRC://[|{
      MAC_OPT_OPT(DE_5, DE_8)
  case LL_RBRC://]|}
      MAC_OPT_OPT(DE_6, DE_9)
  case LL_BSLS: //\||
    // \ is Shift+Opt+7, | is Opt+7
    if(record->event.pressed) {
      timer_timeout();
      if (lshift || rshift) {
        MAC_OPT(DE_7)
      } else {
        MAC_SOPT(DE_7)
      }
      MAC_RESTORE_SFT()
    }
    return false;
  case LL_SPECIAL:// °|unset/can be used for whatever
      SHIFT_NORM(KC_KP_0, DE_CIRC)
  case LL_AR_L://<= | <-
      if(record->event.pressed) {
          unregister_code(KC_LSFT);
          if (lshift){
              SEND_STRING("<-");
          }else{
              SEND_STRING("<=");
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
              SEND_STRING("->");
          }else{
              SEND_STRING("=>");
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
