/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module hal_systick.
 *  \TODO   Refactor!!
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */

/* User includes */
#include "hal_systick.h"
#include "reg_stm32f4xx.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

#define STK_CTRL_ENABLE         (0x1u << 0u)
#define STK_CTRL_TICK_EN        (0x1u << 1u)
#define STK_CTRL_CLEAR_MASK     (0xfffefff8)
#define STK_LOAD_MASK           (0x00ffffff)

#define SCB_SYSTICK_PRIO        (3u << 28u)
#define SCB_CLEAR_MASK          (0x00ffffff)


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 *  See header file
 */
void hal_systick_reset(void)
{
    STK->CTRL &= STK_CTRL_CLEAR_MASK;
    STK->LOAD = 0u;
    STK->VAL = 0u;
    
    SCB->SHPR3 &= SCB_CLEAR_MASK;
}


/*
 *  See header file
 */
void hal_systick_init(hal_systick_clk_t clock, uint32_t reload)
{
    /* Initialize SysTick timer */
    STK->CTRL &= STK_CTRL_CLEAR_MASK;
    STK->CTRL |= ((uint32_t) clock << 2u);
    STK->CTRL |= STK_CTRL_TICK_EN;
    STK->LOAD = (reload & STK_LOAD_MASK);
    STK->VAL = 0u;
    
    /* Set priority of SysTick timer */
    SCB->SHPR3 |= SCB_SYSTICK_PRIO;
    
    /* Enable SysTick timer */
    STK->CTRL |= STK_CTRL_ENABLE;
}


/*
 *  See header file
 */
void hal_systick_pause(void)
{
    STK->CTRL &= ~(STK_CTRL_TICK_EN);
}


/*
 *  See header file
 */
void hal_systick_resume(void)
{
    STK->CTRL |= STK_CTRL_TICK_EN;
}

