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
static const char *TAG="Mariscal";

//Inicializar pin digital
esp_err_t init_led(void){
    gpio_reset_pin(LED);
    esp_err_t err = gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    return err;
    if (err ==ESP_OK){
        ESP_LOGI(TAG, "El led se inicializo correctamente %d", LED);
        ESP_LOGD(TAG, "Debug: init_led() regreso ESP-OK");
    } else{
        ESP_LOGE(TAG, "Fallo la inicializacion del led");

    }
    return err;
}

esp_err_t blink_led(void){
    ESP_LOGD(TAG, "Debug: parpadeo del, siguiente estado=%u, led_level");
    ESP_LOGI(TAG, "El estado del led cambio");
    return gpio_set_level(LED, led_level);
}

void app_main(void){

    esp_log_level_set(TAG,ESP_LOG_DEBUG);


    ESP_ERROR_CHECK(init_led());
    while(1)
    {        
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_ERROR_CHECK(blink_led());

        ESP_LOGI(TAG, "Estado del led:%u", led_level);
        count++;

        if(count>30) count = 0;

        if(count<10){
            ESP_LOGI(TAG,"LOG DE INFO");
        } else if (count<20){
            ESP_LOGW(TAG, "LAG DE WARNING");
        }else {
            ESP_LOGE(TAG,"LOG DE ERROR");
        }   
    }
}
