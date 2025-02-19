/*
    FreeRTOS V7.1.0 - Copyright (C) 2011 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/*
 * Creates all the demo application tasks, then starts the scheduler.
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Check" task -  This only executes every five seconds but has the highest
 * priority so is guaranteed to get processor time.  Its main function is to
 * check that all the standard demo tasks are still operational.  The check
 * task will write an error message to the console should an error be detected
 * within any of the demo tasks.  The check task also toggles the LED defined
 * by mainCHECK_LED every 5 seconds while the system is error free, with the
 * toggle rate increasing to every 500ms should an error occur.
 *
 * "Reg test" tasks - These fill the registers with known values, then check
 * that each register still contains its expected value.  Each task uses
 * different values.  The tasks run with very low priority so get preempted very
 * frequently.  A register containing an unexpected value is indicative of an
 * error in the context switching mechanism.
 *
 * See the online documentation for this demo for more information on interrupt
 * usage.
 */

/* Standard includes. */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

/* Demo application includes. */
#include "partest.h"
#include "blocktim.h"
#include "semtest.h"
#include "serial.h"
#include "GenQTest.h"
#include "QPeek.h"
#include "integer.h"
#include "PollQ.h"
#include "BlockQ.h"
#include "dynamic.h"
#include "countsem.h"
#include "recmutex.h"
#include "death.h"

#include <arch/cc.h>

/*-----------------------------------------------------------*/

#define FREERTOS_DEMOS_TASKS    0

/* The rate at which the LED controlled by the 'check' task will toggle when no
errors have been detected. */
#define mainNO_ERROR_PERIOD	( 5000 )

/* The rate at which the LED controlled by the 'check' task will toggle when an
error has been detected. */
#define mainERROR_PERIOD 	( 500 )

/* Priority definitions for the tasks in the demo application. */
#define mainLED_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define mainCREATOR_TASK_PRIORITY	( tskIDLE_PRIORITY + 3 )
#define mainCHECK_TASK_PRIORITY		( tskIDLE_PRIORITY + 4 )
#define mainQUEUE_POLL_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_BLOCK_PRIORITY	( tskIDLE_PRIORITY + 3 )
#define mainCOM_TEST_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define mainSEMAPHORE_TASK_PRIORITY	( tskIDLE_PRIORITY + 1 )
#define mainGENERIC_QUEUE_PRIORITY	( tskIDLE_PRIORITY )
#define mainREG_TEST_PRIORITY           ( tskIDLE_PRIORITY )

/* Misc. */
#define mainDONT_WAIT						( 0 )

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Function prototypes, because i'm to lazy to create a header file...
 */

extern void xEthernetRun(void* param);
extern void prvMySocketTest(void *params);

#ifdef __cplusplus
}
#endif

void vApplicationStackOverflowHook(__unused TaskHandle_t xTask, char *pcTaskName )
{
	printf("[free_rtos] Application stack overflow at task: %s\n", pcTaskName);
}

void vApplicationMallocFailedHook(void)
{
	printf("[free_rtos] Malloc Failed\n");
}

void _general_exception_handler( unsigned long ulCause, unsigned long ulStatus )
{
	/* This overrides the definition provided by the kernel.  Other exceptions
	should be handled here. */
	for( ;; )
    {
		asm( "break" );
    }
}
/*-----------------------------------------------------------*/
#if FREERTOS_DEMOS_TASKS

// Counters that are incremented on each iteration of the RegTest tasks
// so long as no errors have been detected.
volatile unsigned long ulRegTest1Counter = 0UL, ulRegTest2Counter = 0UL;

// The parameters passed to the reg test tasks.  This is just done to check
// the parameter passing mechanism is working correctly.
#define mainREG_TEST_1_PARAMETER    ( ( void * ) 0x12345678 )
#define mainREG_TEST_2_PARAMETER    ( ( void * ) 0x87654321 )

