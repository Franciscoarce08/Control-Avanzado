#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
#include "esp_err.h"
#include "esp_timer.h"

#define LED 2
static uint8_t led_level = 0;
static uint8_t count = 0;
static const char *TAG = "Arce";

// ---------- Inicializar pin ----------
esp_err_t init_led(void){
    gpio_reset_pin(LED);
    esp_err_t err = gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    
    if (err == ESP_OK){
        ESP_LOGI(TAG, "El led se inicializo correctamente %d", LED);
        ESP_LOGD(TAG, "Debug: init_led() regreso ESP_OK");
    } else{
        ESP_LOGE(TAG, "Fallo la inicializacion del led");
    }
    return err;
}

// ---------- Cambiar estado LED ----------
esp_err_t blink_led(void){
    ESP_LOGD(TAG, "Debug: parpadeo, siguiente estado=%u", led_level);
    ESP_LOGI(TAG, "El estado del led cambio");
    led_level = !led_level;
    return gpio_set_level(LED, led_level);
}

// ---------- Callback del Timer ----------
static void timer_callback(void* arg)
{
    ESP_ERROR_CHECK(blink_led());

    ESP_LOGI(TAG, "Estado del led:%u", led_level);
    count++;

    if(count > 30) count = 0;

    if(count < 10){
        ESP_LOGI(TAG,"LOG DE INFO");
    } else if (count < 20){
        ESP_LOGW(TAG, "LOG DE WARNING");
    } else {
        ESP_LOGE(TAG,"LOG DE ERROR");
    }
}

// ---------- Main ----------
void app_main(void){

    esp_log_level_set(TAG, ESP_LOG_DEBUG);

    ESP_ERROR_CHECK(init_led());

    // Configuración del timer periódico
    const esp_timer_create_args_t timer_args = {
        .callback = &timer_callback,
        .name = "led_timer"
    };

    esp_timer_handle_t timer;
    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &timer));

    // Inicia timer cada 1 segundo (1,000,000 us)
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer, 1000000));
}