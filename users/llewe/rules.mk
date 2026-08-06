SRC += llewe.c

ifeq ($(strip $(GERMAN_ENABLE)), yes)
    OPT_DEFS += -DGERMAN_ENABLE
endif

ifeq ($(strip $(GERMAN_MAC_ISO)), yes)
    OPT_DEFS += -DGERMAN_MAC_ISO
endif

