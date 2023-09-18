/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ------------------------------------------------------------------------- */
/**
 *  \brief  Implementation of module scheduler.
 * 
 *  $Id$
 * ------------------------------------------------------------------------- */

 
/* Standard includes */
#include <stdbool.h>

/* User includes */
#include "scheduler.h"
#include "hal_systick.h"


/* -- Macros
 * ------------------------------------------------------------------------- */

#define NULL                ((void *)0)
    
#define SYSTICK_RELOAD      (84000u - 1u)


/* -- Variables with module-wide scope
 * ------------------------------------------------------------------------- */
 
static scheduler_task_t *task_temp = NULL;
static uint32_t tick_count;


/* -- Local function declarations
 * ------------------------------------------------------------------------- */
 
static void scheduler_check_tasks(void);
static void scheduler_task_add(scheduler_task_t *task);
static void scheduler_task_remove(scheduler_task_t *task);
static void scheduler_task_reschedule(scheduler_task_t *task);
static bool schedule_is_elapsed(scheduler_task_t *task);


/* -- Public function definitions
 * ------------------------------------------------------------------------- */

/*
 *  See header file
 */
void scheduler_init(void)
{
    /* Initialize counter variable */
    tick_count = 0u;
    
    /* Initialize SysTick timer */
    hal_systick_init(HAL_RCC_CLK_HCLK, SYSTICK_RELOAD);
}


/*
 *  See header file
 */
void scheduler_register_task(scheduler_task_t *task,
                             scheduler_callback_t callback,     
                             uint32_t period_ms)
{
    uint32_t now = tick_count;
    
    // initialize object
    task->callback = callback;
    task->period_ms = period_ms;
    task->elapsed_at = now + period_ms;
    task->delayed_exec_count = 0;

    scheduler_task_add(task);
}


/*
 *  See header file
 */
void scheduler_unregister_task(scheduler_task_t *task)
{
    // critical section
    hal_systick_pause();
    task->callback = NULL;
    scheduler_task_remove(task);
    // end critical section
    hal_systick_resume();
}


/* -- Interrupt function definitions
 * ------------------------------------------------------------------------- */
 
void SysTick_Handler(void)
{
    // call hal tick handler to handle tick accordingly
    // and use the default functionality given by hal
    tick_count++;
    
    // go through all waiting objects
    scheduler_check_tasks();
}


/* -- Local function definitions
 * ------------------------------------------------------------------------- */

/**
 *  \brief  Go through task list and check if to execute, do so if needed.
 */
static void scheduler_check_tasks(void)
{
    scheduler_task_t *item = task_temp;
    
    while(item != NULL) {
        if(schedule_is_elapsed(item)) {
            if(item->callback != NULL) {
                item->callback();
            }
            scheduler_task_reschedule(item);
        }
        item = item->next;
    }
}


/**
 *  \brief  Adds a new task object to the execution list safely.
 *  \param  object : Task object to be added to list.
 */
static void scheduler_task_add(scheduler_task_t *task)
{
    scheduler_task_t **item = &task_temp;
    
    if(task != NULL) {
        // critical section: add new node
        hal_systick_pause();
        
        if(item != NULL) {
            (*item)->prev = task;
            task->next = *item;
            task->prev = NULL;
        } 
        else {
            task->prev = NULL;
            task->next = NULL;
        }
        
        *item = task;
        hal_systick_resume();
    }
}


/**
 *  \brief  Removes a task object from the execution list safely.
 *  \param  object : Task object to be removed from list.
 */
static void scheduler_task_remove(scheduler_task_t *task)
{
    // begin of queue
    if(task->prev == NULL) {
        task_temp = task->next;
        if(task->next != NULL) {
            task->next->prev = NULL;
        }
    }
    // end of queue
    else if(task->next == NULL) {
        task->prev->next = NULL;
    }
    // middle of queue
    else if(task->prev != NULL && task->next != NULL) {
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }
}


/**
 *  \brief  Reschedules a task for next period, checks if executions
 *          have been missing due to an other task blocking too long.
 *  \param  object : Task object to reschedule.
 */
static void scheduler_task_reschedule(scheduler_task_t *task)
{
    // catch up with delayed executions (skip)
    while((task->elapsed_at += task->period_ms) < tick_count) {
        // delayed execution count!
        // make sure tasks are held short!!
        task->delayed_exec_count++;
    }
}


/**
 *  \brief  Checks if the task needs to be executed (is elapsed).
 *  \param  object : Task object to check.
 */
static bool schedule_is_elapsed(scheduler_task_t *task)
{
    bool retVal = false;
    uint32_t now = tick_count;
    
    // for normal programmed scheduler
    if(now >= task->elapsed_at) {
        retVal = true;
    }
    // handle overflown separately (not shown)
    
    return retVal;
}
