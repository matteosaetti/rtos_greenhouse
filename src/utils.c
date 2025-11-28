#include "utils.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    (void)xTask;
    (void)pcTaskName;
    while(1); 
}

void vApplicationMallocFailedHook(void) {
    while(1); 
}

uint32_t millis_from_tick(TickType_t t)
{
    return (t * 1000) / configTICK_RATE_HZ;
}