#ifndef BUZZER_H
#define BUZZER_H

#include "leds.h"

/* Inicialización del buzzer */
void Buzzer_init(void);

/* Control del sonido */
void Buzzer_on(led_color_t color);
void Buzzer_off(void);
void Buzzer_error_on(void);

#endif