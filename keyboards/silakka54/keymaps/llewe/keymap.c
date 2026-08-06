// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef GERMAN_MAC_ISO
#include "keymap_german_mac_iso.h"
#include "german_mac_iso.h"
#include "sendstring_german_mac_iso.h"
#else
#include "keymap_german.h"
#include "sendstring_german.h"
#endif
#include "llewe.h"
#include "llewe_common.h"