// Execute all of the check functions to ensure the tests haven't failed.

static void prvCheckTask( void *pvParameters );


// The register test (or RegTest) tasks as described at the top of this file.

static void prvFirstRegTestTask( void *pvParameters );
static void prvSecondRegTestTask( void *pvParameters );

static void prvCheckTask( void *pvParameters )
{
portTickType xLastExecutionTime, ulTicksToWait = mainNO_ERROR_PERIOD;
unsigned long ulLastRegTest1 = 0UL, ulLastRegTest2 = 0UL;
const char * pcMessage;

	/* Initialise the variable used to control our iteration rate prior to
	its first use. */
	xLastExecutionTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Wait until it is time to run the tests again. */
		vTaskDelayUntil( &xLastExecutionTime, ulTicksToWait );

		/* Have any of the standard demo tasks detected an error in their
		operation? */
		if( xAreIntegerMathsTaskStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Integer Maths.\n";
		}
		else if( xAreGenericQueueTasksStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: GenQ.\n";
		}
		else if( xAreBlockingQueuesStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: BlockQ.\n";
		}
		else if( xArePollingQueuesStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: PollQ.\n";
		}
		else if( xAreQueuePeekTasksStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: PeekQ.\n";
		}
		else if( xAreBlockTimeTestTasksStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Block Time.\n";
		}
		else if( xAreSemaphoreTasksStillRunning() != pdTRUE )
	    {
	        ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Semaphore Test.\n";
	    }
		else if( xIsCreateTaskStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Suicidal Tasks.\n";
		}
		else if( xAreDynamicPriorityTasksStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Dynamic Priority.\n";
		}
		else if( xAreCountingSemaphoreTasksStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Count Semaphore.\n";
		}
		else if( xAreRecursiveMutexTasksStillRunning() != pdTRUE )
		{
			ulTicksToWait = mainERROR_PERIOD;
			pcMessage = "Error: Recursive Mutex.\n";
		}
        else if( ulLastRegTest1 == ulRegTest1Counter )
        {
            /* ulRegTest1Counter is no longer being incremented, indicating
            that an error has been discovered in prvFirstRegTestTask(). */
            ulTicksToWait = mainERROR_PERIOD;
            pcMessage = "Error: Reg Test1.\n";
        }
        else if( ulLastRegTest2 == ulRegTest2Counter )
        {
            /* ulRegTest2Counter is no longer being incremented, indicating
            that an error has been discovered in prvSecondRegTestTask(). */
            ulTicksToWait = mainERROR_PERIOD;
            pcMessage = "Error: Reg Test2.\n";
        }
		else
		{
			pcMessage = NULL;
		}

        /* Remember the counter values this time around so a counter failing
        to be incremented correctly can be spotted. */
        ulLastRegTest1 = ulRegTest1Counter;
        ulLastRegTest2 = ulRegTest2Counter;

        /* Print out an error message if there is one.  Mutual exclusion is
        not used as this is the only task accessing stdout. */
        if( pcMessage != NULL )
        {
            printf( pcMessage );
        }
	}
}
/*-----------------------------------------------------------*/

