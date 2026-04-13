#include "fsm.h"
#include "leds.h"
#include "buzzer.h"
#include "buttons.h"
#include "timers.h"
#include "uart.h"
#include "game.h"

#include <stdint.h>
#include <stdbool.h>

/* =========================
 * Estados principales
 * ========================= */
typedef enum {
    STATE_IDLE,
    STATE_INIT_GAME,
    STATE_SHOW_SEQUENCE,
    STATE_WAIT_INPUT,
    STATE_GAME_OVER
} fsm_state_t;

/* =========================
 * Subestados secuencia
 * ========================= */
typedef enum {
    SHOW_LED_ON,
    SHOW_LED_OFF
} show_substate_t;

/* =========================
 * Configuración
 * ========================= */
#define MAX_SEQUENCE_LEN     10
#define LED_ON_TICKS        300
#define LED_OFF_TICKS       200

/* =========================
 * Variables FSM
 * ========================= */
static fsm_state_t current_state;
static show_substate_t show_substate;

static led_color_t sequence[MAX_SEQUENCE_LEN];
static uint8_t sequence_length;
static uint8_t seq_index;
static uint8_t input_index;

static led_color_t current_color;

/* =========================
 * Función auxiliar:
 * Button → LED color
 * ========================= */
static bool button_to_color(button_t button, led_color_t *color) {
    switch (button) {
        case BUTTON_RED:
            *color = RED;
            return true;
        case BUTTON_GREEN:
            *color = GREEN;
            return true;
        case BUTTON_BLUE:
            *color = BLUE;
            return true;
        case BUTTON_YELLOW:
            *color = YELLOW;
            return true;
        default:
            return false;
    }
}

/* =========================
 * Inicialización FSM
 * ========================= */
void FSM_init(void) {
    current_state = STATE_IDLE;

    sequence_length = 0;
    seq_index = 0;
    input_index = 0;

    LED_all_off();
    Buzzer_off();

    uart_print("Sistema listo. Pulse START\r\n");
}

/* =========================
 * Ejecución FSM (tick)
 * ========================= */
void FSM_run(void) {
    button_t button = ButtonsPressed();

    switch (current_state) {
            /* =========================
             * ESTADO IDLE
             * ========================= */
        case STATE_IDLE:
            if (button == BUTTON_START) {
                current_state = STATE_INIT_GAME;
            }
            break;

            /* =========================
             * INICIO DE JUEGO
             * ========================= */
        case STATE_INIT_GAME:
            sequence_length = 1;
            sequence[0] = get_random_color();

            seq_index = 0;
            input_index = 0;

            show_substate = SHOW_LED_ON;

            uart_print("Comienza el juego\r\n");
            current_state = STATE_SHOW_SEQUENCE;
            break;

            /* =========================
             * MOSTRAR SECUENCIA
             * ========================= */
        case STATE_SHOW_SEQUENCE:
            if (show_substate == SHOW_LED_ON) {
                LED_on(sequence[seq_index]);
                Buzzer_on(sequence[seq_index]);

                timer_start(LED_ON_TICKS);
                show_substate = SHOW_LED_OFF;
            } else if (show_substate == SHOW_LED_OFF && timer_expired()) {
                LED_off(sequence[seq_index]);
                Buzzer_off();

                timer_start(LED_OFF_TICKS);
                seq_index++;

                if (seq_index >= sequence_length) {
                    seq_index = 0;
                    current_state = STATE_WAIT_INPUT;
                } else {
                    show_substate = SHOW_LED_ON;
                }
            }
            break;

            /* =========================
             * ESPERA INPUT USUARIO
             * ========================= */
        case STATE_WAIT_INPUT:
            if (button_to_color(button, &current_color)) {
                LED_on(current_color);
                Buzzer_on(current_color);
                timer_start(LED_ON_TICKS);

                if (current_color == sequence[input_index]) {
                    input_index++;

                    if (input_index >= sequence_length) {
                        /* Ronda superada */
                        LED_all_off();
                        Buzzer_off();

                        input_index = 0;
                        seq_index = 0;

                        if (sequence_length < MAX_SEQUENCE_LEN) {
                            sequence[sequence_length] = get_random_color();
                            sequence_length++;
                        }

                        show_substate = SHOW_LED_ON;
                        current_state = STATE_SHOW_SEQUENCE;
                    }
                } else {
                    current_state = STATE_GAME_OVER;
                }
            }
            break;

            /* =========================
             * FIN DE PARTIDA
             * ========================= */
        case STATE_GAME_OVER:
            LED_all_off();
            Buzzer_off();

            uart_print("Error. Fin del juego\r\n");

            if (button == BUTTON_START) {
                current_state = STATE_INIT_GAME;
            }
            break;

        default:
            current_state = STATE_IDLE;
            break;
    }
}