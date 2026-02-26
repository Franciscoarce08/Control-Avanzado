#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
#include "esp_err.h"

/* ------------------- Configuración ------------------- */
#define GPIO_LED        GPIO_NUM_2
#define INTERVALO_MS    1000

static const char *LOG_TAG = "Control_LED";

/* ------------------- Variables privadas ------------------- */
static bool estado_actual = false;

/* ------------------- Funciones internas ------------------- */

static esp_err_t configurar_salida(gpio_num_t pin)
{
    gpio_config_t config = {
        .pin_bit_mask = (1ULL << pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    esp_err_t resultado = gpio_config(&config);

    if (resultado != ESP_OK) {
        ESP_LOGE(LOG_TAG, "No se pudo configurar el GPIO");
    } else {
        ESP_LOGI(LOG_TAG, "GPIO configurado como salida correctamente");
    }

    return resultado;
}

static esp_err_t actualizar_estado(void)
{
    estado_actual = !estado_actual;

    ESP_LOGD(LOG_TAG, "Nuevo estado lógico: %d", estado_actual);

    esp_err_t resultado = gpio_set_level(GPIO_LED, estado_actual);

    if (resultado == ESP_OK) {
        ESP_LOGI(LOG_TAG, "LED %s",
                 estado_actual ? "ENCENDIDO" : "APAGADO");
    } else {
        ESP_LOGW(LOG_TAG, "Fallo al escribir en el pin");
    }

    return resultado;
}

/* ------------------- Aplicación principal ------------------- */

void app_main(void)
{
    // Selección del nivel de log
    esp_log_level_set(LOG_TAG, ESP_LOG_INFO);

    ESP_ERROR_CHECK(configurar_salida(GPIO_LED));

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(INTERVALO_MS));
        ESP_ERROR_CHECK(actualizar_estado());
    }
}