static void prvFirstRegTestTask( void *pvParameters )
{
    /* Check the parameters are passed in as expected. */
    if( pvParameters != mainREG_TEST_1_PARAMETER )
    {
        /* Don't execute any further so an error is recognised by the check
        task. */
        vTaskDelete( NULL );
    }

    /* Fill registers with known values, then check that each register still
    contains its expected value.  An incorrect value is indicative of an error
    in the context switching process.

    If no errors are found ulRegTest1Counter is incremented.  The check task
    will recognise an error if ulRegTest1Counter stops being incremented.
    This task also performs a manual yield in the middle of its execution, just
    to increase the test coverage. */
    asm volatile (
        "   .extern ulRegTest1Counter           \n" \
        "                                       \n" \
        "   addi    r3, r0, 3                   \n" \
        "   addi    r4, r0, 4                   \n" \
        "   addi    r5, r0, 5                   \n" \
        "   addi    r6, r0, 6                   \n" \
        "   addi    r7, r0, 7                   \n" \
        "   addi    r8, r0, 8                   \n" \
        "   addi    r9, r0, 9                   \n" \
        "   addi    r10, r0, 10                   \n" \
        "   addi    r11, r0, 11                   \n" \
        "   addi    r12, r0, 12                   \n" \
        "   addi    r13, r0, 13                   \n" \
        "   addi    r14, r0, 14                   \n" \
        "   addi    r15, r0, 15                   \n" \
        "   addi    r16, r0, 16                   \n" \
        "   addi    r17, r0, 17                   \n" \
        "   addi    r18, r0, 18                   \n" \
        "   addi    r19, r0, 19                   \n" \
        "   addi    r20, r0, 20                   \n" \
        "   addi    r21, r0, 21                   \n" \
        "   addi    r22, r0, 22                   \n" \
        "   addi    r23, r0, 23                   \n" \
        "   addi    r28, r0, 28                   \n" \
        "   addi    r31, r0, 31                   \n" \
        "RegTest1:                              \n" \
        "   addi    r2, r0, 0                   \n" \
        "   trap                                \n" \
        "   bne     r2, r0, RegTest1Error       \n" \
        "   addi    r2, r0, 3                   \n" \
        "   bne     r2, r3, RegTest1Error       \n" \
        "   addi    r2, r0, 4                   \n" \
        "   bne     r2, r4, RegTest1Error       \n" \
        "   addi    r2, r0, 5                   \n" \
        "   bne     r2, r5, RegTest1Error       \n" \
        "   addi    r2, r0, 6                   \n" \
        "   bne     r2, r6, RegTest1Error       \n" \
        "   addi    r2, r0, 7                   \n" \
        "   bne     r2, r7, RegTest1Error       \n" \
        "   addi    r2, r0, 8                   \n" \
        "   bne     r2, r8, RegTest1Error       \n" \
        "   addi    r2, r0, 9                   \n" \
        "   bne     r2, r9, RegTest1Error       \n" \
        "   addi    r2, r0, 10                   \n" \
        "   bne     r2, r10, RegTest1Error       \n" \
        "   addi    r2, r0, 11                   \n" \
        "   bne     r2, r11, RegTest1Error       \n" \
        "   addi    r2, r0, 12                   \n" \
        "   bne     r2, r12, RegTest1Error       \n" \
        "   addi    r2, r0, 13                   \n" \
        "   bne     r2, r13, RegTest1Error       \n" \
        "   addi    r2, r0, 14                   \n" \
        "   bne     r2, r14, RegTest1Error       \n" \
        "   addi    r2, r0, 15                   \n" \
        "   bne     r2, r15, RegTest1Error       \n" \
        "   addi    r2, r0, 16                   \n" \
        "   bne     r2, r16, RegTest1Error       \n" \
        "   addi    r2, r0, 17                   \n" \
        "   bne     r2, r17, RegTest1Error       \n" \
        "   addi    r2, r0, 18                   \n" \
        "   bne     r2, r18, RegTest1Error       \n" \
        "   addi    r2, r0, 19                   \n" \
        "   bne     r2, r19, RegTest1Error       \n" \
        "   addi    r2, r0, 20                   \n" \
        "   bne     r2, r20, RegTest1Error       \n" \
        "   addi    r2, r0, 21                   \n" \
        "   bne     r2, r21, RegTest1Error       \n" \
        "   addi    r2, r0, 22                   \n" \
        "   bne     r2, r22, RegTest1Error       \n" \
        "   addi    r2, r0, 23                   \n" \
        "   bne     r2, r23, RegTest1Error       \n" \
        "   addi    r2, r0, 28                   \n" \
        "   bne     r2, r28, RegTest1Error       \n" \
        "   addi    r2, r0, 31                   \n" \
        "   bne     r2, r31, RegTest1Error       \n" \
        "   ldw     r2, %gprel(ulRegTest1Counter)(gp)       \n" \
        "   addi    r2, r2, 1                   \n" \
        "   stw     r2, %gprel(ulRegTest1Counter)(gp)       \n" \
        "   br      RegTest1                    \n" \
        "RegTest1Error:                         \n" \
        "   br      RegTest1Error               \n"
    );
}
/*-----------------------------------------------------------*/

