 Blink LED con ESP32

##  Descripción

Este proyecto consiste en el control de un LED utilizando un microcontrolador ESP32 y el framework ESP-IDF.  
El programa configura un pin digital como salida y hace que el LED parpadee encendiéndose y apagándose cada segundo.

Esta práctica permite comprender el manejo básico de GPIO en sistemas embebidos.


## Requisitos

- Tarjeta ESP32
- Cable USB
- ESP-IDF instalado
- Visual Studio Code 

##  Funcionamiento

El programa realiza las siguientes acciones:

1. Inicializa el pin GPIO como salida digital
2. Enciende el LED
3. Espera 1 segundo
4. Apaga el LED
5. Repite el proceso indefinidamente

##  Compilación y carga

Desde la terminal de ESP-IDF:

```bash
idf.py build
idf.py flash
idf.py monitor