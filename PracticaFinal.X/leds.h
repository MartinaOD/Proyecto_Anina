#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

/* Enumerado de colores */
typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW
} led_color_t;

/* Inicialización */
void initLEDs(void);

/* Control individual */
void LED_on(led_color_t color);
void LED_off(led_color_t color);

/* Control múltiple */
void LED_all_on(void);
void LED_all_off(void);
void LED_toggle(led_color_t color);

#endif