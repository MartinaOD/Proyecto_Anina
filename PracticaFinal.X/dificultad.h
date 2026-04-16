#ifndef DIFICULTAD_H
#define DIFICULTAD_H

#include <stdint.h>
/*
typedef struct {
    uint16_t led_on_ticks;
    uint16_t led_off_ticks;
    uint16_t input_feedback_ticks;
} game_speed_t;

// Variable global de velocidad
extern game_speed_t game_speed;
*/

/* Configura la dificultad a partir de un carácter recibido por UART */
void dificultad_configurar(char nivel);

uint16_t dificultad_get_led_on_ticks(void);
uint16_t dificultad_get_led_off_ticks(void);
uint16_t dificultad_get_input_feedback_ticks(void);


#endif