#include "fsm.h"
#include "leds.h"
#include "buzzer.h"
#include "buttons.h"
#include "timers.h"
#include "game.h"
#include "UART1simple.h"

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
 * Propietario del temporizador
 * ========================= */
typedef enum {
    TIMER_NONE,
    TIMER_SHOW_SEQUENCE,
    TIMER_INPUT_FEEDBACK
} timer_owner_t;

/* =========================
 * Configuración
 * ========================= */
#define MAX_SEQUENCE_LEN        10
#define LED_ON_TICKS           300
#define LED_OFF_TICKS          200
#define INPUT_FEEDBACK_TICKS   150   // Feedback al pulsar botones

/* =========================
 * Variables FSM
 * ========================= */
static fsm_state_t current_state;
static show_substate_t show_substate;
static timer_owner_t timer_owner;

static led_color_t sequence[MAX_SEQUENCE_LEN];
static uint8_t sequence_length;
static uint8_t seq_index;
static uint8_t input_index;

static led_color_t current_color;

/* Flags */
static bool timer_running = false;
static bool game_over_msg_sent = false;
static bool input_feedback_active = false;

/* Control flanco botones */
static button_t last_button = BUTTON_NONE;

/* =========================
 * Button → LED color
 * ========================= */
static bool button_to_color(button_t button, led_color_t *color) {
    switch (button) {
        case BUTTON_RED: *color = RED;
            return true;
        case BUTTON_GREEN: *color = GREEN;
            return true;
        case BUTTON_BLUE: *color = BLUE;
            return true;
        case BUTTON_YELLOW: *color = YELLOW;
            return true;
        default: return false;
    }
}

/* =========================
 * UART: imprimir color
 * ========================= */
static void uart_print_color(led_color_t color) {
    switch (color) {
        case RED: putsUART("ROJO ");
            break;
        case GREEN: putsUART("VERDE ");
            break;
        case BLUE: putsUART("AZUL ");
            break;
        case YELLOW: putsUART("AMARILLO ");
            break;
        default: break;
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

    timer_running = false;
    timer_owner = TIMER_NONE;
    game_over_msg_sent = false;
    input_feedback_active = false;
    last_button = BUTTON_NONE;

    LED_all_off();
    Buzzer_off();

    putsUART("\r\nSistema listo. Pulse START\r\n");
}

/* =========================
 * FSM run (tick)
 * ========================= */
void FSM_run(void) {
    button_t button = ButtonsPressed();
    bool new_press = (button != BUTTON_NONE && button != last_button);
    last_button = button;

    switch (current_state) {
            /* =========================
             * ESTADO IDLE
             * ========================= */
        case STATE_IDLE:
            if (new_press && button == BUTTON_START) {
                srand(Timer1_getTicks()); // o TMR1
                current_state = STATE_INIT_GAME;
            }
            break;

            /* =========================
             * INICIO DE PARTIDA
             * ========================= */
        case STATE_INIT_GAME:
            sequence_length = 1;
            sequence[0] = get_random_color();

            seq_index = 0;
            input_index = 0;

            show_substate = SHOW_LED_ON;
            timer_running = false;
            timer_owner = TIMER_NONE;
            game_over_msg_sent = false;
            input_feedback_active = false;

            putsUART("\r\nComienza el juego\r\n");
            putsUART("Secuencia inicial: ");
            uart_print_color(sequence[0]);
            putsUART("\r\n");

            current_state = STATE_SHOW_SEQUENCE;
            break;

            /* =========================
             * MOSTRAR SECUENCIA
             * ========================= */
        case STATE_SHOW_SEQUENCE:

            if (show_substate == SHOW_LED_ON) {
                if (!timer_running) {
                    /* 🔴 Mostrar color: LED + BUZZER */
                    LED_on(sequence[seq_index]);
                    Buzzer_on(sequence[seq_index]);

                    timer_start(LED_ON_TICKS);
                    timer_owner = TIMER_SHOW_SEQUENCE;
                    timer_running = true;
                }

                /* Tiempo de LED encendido agotado */
                if (timer_owner == TIMER_SHOW_SEQUENCE && timer_expired()) {
                    LED_off(sequence[seq_index]);
                    Buzzer_off();

                    timer_start(LED_OFF_TICKS);
                    timer_running = false;
                    show_substate = SHOW_LED_OFF;
                }
            } else if (show_substate == SHOW_LED_OFF) {
                /* Tiempo de pausa entre colores agotado */
                if (timer_owner == TIMER_SHOW_SEQUENCE && timer_expired()) {
                    seq_index++;

                    if (seq_index >= sequence_length) {
                        seq_index = 0;
                        putsUART("Introduzca secuencia:\r\n");
                        current_state = STATE_WAIT_INPUT;
                    } else {
                        show_substate = SHOW_LED_ON;
                    }
                }
            }
            break;

            /* =========================
             * ENTRADA USUARIO
             * ========================= */
        case STATE_WAIT_INPUT:

            /* Apagar feedback visual/sonoro tras el tiempo */
            if (input_feedback_active &&
                    timer_owner == TIMER_INPUT_FEEDBACK &&
                    timer_expired()) {
                LED_off(current_color);
                Buzzer_off();
                input_feedback_active = false;
                timer_owner = TIMER_NONE;
            }

            /* Nueva pulsación del usuario */
            if (new_press && button_to_color(button, &current_color)) {
                /* Mostrar pulsación por UART */
                putsUART("Pulsado: ");
                uart_print_color(current_color);
                putsUART("\r\n");

                /* 🔊 FEEDBACK: LED + BUZZER según el color pulsado */
                LED_on(current_color);
                Buzzer_on(current_color);

                timer_start(INPUT_FEEDBACK_TICKS);
                timer_owner = TIMER_INPUT_FEEDBACK;
                input_feedback_active = true;

                /* Comprobación de la secuencia */
                if (current_color == sequence[input_index]) {
                    input_index++;

                    if (input_index >= sequence_length) {
                        /* Ronda superada */
                        input_index = 0;
                        seq_index = 0;

                        if (sequence_length < MAX_SEQUENCE_LEN) {
                            sequence[sequence_length] = get_random_color();
                            sequence_length++;
                        }

                        putsUART("Nueva secuencia: ");
                        for (uint8_t i = 0; i < sequence_length; i++) {
                            uart_print_color(sequence[i]);
                        }
                        putsUART("\r\n");

                        show_substate = SHOW_LED_ON;
                        timer_running = false;
                        timer_owner = TIMER_NONE;
                        input_feedback_active = false;
                        current_state = STATE_SHOW_SEQUENCE;
                    }
                } else {
                    /* Error → fin del juego */
                    LED_all_off();
                    Buzzer_off();
                    input_feedback_active = false;
                    timer_owner = TIMER_NONE;
                    current_state = STATE_GAME_OVER;
                }
            }
            break;


            /* =========================
             * FIN DEL JUEGO
             * ========================= */
        case STATE_GAME_OVER:

            LED_all_off();
            Buzzer_off();

            if (!game_over_msg_sent) {
                putsUART("\r\nError. Fin del juego\r\n");
                putsUART("Pulse START para reiniciar\r\n");
                game_over_msg_sent = true;
            }

            if (new_press && button == BUTTON_START) {
                game_over_msg_sent = false;
                current_state = STATE_INIT_GAME;
            }
            break;

        default:
            current_state = STATE_IDLE;
            break;
    }
}