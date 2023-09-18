/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  CT Board periphery test.
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */


/* Standard includes */
#include <stdint.h>

/* User includes */
#include "init_ctboard.h"
#include "scheduler.h"
#include "tests.h"

#include "hal_gpio.h"


/* -- Macros
 * ------------------------------------------------------------------------- */
 
#define INTERVAL_COMMON                 (10u)
#define INTERVAL_FAST                   (5u)
#define INTERVAL_SLOW                   (20u)


/* -- Local function declarations
 * ------------------------------------------------------------------------- */

static scheduler_task_t task_DIPSW_LED;
static scheduler_task_t task_7SEGMENT;
static scheduler_task_t task_BUTTON;
static scheduler_task_t task_POTI;
static scheduler_task_t task_PWM;
static scheduler_task_t task_GPIO;
static scheduler_task_t task_HEXSW;
static scheduler_task_t task_DIRECT_GPIO;
    

/* -- M A I N --------------------------------------------------------------
 * ------------------------------------------------------------------------- */


int main(void)
{   
    init_CT_BOARD();
    scheduler_init();
    
    scheduler_register_task(&task_BUTTON, test_BUTTON, INTERVAL_COMMON);
    scheduler_register_task(&task_GPIO, test_GPIO, INTERVAL_COMMON);
    scheduler_register_task(&task_HEXSW, test_HEXSW, INTERVAL_COMMON);
    scheduler_register_task(&task_PWM, test_PWM, INTERVAL_COMMON);
    scheduler_register_task(&task_DIPSW_LED, test_DIPSW_LED, INTERVAL_SLOW);
    scheduler_register_task(&task_7SEGMENT, test_7SEGMENT, INTERVAL_SLOW);
    scheduler_register_task(&task_POTI, test_POTI, INTERVAL_FAST);
    scheduler_register_task(&task_DIRECT_GPIO, test_DIRECT_GPIO, INTERVAL_COMMON);
    
    while(1);
}
