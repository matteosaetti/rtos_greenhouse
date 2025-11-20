#include "main.h"

extern QueueHandle_t qSensor;
extern SemaphoreHandle_t stateMutex;

static const int adc_channel_offset = 26;

//Hysteresis parameters
#define HYSTERESIS_DELTA 5

//Humidity value in %
static int adc_to_percent(uint16_t v){ return (v * 100) / 4095; }

void sensor_task(void *pv) {
    int id = (int)pv; 
    int gpio = adc_channel_offset + (id - 1);

    TickType_t lastWake = xTaskGetTickCount();
    sensor_msg_t msg;

    for(;;) {
        adc_gpio_init(gpio);
        adc_select_input(gpio - adc_channel_offset);
        uint16_t raw = adc_read();
        int hum = adc_to_percent(raw);

        msg.sensor_id = id;
        msg.humidity = hum;
        msg.timestamp = (uint32_t)millis_from_tick(xTaskGetTickCount());

        //Send to controller
        xQueueSend(qSensor, &msg, 0);

        vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(PERIOD_SENSOR_MS));
    }
}
