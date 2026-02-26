#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/freeRTOS.H"
#include "freertos/task.h"
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
#include "esp_err.h"

#define LED 2
static uint8_t led_level = 0;
static uint8_t count =0;
static const char *TAG="Arce";

// Inicializar pin digital
esp_err_t init_led(void){
    gpio_reset_pin(LED);  // Reinicia el pin LED
    esp_err_t err = gpio_set_direction(LED, GPIO_MODE_OUTPUT); // Configura el pin como salida
    
    if (err == ESP_OK){
        ESP_LOGI(TAG, "El led se inicializo correctamente %d", LED); // Log de éxito
        ESP_LOGD(TAG, "Debug: init_led() regreso ESP-OK");           // Log de debug
    } else{
        ESP_LOGE(TAG, "Fallo la inicializacion del led");           // Log de error
    }
    return err;
}

// Cambiar estado del LED
esp_err_t blink_led(void){
    ESP_LOGD(TAG, "Debug: parpadeo del, siguiente estado=%u, led_level"); // Debug
    ESP_LOGI(TAG, "El estado del led cambio");  // Log info
    led_level=!led_level;
    return gpio_set_level(LED, led_level); // Cambia el nivel del LED
}

void app_main(void){

    esp_log_level_set(TAG,ESP_LOG_DEBUG);  // Configura el nivel de logs

    ESP_ERROR_CHECK(init_led());           // Inicializa el LED y chequea errores
    while(1)
    {        
        vTaskDelay(pdMS_TO_TICKS(1000));  
        ESP_ERROR_CHECK(blink_led());      // Cambia el LED y chequea errores

        ESP_LOGI(TAG, "Estado del led:%u", led_level); // Muestra el estado actual
        count++;

        if(count>30) count = 0;           // Reinicia contador después de 30

        if(count<10){
            ESP_LOGI(TAG,"LOG DE INFO");   // Log info
        } else if (count<20){
            ESP_LOGW(TAG, "LAG DE WARNING"); // Log warning
        } else {
            ESP_LOGE(TAG,"LOG DE ERROR");    // Log error
        }   
    }
}