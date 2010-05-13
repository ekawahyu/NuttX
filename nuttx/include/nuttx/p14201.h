/****************************************************************************
 * include/nuttx/p14201.h
 *
 *   Copyright (C) 2010 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <spudmonkey@racsa.co.cr>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_P14201_H
#define __INCLUDE_NUTTX_P14201_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* P14201 Configuration Settings:
 *
 * CONFIG_LCD_P14201 - Enable P14201 support
 * CONFIG_P14201_OWNBUS - Set if the P14201 is the only active device on the SPI bus.
 *   No locking or SPI configuration will be performed. All transfers will be performed
 *   from the ENC2J60 interrupt handler.
 * CONFIG_P14201_SPIMODE - Controls the SPI mode
 * CONFIG_P14201_FREQUENCY - Define to use a different bus frequency
 * CONFIG_P14201_NINTERFACES - Specifies the number of physical P14201 devices that
 *   will be supported.
 *
 * Required LCD driver settings:
 * CONFIG_LCD_MAXCONTRAST should be 255, but any value >0 and <=255 will be accepted.
 * CONFIG_LCD_MAXPOWER must be 1
 */

/* Some important "colors" */

#define RIT_Y4_BLACK 0x00
#define RIT_Y4_WHITE 0x0f

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C" {
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/**************************************************************************************
 * Name:  rit_initialize
 *
 * Description:
 *   Initialize the P14201 video hardware.  The initial state of the OLED is fully
 *   initialized, display memory cleared, and the OLED ready to use, but with the power
 *   setting at 0 (full off == sleep mode).
 *
 * Input Parameters:
 *
 *   spi - A reference to the SPI driver instance.
 *   devno - A value in the range of 0 throuh CONFIG_P14201_NINTERFACES-1.  This allows
 *   support for multiple OLED devices.
 *
 * Returned Value:
 *
 *   On success, this function returns a reference to the LCD object for the specified
 *   OLED.  NULL is returned on any failure.
 *
 **************************************************************************************/

struct lcd_dev_s; /* see nuttx/lcd.h */
struct spi_dev_s; /* see nuttx/spi.h */
EXTERN FAR struct lcd_dev_s *rit_initialize(FAR struct spi_dev_s *spi, unsigned int devno);

/**************************************************************************************
 * Name:  rit_seldata
 *
 * Description:
 *   Set or clear the SD1329 D/Cn bit to select data (true) or command (false).  This
 *   function must be provided by platform-specific logic.
 *
 * Input Parameters:
 *
 *   devno - A value in the range of 0 throuh CONFIG_P14201_NINTERFACES-1.  This allows
 *   support for multiple OLED devices.
 *   data - true: select data; false: select command
 *
 * Returned Value:
 *   None
 *
 **************************************************************************************/

EXTERN void rit_seldata(unsigned int devno, bool data);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_NUTTX_P14201_H */