static void prvSecondRegTestTask( void *pvParameters )
{
    /* Check the parameters are passed in as expected. */
    if( pvParameters != mainREG_TEST_2_PARAMETER )
    {
        /* Don't execute any further so an error is recognised by the check
        task. */
        vTaskDelete( NULL );
    }

    /* Fill registers with known values, then check that each register still
    contains its expected value.  An incorrect value is indicative of an error
    in the context switching process.

    If no errors are found ulRegTest2Counter is incremented.  The check task
    will recognise an error if ulRegTest2Counter stops being incremented. */
    asm volatile (
        "   .extern ulRegTest2Counter           \n" \
        "                                       \n" \
        "   addi    r3, r0, 3                   \n" \
        "   addi    r4, r0, 4                   \n" \
        "   addi    r5, r0, 5                   \n" \
        "   addi    r6, r0, 6                   \n" \
        "   addi    r7, r0, 7                   \n" \
        "   addi    r8, r0, 8                   \n" \
        "   addi    r9, r0, 9                   \n" \
        "   addi    r10, r0, 10                   \n" \
        "   addi    r11, r0, 11                   \n" \
        "   addi    r12, r0, 12                   \n" \
        "   addi    r13, r0, 13                   \n" \
        "   addi    r14, r0, 14                   \n" \
        "   addi    r15, r0, 15                   \n" \
        "   addi    r16, r0, 16                   \n" \
        "   addi    r17, r0, 17                   \n" \
        "   addi    r18, r0, 18                   \n" \
        "   addi    r19, r0, 19                   \n" \
        "   addi    r20, r0, 20                   \n" \
        "   addi    r21, r0, 21                   \n" \
        "   addi    r22, r0, 22                   \n" \
        "   addi    r23, r0, 23                   \n" \
        "   addi    r28, r0, 28                   \n" \
        "   addi    r31, r0, 31                   \n" \
        "RegTest2:                              \n" \
        "   addi    r2, r0, 0                   \n" \
        "   bne     r2, r0, RegTest2Error       \n" \
        "   addi    r2, r0, 3                   \n" \
        "   bne     r2, r3, RegTest2Error       \n" \
        "   addi    r2, r0, 4                   \n" \
        "   bne     r2, r4, RegTest2Error       \n" \
        "   addi    r2, r0, 5                   \n" \
        "   bne     r2, r5, RegTest2Error       \n" \
        "   addi    r2, r0, 6                   \n" \
        "   bne     r2, r6, RegTest2Error       \n" \
        "   addi    r2, r0, 7                   \n" \
        "   bne     r2, r7, RegTest2Error       \n" \
        "   addi    r2, r0, 8                   \n" \
        "   bne     r2, r8, RegTest2Error       \n" \
        "   addi    r2, r0, 9                   \n" \
        "   bne     r2, r9, RegTest2Error       \n" \
        "   addi    r2, r0, 10                   \n" \
        "   bne     r2, r10, RegTest2Error       \n" \
        "   addi    r2, r0, 11                   \n" \
        "   bne     r2, r11, RegTest2Error       \n" \
        "   addi    r2, r0, 12                   \n" \
        "   bne     r2, r12, RegTest2Error       \n" \
        "   addi    r2, r0, 13                   \n" \
        "   bne     r2, r13, RegTest2Error       \n" \
        "   addi    r2, r0, 14                   \n" \
        "   bne     r2, r14, RegTest2Error       \n" \
        "   addi    r2, r0, 15                   \n" \
        "   bne     r2, r15, RegTest2Error       \n" \
        "   addi    r2, r0, 16                   \n" \
        "   bne     r2, r16, RegTest2Error       \n" \
        "   addi    r2, r0, 17                   \n" \
        "   bne     r2, r17, RegTest2Error       \n" \
        "   addi    r2, r0, 18                   \n" \
        "   bne     r2, r18, RegTest2Error       \n" \
        "   addi    r2, r0, 19                   \n" \
        "   bne     r2, r19, RegTest2Error       \n" \
        "   addi    r2, r0, 20                   \n" \
        "   bne     r2, r20, RegTest2Error       \n" \
        "   addi    r2, r0, 21                   \n" \
        "   bne     r2, r21, RegTest2Error       \n" \
        "   addi    r2, r0, 22                   \n" \
        "   bne     r2, r22, RegTest2Error       \n" \
        "   addi    r2, r0, 23                   \n" \
        "   bne     r2, r23, RegTest2Error       \n" \
        "   addi    r2, r0, 28                   \n" \
        "   bne     r2, r28, RegTest2Error       \n" \
        "   addi    r2, r0, 31                   \n" \
        "   bne     r2, r31, RegTest2Error       \n" \
        "   ldw     r2, %gprel(ulRegTest2Counter)(gp)       \n" \
        "   addi    r2, r2, 1                   \n" \
        "   stw     r2, %gprel(ulRegTest2Counter)(gp)       \n" \
        "   br      RegTest2                    \n" \
        "RegTest2Error:                         \n" \
        "   br      RegTest2Error               \n"
    );
}
/*-----------------------------------------------------------*/

