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

/**
 * Modified by Engineering Spirit (c) 2012 http://engineering-spirit.nl to provide
 * a more general support to configure the package with the BSP editor.
 *
 * Also fixed support for system clock detection in a more automated way.
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "system.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *----------------------------------------------------------*/

#define SYSTEM_H_CPU_CLOCK_HZ                                   ALT_CPU_FREQ

#define configUSE_PREEMPTION					SYSTEM_H_USE_PREEMPTION
#define configUSE_IDLE_HOOK					SYSTEM_H_USE_IDLE_HOOK
#define configUSE_TICK_HOOK					SYSTEM_H_USE_TICK_HOOK
#define configTICK_RATE_HZ					( ( portTickType ) SYSTEM_H_TICK_RATE_HZ )
#define configCPU_CLOCK_HZ					( ( unsigned long ) SYSTEM_H_CPU_CLOCK_HZ )
#define configMAX_PRIORITIES					SYSTEM_H_MAX_PRIORITIES
#define configMINIMAL_STACK_SIZE				( SYSTEM_H_MINIMAL_STACK_SIZE )
#define configISR_STACK_SIZE					SYSTEM_H_MINIMAL_STACK_SIZE
#define configTOTAL_HEAP_SIZE					( ( size_t ) SYSTEM_H_TOTAL_HEAP_SIZE )
#define configMAX_TASK_NAME_LEN					( SYSTEM_H_MAX_TASK_NAME_LEN )
#define configUSE_TRACE_FACILITY				SYSTEM_H_USE_TRACE_FACILITY
#define configUSE_16_BIT_TICKS					SYSTEM_H_USE_16_BIT_TICKS
#define configIDLE_SHOULD_YIELD					SYSTEM_H_IDLE_SHOULD_YIELD
#define configUSE_MUTEXES					SYSTEM_H_USE_MUTEXES
#define configUSE_RECURSIVE_MUTEXES				SYSTEM_H_USE_RECURSIVE_MUTEXES
#define configUSE_COUNTING_SEMAPHORES				SYSTEM_H_USE_COUNTING_SEMAPHORES
#define configCHECK_FOR_STACK_OVERFLOW				SYSTEM_H_CHECK_FOR_STACK_OVERFLOW
#define configQUEUE_REGISTRY_SIZE				SYSTEM_H_QUEUE_REGISTRY_SIZE
#define configUSE_ALTERNATIVE_API				SYSTEM_H_USE_ALTERNATIVE_API
#define configUSE_MALLOC_FAILED_HOOK				SYSTEM_H_USE_MALLOC_FAILED_HOOK
#define configUSE_STATS_FORMATTING_FUNCTIONS                    SYSTEM_H_USE_STATS_FORMATTING_FUNCTIONS

// Timer settings
#define configUSE_TIMERS                			1
#define configTIMER_TASK_PRIORITY       			SYSTEM_H_TIMER_TASK_PRIORITY
#define configTIMER_QUEUE_LENGTH        			SYSTEM_H_TIMER_QUEUE_LENGTH
#define configTIMER_TASK_STACK_DEPTH    			SYSTEM_H_MINIMAL_STACK_SIZE

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 					SYSTEM_H_USE_CO_ROUTINES
#define configMAX_CO_ROUTINE_PRIORITIES 			SYSTEM_H_MAX_CO_ROUTINE_PRIORITIES

/* Enables the test whereby a stack larger than the total heap size is
requested. */
#define configSTACK_DEPTH_TYPE uint32_t

#define OS_THREAD_SAFE_NEWLIB					SYSTEM_H_THREAD_SAFE_NEWLIB
/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet				SYSTEM_H_VTASKPRIORITYSET
#define INCLUDE_uxTaskPriorityGet				SYSTEM_H_UXTASKPRIORITYGET
#define INCLUDE_vTaskDelete					SYSTEM_H_VTASKDELETE
#define INCLUDE_vTaskCleanUpResources				SYSTEM_H_VTASKCLEANUPRESOURCES
#define INCLUDE_vTaskSuspend					SYSTEM_H_VTASKSUSPEND
#define INCLUDE_vTaskDelayUntil					SYSTEM_H_VTASKDELAYUNTIL
#define INCLUDE_vTaskDelay					SYSTEM_H_VTASKDELAY
#define INCLUDE_uxTaskGetStackHighWaterMark			SYSTEM_H_UXTASKGETSTACKHIGHWATERMARK

/* The priority at which the tick interrupt runs.  This should probably be
kept at 1. */
#define configKERNEL_INTERRUPT_PRIORITY				SYSTEM_H_KERNEL_INTERRUPT_PRIORITY

/* The maximum interrupt priority from which FreeRTOS.org API functions can
be called.  Only API functions that end in ...FromISR() can be used within
interrupts. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY			SYSTEM_H_MAX_SYSCALL_INTERRUPT_PRIORITY

#define CONCAT(a,b)						a ## b

#define SYSTEM_H_CLOCK_BASE(clk)						CONCAT(clk,_BASE)
#define SYSTEM_H_CLOCK_FREQ(clk)						CONCAT(clk,_FREQ)
#define SYSTEM_H_CLOCK_IRQ(clk)							CONCAT(clk,_IRQ)
#define SYSTEM_H_CLOCK_TICKS_PER_SEC(clk)				CONCAT(clk,_TICKS_PER_SEC)
#define SYSTEM_H_CLOCK_IRQ_INTERRUPT_CONTROLLER_ID(clk)	CONCAT(clk,_IRQ_INTERRUPT_CONTROLLER_ID)

#define SYSTEM_H_CLK_BASE								SYSTEM_H_CLOCK_BASE(ALT_SYS_CLK)
#define SYSTEM_H_CLK_FREQ								SYSTEM_H_CLOCK_FREQ(ALT_SYS_CLK)
#define SYSTEM_H_CLK_IRQ								SYSTEM_H_CLOCK_IRQ(ALT_SYS_CLK)
#define SYSTEM_H_CLK_TICKS_PER_SEC						SYSTEM_H_CLOCK_TICKS_PER_SEC(ALT_SYS_CLK)
#define SYSTEM_H_CLK_IRQ_INTERRUPT_CONTROLLER_ID		SYSTEM_H_CLOCK_IRQ_INTERRUPT_CONTROLLER_ID(ALT_SYS_CLK)

#endif /* FREERTOS_CONFIG_H */
