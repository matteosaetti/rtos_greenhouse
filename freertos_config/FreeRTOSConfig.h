#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/* Basic FreeRTOS settings */
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              ( 125000000UL )  // RP2040 main clock
#define configTICK_RATE_HZ              ( 1000 )
#define configMAX_PRIORITIES            ( 5 )
#define configMINIMAL_STACK_SIZE        ( 128 )
#define configTOTAL_HEAP_SIZE           ( 16 * 1024 )
#define configMAX_TASK_NAME_LEN         ( 16 )
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1
#define configUSE_MUTEXES               1
#define configQUEUE_REGISTRY_SIZE       10
#define configCHECK_FOR_STACK_OVERFLOW  2
#define configUSE_COUNTING_SEMAPHORES   1
#define configUSE_APPLICATION_TASK_TAG  0
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/* Hook function related definitions */
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0

/* RP2040 MPU (Cortex-M0+) */
#define configENABLE_MPU                0

/* Software timers */
#define configUSE_TIMERS                1
#define configTIMER_TASK_PRIORITY       ( 2 )
#define configTIMER_QUEUE_LENGTH        10
#define configTIMER_TASK_STACK_DEPTH    ( configMINIMAL_STACK_SIZE * 2 )

#endif /* FREERTOS_CONFIG_H */
