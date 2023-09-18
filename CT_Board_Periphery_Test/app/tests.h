/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Interface of module tests.
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */

/* re-definition guard */
#ifndef _TESTS_H
#define _TESTS_H
 
 
/* -- Public function declarations
 * ------------------------------------------------------------------------- */
 
void test_DIPSW_LED(void);
void test_7SEGMENT(void);
void test_BUTTON(void);
void test_POTI(void);
void test_PWM(void);
void test_GPIO(void);
void test_HEXSW(void);
void test_DIRECT_GPIO(void);


#endif
