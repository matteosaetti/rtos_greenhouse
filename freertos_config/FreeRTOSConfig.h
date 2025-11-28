#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
#include "pico/unique_id.h"     // Per rp2040 port.c (richiede include di pico)
#include "pico/stdlib.h"

/*-----------------------------------------------------------
 * FreeRTOS specific configuration
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                    1
#define configUSE_TICK_HOOK                     0
#define configUSE_IDLE_HOOK                     0
#define configUSE_MALLOC_FAILED_HOOK            1

#define configCPU_CLOCK_HZ                      ( 125000000UL )
#define configTICK_RATE_HZ                      ( 1000 )
#define configMAX_PRIORITIES                    ( 5 )
#define configMINIMAL_STACK_SIZE                ( 128 )
#define configTOTAL_HEAP_SIZE                   ( 16 * 1024 )   /* 16 KB */
#define configMAX_TASK_NAME_LEN                 ( 16 )
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1

#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_QUEUE_SETS                    0

#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( 2 )
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            ( configMINIMAL_STACK_SIZE * 2 )

#define configCHECK_FOR_STACK_OVERFLOW          2

/*-----------------------------------------------------------
 * Interrupt related definitions
 *----------------------------------------------------------*/

#define configKERNEL_INTERRUPT_PRIORITY        ( 1 << (8 - 2) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY   ( 3 << (8 - 2) )

/* Cortex-M0+ quindi niente basepri */
#define configPRIO_BITS                        2

/*-----------------------------------------------------------
 * Assertion
 *----------------------------------------------------------*/

#define configASSERT(x)                         \
    if((x) == 0) {                              \
        printf("ASSERT FAILED: %s:%d\n", __FILE__, __LINE__); \
        taskDISABLE_INTERRUPTS();               \
        for( ;; );                              \
    }

/*-----------------------------------------------------------
 * Optional functions
 *----------------------------------------------------------*/

#define INCLUDE_vTaskDelay                       1
#define INCLUDE_xTaskDelayUntil                  1
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_vTaskPriorityGet                  1
#define INCLUDE_xTaskGetIdleTaskHandle            1
#define INCLUDE_xTaskGetCurrentTaskHandle         1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskCleanUpResources             0
#define INCLUDE_xTimerPendFunctionCall            1
#define INCLUDE_uxTaskGetStackHighWaterMark       1

/*-----------------------------------------------------------
 * For RP2040 multicore
 *----------------------------------------------------------*/

#define configNUM_CORES                         1

#endif /* FREERTOS_CONFIG_H */
