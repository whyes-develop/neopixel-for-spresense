ifeq ($(CONFIG_EXTERNALS_NEOPIXEL),y)
EXTRA_LIBPATHS += -L "$(EXTLIBDIR)$(DELIM)neopixel-for-spresense"
EXTRA_LIBS     += -lneopixel
endif
