#include "controller.h"

extern QueueHandle_t qSensor;
extern QueueHandle_t qValveCmd[3];
extern SemaphoreHandle_t stateMutex;
extern system_state_t sysState;

#define HUM_THRESHOLD_LOW  40
#define HUM_THRESHOLD_HIGH 60
#define CONTROLLER_PERIOD pdMS_TO_TICKS(PERIOD_CONTROLLER_MS)

void controller_task(void *pv) {
    sensor_msg_t msg;
    TickType_t lastWake = xTaskGetTickCount();

    for(;;) {
        while(xQueueReceive(qSensor, &msg, 0) == pdTRUE) {
            int idx = msg.sensor_id - 1;
            xSemaphoreTake(stateMutex, portMAX_DELAY);
            int old = sysState.humidity[idx];
            sysState.humidity[idx] = msg.humidity;
            xSemaphoreGive(stateMutex);

            bool wantOpen = false;
            xSemaphoreTake(stateMutex, portMAX_DELAY);
            int current = sysState.humidity[idx];
            bool curValve = sysState.valveOn[idx];
            xSemaphoreGive(stateMutex);

            if (current < HUM_THRESHOLD_LOW) wantOpen = true;
            else if (current > HUM_THRESHOLD_HIGH) wantOpen = false;
            else wantOpen = curValve; 

            valve_cmd_t cmd = wantOpen ? CMD_VALVE_OPEN : CMD_VALVE_CLOSE;
            xQueueSend(qValveCmd[idx], &cmd, 0);
        }

        vTaskDelay(CONTROLLER_PERIOD);
    }
}
