############################################################################
# configs/sam3u-ek/kernel/Makefile
#
#   Copyright (C) 2011 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

-include $(TOPDIR)/.config
-include $(TOPDIR)/Make.defs

# This is the directory for the board-specific header files

BOARD_INCLUDE	= $(TOPDIR)/configs/$(CONFIG_ARCH_BOARD)/include

# Get the paths to the libraries and the links script path in format that
# is appropriate for the host OS

ifeq ($(WINTOOL),y)
  # Windows-native toolchains
  USER_LIBPATHS	= ${shell for path in $(USERLIBS); do dir=`dirname $(TOPDIR)/$$path`;echo "-L\"`cygpath -w $$dir`\"";done}
  USER_LDSCRIPT	= -T "${shell cygpath -w $(TOPDIR)/configs/$(CONFIG_ARCH_BOARD)/kernel/kernel.ld}"
else
  # Linux/Cygwin-native toolchain 
  USER_LIBPATHS	= $(addprefix -L$(TOPDIR)/,$(dir $(USERLIBS)))
  USER_LDSCRIPT	= -T$(TOPDIR)/configs/$(CONFIG_ARCH_BOARD)/kernel/kernel.ld
endif

USER_LDFLAGS	= $(USER_LDSCRIPT)
USER_LDLIBS		= $(patsubst lib%,-l%,$(basename $(notdir $(USERLIBS))))
USER_LIBGCC		= "${shell $(CC) -print-libgcc-file-name}"

# Targets:

all: $(TOPDIR)/nuttx_user.elf $(TOPDIR)/User.map $(BOARD_INCLUDE)/user_map.h

.PHONY:	depend clean distclean

# Create the nuttx_user.elf file containing all of the user-mode code

nuttx_user.elf:
	@$(LD) -o $@ $(USER_LDFLAGS) $(USER_LIBPATHS) --start-group $(USER_LDLIBS) --end-group $(USER_LIBGCC) 

$(TOPDIR)/nuttx_user.elf: nuttx_user.elf
	@echo "LD: nuttx_user.elf"
	@cp -a nuttx_user.elf $(TOPDIR)/nuttx_user.elf
ifeq ($(CONFIG_INTELHEX_BINARY),y)
	@echo "CP: nuttx_user.hex"
	@$(OBJCOPY) $(OBJCOPYARGS) -O ihex nuttx_user.elf $(TOPDIR)/nuttx_user.hex
endif
ifeq ($(CONFIG_MOTOROLA_SREC),y)
	@echo "CP: nuttx_user.srec"
	@$(OBJCOPY) $(OBJCOPYARGS) -O srec nuttx_user.elf $(TOPDIR)/nuttx_user.srec
endif
ifeq ($(CONFIG_RAW_BINARY),y)
	@echo "CP: nuttx_user.bin"
	@$(OBJCOPY) $(OBJCOPYARGS) -O binary nuttx_user.elf $(TOPDIR)/nuttx_user.bin
endif

$(TOPDIR)/User.map: nuttx_user.elf
	@echo "MK: User.map"
	@$(NM) nuttx_user.elf >$(TOPDIR)/User.map
	@$(CROSSDEV)size nuttx_user.elf

$(BOARD_INCLUDE)/user_map.h: $(TOPDIR)/User.map
	@echo "MK: user_map.h"
	@echo "/* configs/$(CONFIG_ARCH_BOARD)/include/user_map.h" > $(BOARD_INCLUDE)/user_map.h
	@echo " *" >> $(BOARD_INCLUDE)/user_map.h
	@echo " * This is an auto-generated file.. Do not edit this file!" >> $(BOARD_INCLUDE)/user_map.h
	@echo " */" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#ifndef __ARCH_BOARD_USER_MAP_H" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define __ARCH_BOARD_USER_MAP_H" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "/* General memory map */" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_ENTRYPOINT    0x`grep \" user_start$\" $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_TEXTSTART     0x`grep \" _stext\"       $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_TEXTEND       0x`grep \" _etext$\"      $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_DATASOURCE    0x`grep \" _eronly$\"    $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_DATADESTSTART 0x`grep \" _sdata$\"     $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_DATADESTEND   0x`grep \" _edata$\"     $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_BSSSTART      0x`grep \" _sbss\"       $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_BSSEND        0x`grep \" _ebss$\"      $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "/* Memory manager entry points */" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_MMINIT        0x`grep \" mm_initialize$\"    $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_MMADDREGION   0x`grep \" mm_addregion$\"     $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_MMTRYSEM      0x`grep \" mm_trysemaphore$\"  $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_MMGIVESEM     0x`grep \" mm_givesemaphore$\" $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_MALLOC        0x`grep \" malloc$\"  $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_REALLOC       0x`grep \" realloc$\" $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_ZALLOC        0x`grep \" zalloc$\"  $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#define CONFIG_USER_FREE          0x`grep \" free$\"    $(TOPDIR)/User.map | cut -d' ' -f1`" >> $(BOARD_INCLUDE)/user_map.h
	@echo "" >> $(BOARD_INCLUDE)/user_map.h
	@echo "#endif /* __ARCH_BOARD_USER_MAP_H */" >> $(BOARD_INCLUDE)/user_map.h

.depend:

depend: .depend

clean:
	@rm -f nuttx_user.elf *~ .*.swp
	@rm -f $(TOPDIR)/nuttx_user.elf $(TOPDIR)/User.map

distclean: clean

