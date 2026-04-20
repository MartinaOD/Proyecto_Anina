#include <xc.h>
#include <stdint.h>

#include "dificultad.h"
#include "UART1simple.h"

static uint16_t led_on_ticks;
static uint16_t led_off_ticks;
static uint16_t input_feedback_ticks;


/* Traduce el nivel a tiempos concretos */
void dificultad_configurar(char nivel)
{
    switch (nivel) {
        case '1':
            led_on_ticks = 450;
            led_off_ticks = 300;
            input_feedback_ticks = 220;
            break;

        case '2': // El de base, el normal
            led_on_ticks = 300;
            led_off_ticks = 200;
            input_feedback_ticks = 150;
            break;

        case '3':
            led_on_ticks = 200;
            led_off_ticks = 120;
            input_feedback_ticks = 100;
            break;

        default: // En caso de fallo, mantenemos la velocidad normal
            led_on_ticks = 300;
            led_off_ticks = 200;
            input_feedback_ticks = 150;
            break;
    }
}

// Getters para usar en la máquina de estados (fsm.c):
uint16_t dificultad_get_led_on_ticks(void){
    return led_on_ticks;
}

uint16_t dificultad_get_led_off_ticks(void){
    return led_off_ticks;
}

uint16_t dificultad_get_input_feedback_ticks(void){
    return input_feedback_ticks;
}
