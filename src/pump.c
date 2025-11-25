#include "main.h"

extern SemaphoreHandle_t stateMutex;
extern system_state_t sysState;
TickType_t pumpLastOnTick = 0;
const TickType_t PUMP_MAX_ON_TICKS = pdMS_TO_TICKS(2 * 60 * 1000);

//void update_return_valve_locked(); 

void pump_task(void *pv) {
    gpio_init(PUMP_PIN); gpio_set_dir(PUMP_PIN, GPIO_OUT); gpio_put(PUMP_PIN, 0);

    const TickType_t poll = pdMS_TO_TICKS(200);
    for(;;) {
        xSemaphoreTake(stateMutex, portMAX_DELAY);
        bool anyValve = (sysState.valveOn[0] || sysState.valveOn[1] || sysState.valveOn[2]);

        //Pump ON if any valve open AND safety checks
        bool newPump = false;
        if (anyValve) {
            newPump = true;
            pumpLastOnTick = xTaskGetTickCount();
        }

        sysState.pumpOn = newPump;
        gpio_put(PUMP_PIN, newPump ? 1 : 0);

        //Return valve closed if pump off OR all three plant valves open
        bool mustClose = (!sysState.pumpOn) || (sysState.valveOn[0] && sysState.valveOn[1] && sysState.valveOn[2]);
        sysState.returnValveOn = !mustClose;
        gpio_put(RETURN_PIN, sysState.returnValveOn ? 1 : 0);

        xSemaphoreGive(stateMutex);

        //Pump watchdog
        if (newPump) {
            if ((xTaskGetTickCount() - pumpLastOnTick) > PUMP_MAX_ON_TICKS) {
                xSemaphoreTake(stateMutex, portMAX_DELAY);
                sysState.pumpOn = false;
                xSemaphoreGive(stateMutex);
                gpio_put(PUMP_PIN, 0);
                for(int i=0;i<3;i++){
                    //commands to close
                }
            }
        }

        vTaskDelay(poll);
    }
}
