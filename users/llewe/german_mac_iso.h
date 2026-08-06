#pragma once

// macOS German layout swaps the ^/° and </> keys relative to the
// Windows/Linux German layout:
//
//   Win/Linux DE:  ^ and ° on KC_GRV (key left of 1), < and > on KC_NUBS (ISO key)
//   macOS DE:      < and > on KC_GRV, ^ and ° on KC_NUBS
//
// keymap_german.h and keymap_german_mac_iso.h both assume the Win/Linux
// positions. When building for macOS (GERMAN_MAC_ISO), remap the aliases so
// sendstring, CU_COMM/CU_DOT, and the dead-key layer produce the right
// characters. DE_RABK (S(DE_LABK)) and DE_DEG (S(DE_CIRC)) follow
// automatically.
#ifdef GERMAN_MAC_ISO
#undef DE_CIRC
#define DE_CIRC KC_NUBS  // ^ (dead)
#undef DE_LABK
#define DE_LABK KC_GRV   // <
#endif
