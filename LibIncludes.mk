ifeq ($(CONFIG_EXTERNALS_NEOPIXEL),y)
NEOPIXEL_LIBDIR += $(EXTERNAL_DIR)$(DELIM)neopixel-for-spresense$(DELIM)neopixel_extlib
CFLAGS     += ${shell $(INCDIR) $(INCDIROPT) "$(CC)" "$(NEOPIXEL_LIBDIR)"}
CXXFLAGS   += ${shell $(INCDIR) $(INCDIROPT) "$(CC)" "$(NEOPIXEL_LIBDIR)"}
endif
