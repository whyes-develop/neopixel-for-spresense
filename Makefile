# SPDX-FileCopyrightText: 2023 whyes-develop
# SPDX-License-Identifier: MIT

-include $(APPDIR)/Make.defs
-include $(SDKDIR)/Make.defs

BIN = libneopixel$(LIBEXT)

NEOPIXELLIBDIR = neopixel_extlib

ROOTDEPPATH += --dep-path $(NEOPIXELLIBDIR)
VPATH += :$(NEOPIXELLIBDIR)

CSRCS += neopixel.c

include $(APPDIR)/Application.mk
