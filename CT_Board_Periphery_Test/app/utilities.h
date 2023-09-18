/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Macros.
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */

/* re-definition guard */
#ifndef _UTILITIES_H
#define _UTILITIES_H


/* -- Macros
 * ------------------------------------------------------------------------- */

#define REG8(ADDRESS, OFFSET)           (*( uint8_t *) (ADDRESS + OFFSET))
#define REG16(ADDRESS, OFFSET)          (*(uint16_t *) (ADDRESS + OFFSET))
#define REG32(ADDRESS, OFFSET)          (*(uint32_t *) (ADDRESS + OFFSET))

 
#define CT_ADDR_LED                     (0x60000100)
#define CT_ADDR_7SEG                    (0x60000110)

#define CT_ADDR_DIPSW                   (0x60000200)
#define CT_ADDR_BUTTON                  (0x60000210)
#define CT_ADDR_HEXSW                   (0x60000211)

#define CT_LCD_ASCII                    (0x60000300)
#define CT_LCD_BIN                      (0x60000330)
#define CT_LCD_PWM                      (0x60000340)

#define CT_GPIO_OUT                     (0x60000400)
#define CT_GPIO_IN                      (0x60000410)


#endif
