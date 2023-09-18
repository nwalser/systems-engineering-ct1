/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Interface of module scheduler.
 *
 *  $Id$
 * ------------------------------------------------------------------------- */

/* Re-definition guard */
#ifndef _SCHEDULER_H
#define _SCHEDULER_H

/* Standard includes */
#include <stdint.h>


/* -- Macros
 * ------------------------------------------------------------------------- */

#define TEN_MILLISECONDS        (uint32_t)10
#define HUNDRED_MILLISECONDS    (uint32_t)100
#define ONE_SECOND              (uint32_t)1000


/* -- Type definitions
 * ------------------------------------------------------------------------- */

typedef void (*scheduler_callback_t)(void);

typedef struct scheduler_task_t {
    scheduler_callback_t callback;
    uint32_t period_ms;
    uint32_t elapsed_at;
    uint32_t delayed_exec_count;

    struct scheduler_task_t *prev;
    struct scheduler_task_t *next;
} scheduler_task_t;


/* -- Public function declarations
 * ------------------------------------------------------------------------- */

/**
 *  \brief  Initializes scheduler module.
 */
void scheduler_init(void);

/**
 *  \brief  Register a cooperative task.
 *  \note   Make sure to hold the task short or overflow of timing
 *          can happen and other tasks not executed on time.
 *  \param  *schedulerTaskObject : Pointer to the task context.
 *  \param  callback : Cooperative Task Routine.
 *  \param  period_ms : Execution period of task in ms.
 */
void scheduler_register_task(scheduler_task_t *task,
                             scheduler_callback_t callback,
                             uint32_t period_ms);

/**
 *  \brief  unregister a given task from execution
 *  \param  *schedulerTaskObject : Pointer to the task context.
 */
void scheduler_unregister_task(scheduler_task_t *task);


/**
 *  \brief  call hal tick handler to handle tick accordingly
            and use the default functionality given by hal
 */
void SysTick_Handler(void);


#endif
