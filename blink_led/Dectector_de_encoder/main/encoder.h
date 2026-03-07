#ifndef ENCODER_H
#define ENCODER_H

#include "driver/pulse_cnt.h"
#include "esp_err.h"

// Pines del encoder
#define ENCODER_GPIO_A      33
#define ENCODER_GPIO_B      25

// Límites del contador
#define ENCODER_PCNT_HIGH_LIMIT   10000
#define ENCODER_PCNT_LOW_LIMIT   -10000

// Resolución del encoder (PPR reales)
#define ENCODER_PPR  400      // ⚠ Cambiar según tu encoder

// Tiempo de muestreo en ms
#define SAMPLE_TIME_MS 1000

esp_err_t encoder_init(void);
esp_err_t encoder_get_count(int *count);
float encoder_calculate_rpm(int current_count);

#endif