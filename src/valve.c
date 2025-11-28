#include "valve.h"

extern QueueHandle_t qValveCmd[3];
extern SemaphoreHandle_t stateMutex;
extern system_state_t sysState;

void valve_task(void *pv) {
    int id = (int)pv;
    int pin = (id==1) ? VALVE1_PIN : (id==2) ? VALVE2_PIN : VALVE3_PIN;
    valve_cmd_t cmd;

    gpio_init(pin); gpio_set_dir(pin, GPIO_OUT); gpio_put(pin, 0);

    for(;;) {
        if (xQueueReceive(qValveCmd[id-1], &cmd, portMAX_DELAY) == pdTRUE) {
            xSemaphoreTake(stateMutex, portMAX_DELAY);

            if (cmd == CMD_VALVE_OPEN) {
                sysState.valveOn[id-1] = true;
                gpio_put(pin, 1);
            } else {
                sysState.valveOn[id-1] = false;
                gpio_put(pin, 0);
            }

            xSemaphoreGive(stateMutex);
        }
    }
}
