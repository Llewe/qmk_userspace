// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*
One keymap for Linux and macOS, switched at runtime.

Press all six thumb keys at once to toggle between the two variants. The
Linux implementation lives in users/llewe/os_linux.h, the
macOS one in users/llewe/os_mac.h - per-system changes stay in a single file.
The OS-variant dispatcher, keycode enums and toggle logic live next to this
file in llewe_common.h; the layer arrays are defined below.

IMPORTANT (macOS): the input source must be "German" (Deutsch), NOT
"German - Standard" (Deutsch Standard). The latter is the PC-style
layout and puts @ { } etc. on the PC AltGr positions (Opt+Q, Opt+7,
Opt+0 ...), which this keymap does not follow.

The two keyboard halves know their role via EE_HANDS. CI builds handedness
variants: flash silakka54_llewe_left.uf2 on both left halves and
silakka54_llewe_right.uf2 on both right halves (drag & drop; each file forces
its role on every boot). Alternatively flash each half once with
`qmk flash -kb silakka54 -km llewe -bl uf2-split-left` / `uf2-split-right` to
store the role in EEPROM. The half connected to USB becomes the master
automatically, so boards with USB on the left or right side both work with
this single firmware.
*/

#include QMK_KEYBOARD_H

#include "keymap_german.h"
#include "sendstring_german.h"
#include "llewe.h"
#include "llewe_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [AG1] = LAYOUT(
        KC_ESC,  DE_1,    LL_2,    CU_3,    DE_4,    DE_5,                                 LL_6,    CU_7,    CU_8,    CU_9,    CU_0,    KC_BSPC,
        KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                                 DE_Y,    DE_U,    DE_I,    DE_O,    DE_P,    LL_HOME,
        LL_LSFT, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                                 DE_H,    DE_J,    DE_K,    DE_L,    CU_SCLN, KC_PGUP,
        KC_LCTL, DE_Z,    DE_X,    DE_C,    DE_V,    DE_B,                                 DE_N,    DE_M,    LL_COMM, LL_DOT,  CU_SLSH, LL_BSLS,
                                            LL_T1,   LL_T2,   KC_SPC,           KC_ENT, MO(GNU), MO(GSK)
    ),
    [GNU] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, LL_LBRC, LL_RBRC,  KC_DEL,
        LL_GRV,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, DE_MINS,  CU_EQL,  LL_END,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, LL_QUOT, KC_PGDN,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, LL_AR_L, LL_AR_R, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_INSERT, KC_TRNS, KC_TRNS
    ),

    [GSK] = LAYOUT(
        KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, LL_PSCR,
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
