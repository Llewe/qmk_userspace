/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    GNU, // German number & fn
    GSK, // German special keys
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
    LL_SPECIAL, //'|"
    LL_ARROW_LEFT, //<= | <-
    LL_ARROW_RIGHT, // =>| ->

    LL_SM_1, //¯\_(ツ)_/¯
    LL_SM_2, //༼ つ ◕_◕ ༽つ
    LL_SM_A,
    LL_T_MOCKING
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




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [AG1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    DE_Q,    DE_W,    DE_E,    DE_R,    DE_T, LL_LBRC,    LL_RBRC,    DE_Y,    DE_U,    DE_I,    DE_O,   DE_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      LL_LSFT,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G, LL_QUOT,    CU_BSLS,    DE_H,    DE_J,    DE_K,    DE_L, CU_SCLN, KC_PGUP,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    DE_Z,    DE_X,    DE_C,    DE_V,    DE_B,                         DE_N,    DE_M, CU_COMM,  CU_DOT, CU_SLSH, KC_HOME,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_LALT,  KC_SPC,     KC_ENT, MO(GNU), MO(GSK)
                                      //`--------------------------'  `--------------------------'

  ),

  [GNU] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_ESC,    DE_1,    LL_2,    CU_3,    DE_4,    DE_5,  LL_GRV,    DE_MINS,    LL_6,    CU_7,    CU_8,    CU_9,    CU_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     CU_EQL, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [GSK] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,   CU_UE, XXXXXXX,   CU_OE, XXXXXXX, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,   CU_AE,   CU_SS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, LL_ARROW_LEFT, LL_ARROW_RIGHT, XXXXXXX,  KC_END,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______, KC_INSERT, MO(OTH), _______
                                      //`--------------------------'  `--------------------------'
  ),

  [OTH] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
    QK_REBOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,LL_T_MOCKING,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  _______, _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [DEFAULT1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_LCTL,    KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,    KC_RALT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),

  [DEFAULT2] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  )
};


enum layers current_active_base_layer = AG1;



// Shift & ALGR
#define SHIFT_AND_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    unregister_code(KC_LSFT); \
    register_code(KC_ALGR); \
    unregister_code(kc2); \
    register_code(kc2); \
    unregister_code(kc2); \
    unregister_code(KC_ALGR); \
    register_code(KC_LSFT); \
    add_to_prev(kc2); \
  } else { \
    register_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;
// Normal & ALGR
#define NORMAL_AND_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    unregister_code(KC_LSFT); \
    register_code(KC_ALGR); \
    unregister_code(kc2); \
    register_code(kc2); \
    unregister_code(kc2); \
    register_code(KC_LSFT); \
    unregister_code(KC_ALGR); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    unregister_code(kc1); \
  } \
} \
return false;

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_WHITE);
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

  case LL_GRV:
      //this key need to check also if its an us or ger key layout at the moment
     // if (AG1 == current_active_base_layer){
      SHIFT_AND_ALGR(KC_EQL, DE_PLUS) //`|~
      /*}
       if (ANSI_US == current_active_base_layer){
        if(record->event.pressed) {
          register_code(KC_GRV);
        } else {
          unregister_code(KC_GRV);
        }
        return false;
      }
    */
      // if (eeconfig_read_default_layer() == ANSI_US_GER){
      //     SHIFT_AND_ALGR(KC_EQL, DE_PLUS) //`|~
      // }
      // if (eeconfig_read_default_layer() == ANSI_US){
      //   if(record->event.pressed) {
      //     register_code(KC_GRV);
      //   } else {
      //     unregister_code(KC_GRV);
      //   }
      //   return false;
      // }
  case LL_2: //2|@
      NORMAL_AND_ALGR(DE_2, DE_Q)
  case LL_6: //6|^
      SHIFT_NO(DE_6, DE_CIRC)
  case LL_QUOT: //'|"
      SHIFT_ALL(DE_HASH, DE_2)
  case LL_LBRC://[|{
      SHIFT_ALGR(DE_8,DE_7)
  case LL_RBRC://}|}
      SHIFT_ALGR(DE_9,DE_0)
  case LL_SPECIAL:// °|unset/can be used for whatever
      SHIFT_NORM(KC_KP_0, DE_CIRC)
  case LL_ARROW_LEFT://<= | <-
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
          return false;
      }
  case LL_ARROW_RIGHT: // =>| ->
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
          return false;
      }
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
  case LL_T_MOCKING:
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