#endif

int main( void )
{
        #if FREERTOS_DEMOS_TASKS
            // Create all the other standard demo tasks.  These serve no purpose other
            // than to test the port and demonstrate the use of the FreeRTOS API.
            vStartIntegerMathTasks( mainGENERIC_QUEUE_PRIORITY );
            vStartPolledQueueTasks( mainQUEUE_POLL_PRIORITY );
            vStartBlockingQueueTasks( mainQUEUE_BLOCK_PRIORITY );
            vCreateBlockTimeTasks();
            vStartSemaphoreTasks( mainSEMAPHORE_TASK_PRIORITY );
            vStartDynamicPriorityTasks();
            vStartQueuePeekTasks();
            vStartGenericQueueTasks( mainGENERIC_QUEUE_PRIORITY );
            vStartCountingSemaphoreTasks();
            vStartRecursiveMutexTasks();

            // prvCheckTask uses sprintf so requires more stack.
            xTaskCreate( prvCheckTask, "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );

            // The RegTest tasks as described at the top of this file.
            xTaskCreate( prvFirstRegTestTask, "Rreg1", configMINIMAL_STACK_SIZE, mainREG_TEST_1_PARAMETER, mainREG_TEST_PRIORITY, NULL );
            xTaskCreate( prvSecondRegTestTask, "Rreg2", configMINIMAL_STACK_SIZE, mainREG_TEST_2_PARAMETER, mainREG_TEST_PRIORITY, NULL );
        #endif
        /* start the network task to start the network */
        xTaskCreate( xEthernetRun, "eth0", KB(4), NULL, mainQUEUE_POLL_PRIORITY, NULL);

        /* This task has to be created last as it keeps account of the number of tasks
        it expects to see running. */
        #if FREERTOS_DEMOS_TASKS
        vCreateSuicidalTasks( mainCREATOR_TASK_PRIORITY );
        #endif
        /* Finally start the scheduler. */
        vTaskStartScheduler();

        /* Will only reach here if there is insufficient heap available to start
        the scheduler. */
        for( ;; );
}
