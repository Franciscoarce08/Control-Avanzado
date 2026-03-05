#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "encoder.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    encoder_init();

    int pulse_count = 0;

    while (1) {

        vTaskDelay(pdMS_TO_TICKS(SAMPLE_TIME_MS));

        encoder_get_count(&pulse_count);

        float rpm = encoder_calculate_rpm(pulse_count);

        const char *direction = "Detenido";

        if (rpm > 0)
            direction = "Horario";
        else if (rpm < 0)
            direction = "Antihorario";

        ESP_LOGI(TAG,
                 "Conteo: %d | RPM: %.2f | Sentido: %s",
                 pulse_count,
                 rpm,
                 direction);
    }
}