#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Raspberry PI Pico pins
#define PUMP_PIN   2
#define VALVE1_PIN 3
#define VALVE2_PIN 4
#define VALVE3_PIN 5
#define RETURN_PIN 6

#define HUM1_PIN   26
#define HUM2_PIN   27
#define HUM3_PIN   28

// Task priorities
#define PRIO_SENSOR (6)
#define PRIO_PUMP (6)
#define PRIO_CONTROLLER (4)
#define PRIO_VALVE (3)
#define PRIO_LOG (1)

// Periods
#define PERIOD_SENSOR_MS 500
#define PERIOD_CONTROLLER_MS 200
#define PERIOD_VALVE_MS 100

#define QUEUE_SENSOR_LEN 8
#define QUEUE_CMD_LEN 8

#define PUMP_MAX_ON_MS 5000
#define MS_TO_TICKS(xTimeInMs) ((TickType_t)((((uint64_t)(xTimeInMs) * (uint64_t)configTICK_RATE_HZ) + 999U) / 1000U))

// Mutex globale
extern SemaphoreHandle_t stateMutex;

typedef enum
{
    CMD_VALVE_OPEN = 1,
    CMD_VALVE_CLOSE
} valve_cmd_t;

// Struct messaggio sensore
typedef struct
{
    int sensor_id;
    float humidity;
    uint32_t timestamp;
} sensor_msg_t;

typedef struct
{
    bool pumpOn;
    bool valveOn[3];
    int humidity[3];
    bool returnValveOn;
} system_state_t;

// Prototipi task
void sensor_task(void *pvParameters);
void controller_task(void *pvParameters);
void valve_task(void *pvParameters);
void pump_task(void *pvParameters);


#endif // MAIN_H
