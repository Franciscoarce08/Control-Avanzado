Blink LED con Timer — ESP32
 -Descripción

Este proyecto consiste en encender y apagar un LED conectado a un ESP32 utilizando un temporizador por software (timer). El parpadeo del LED se realiza automáticamente a intervalos definidos sin necesidad de usar retardos bloqueantes.

El objetivo es comprender el uso de timers, manejo de GPIO y programación básica en ESP-IDF.

 -Funcionamiento

Se configura un pin GPIO como salida.

Se inicializa un temporizador.

El timer cambia el estado del LED periódicamente.

El LED parpadea de forma continua.