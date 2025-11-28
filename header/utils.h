#ifndef UTILS_H
#define UTILS_H
#pragma once
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

uint32_t millis_from_tick(TickType_t t);
void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);

#endif