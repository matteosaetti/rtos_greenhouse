#include "main.h"

// Sensors -> controller
QueueHandle_t qSensor;
// Controller -> each valve
QueueHandle_t qValveCmd[3];
// Mutex variable
SemaphoreHandle_t stateMutex;

system_state_t sysState;

// Watchdog
TickType_t pumpLastOnTick = 0;

static inline uint32_t millis_from_tick(TickType_t t) { return (uint32_t)(t * portTICK_PERIOD_MS); }

int main()
{
    stdio_init_all();
    adc_init();

    // Init pins
    gpio_init(PUMP_PIN);
    gpio_set_dir(PUMP_PIN, GPIO_OUT);
    gpio_put(PUMP_PIN, 0);
    gpio_init(VALVE1_PIN);
    gpio_set_dir(VALVE1_PIN, GPIO_OUT);
    gpio_put(VALVE1_PIN, 0);
    gpio_init(VALVE2_PIN);
    gpio_set_dir(VALVE2_PIN, GPIO_OUT);
    gpio_put(VALVE2_PIN, 0);
    gpio_init(VALVE3_PIN);
    gpio_set_dir(VALVE3_PIN, GPIO_OUT);
    gpio_put(VALVE3_PIN, 0);
    gpio_init(RETURN_PIN);
    gpio_set_dir(RETURN_PIN, GPIO_OUT);
    gpio_put(RETURN_PIN, 1);

    qSensor = xQueueCreate(QUEUE_SENSOR_LEN, sizeof(sensor_msg_t));
    for (int i = 0; i < 3; i++)
        qValveCmd[i] = xQueueCreate(QUEUE_CMD_LEN, sizeof(valve_cmd_t));
    stateMutex = xSemaphoreCreateMutex();

    // Init state
    xSemaphoreTake(stateMutex, portMAX_DELAY);
    sysState.pumpOn = false;
    sysState.returnValveOn = true;
    for (int i = 0; i < 3; i++)
    {
        sysState.valveOn[i] = false;
        sysState.humidity[i] = 0;
    }
    xSemaphoreGive(stateMutex);

    // Create tasks
    xTaskCreate(sensor_task, "Sensor1", 256, (void *)1, PRIO_SENSOR, NULL);
    xTaskCreate(sensor_task, "Sensor2", 256, (void *)2, PRIO_SENSOR, NULL);
    xTaskCreate(sensor_task, "Sensor3", 256, (void *)3, PRIO_SENSOR, NULL);

    xTaskCreate(controller_task, "Controller", 512, NULL, PRIO_CONTROLLER, NULL);

    xTaskCreate(valve_task, "Valve1", 256, (void *)1, PRIO_VALVE, NULL);
    xTaskCreate(valve_task, "Valve2", 256, (void *)2, PRIO_VALVE, NULL);
    xTaskCreate(valve_task, "Valve3", 256, (void *)3, PRIO_VALVE, NULL);

    xTaskCreate(pump_task, "Pump", 256, NULL, PRIO_PUMP, NULL);

    vTaskStartScheduler();

    while (1)
        ;
    return 0;
}
