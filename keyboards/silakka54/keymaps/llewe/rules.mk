PROGRAMMABLE_BUTTON_ENABLE = yes
USER_NAME := llewe
GERMAN_ENABLE = yes
UCIS_ENABLE = yes
COMBO_ENABLE = yes

# Handedness variants for CI: qmk compile -e HANDEDNESS=left|right bakes
# INIT_EE_HANDS_* into the firmware, so the resulting .uf2 forces that half's
# role on every boot (drag & drop flashing, no EE_HANDS setup needed).
ifeq ($(strip $(HANDEDNESS)), left)
    OPT_DEFS += -DINIT_EE_HANDS_LEFT
endif
ifeq ($(strip $(HANDEDNESS)), right)
    OPT_DEFS += -DINIT_EE_HANDS_RIGHT
endif
