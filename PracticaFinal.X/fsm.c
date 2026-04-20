#include "fsm.h"
#include "leds.h"
#include "buzzer.h"
#include "buttons.h"
#include "timers.h"
#include "game.h"
#include "UART1simple.h"
#include "dificultad.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* =========================
 * Estados principales
 * ========================= */
typedef enum {
    STATE_IDLE,
    STATE_INIT_GAME,
    STATE_SHOW_SEQUENCE,
    STATE_WAIT_INPUT,
    STATE_ROUND_TRANSITION,
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
    TIMER_INPUT_FEEDBACK,
    TIMER_ROUND_PAUSE
} timer_owner_t;

/* =========================
 * Configuración
 * ========================= */
#define MAX_SEQUENCE_LEN 10
#define ERROR_SOUND_TICKS 1000   // 1 segundo

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
static bool last_input_correct = false;
static bool error_sound_active = false;
static bool state_entry;

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
 * Inicialización FSM
 * ========================= */
void FSM_init(void) {
    current_state = STATE_IDLE;

    sequence_length = 0;
    seq_index = 0;
    input_index = 0;
    error_sound_active = false;
    state_entry = true;

    timer_running = false;
    timer_owner = TIMER_NONE;
    game_over_msg_sent = false;
    input_feedback_active = false;
    last_input_correct = false;
    last_button = BUTTON_NONE;

    LED_all_off();
    Buzzer_off();

    putsUART("\nSistema listo\n");
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
             * IDLE
             * ========================= */
        case STATE_IDLE:
            if (new_press && button == BUTTON_START) {

                srand(Timer1_getTicks()); // o TMR1, o el contador de ticks
                current_state = STATE_INIT_GAME;
                state_entry = true;
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
            last_input_correct = false;


            putsUART("\nInicio\n");
            current_state = STATE_SHOW_SEQUENCE;
            state_entry = true;
            break;

            /* =========================
             * MOSTRAR SECUENCIA
             * ========================= */
        case STATE_SHOW_SEQUENCE:

            if (show_substate == SHOW_LED_ON) {
                if (!timer_running) {
                    LED_on(sequence[seq_index]);
                    Buzzer_on(sequence[seq_index]);

                    timer_start(dificultad_get_led_on_ticks());
                    timer_owner = TIMER_SHOW_SEQUENCE;
                    timer_running = true;
                }

                if (timer_owner == TIMER_SHOW_SEQUENCE && timer_expired()) {
                    LED_off(sequence[seq_index]);
                    Buzzer_off();

                    timer_start(dificultad_get_led_off_ticks());
                    timer_running = false;
                    show_substate = SHOW_LED_OFF;
                }
            } else if (show_substate == SHOW_LED_OFF) {
                if (timer_owner == TIMER_SHOW_SEQUENCE && timer_expired()) {
                    seq_index++;

                    if (seq_index >= sequence_length) {
                        seq_index = 0;
                        putsUART("\nTu turno\n");
                        current_state = STATE_WAIT_INPUT;
                        state_entry = true;
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

            /* Fin del feedback del botón */
            if (input_feedback_active &&
                    timer_owner == TIMER_INPUT_FEEDBACK &&
                    timer_expired()) {
                LED_off(current_color);
                Buzzer_off();
                input_feedback_active = false;
                timer_owner = TIMER_NONE;

                /* Si era el último botón correcto → transición */
                if (last_input_correct) {
                    last_input_correct = false;

                    if (sequence_length < MAX_SEQUENCE_LEN) {
                        sequence[sequence_length] = get_random_color();
                        sequence_length++;
                    }

                    timer_start(dificultad_get_led_off_ticks());
                    timer_owner = TIMER_ROUND_PAUSE;
                    current_state = STATE_ROUND_TRANSITION;
                    state_entry = true;
                }
            }

            /* Nueva pulsación */
            if (new_press && button_to_color(button, &current_color)) {
                LED_on(current_color);
                Buzzer_on(current_color);

                timer_start(dificultad_get_input_feedback_ticks());
                timer_owner = TIMER_INPUT_FEEDBACK;
                input_feedback_active = true;

                if (current_color == sequence[input_index]) {
                    input_index++;

                    if (input_index >= sequence_length) {
                        /* Último botón correcto */
                        input_index = 0;
                        last_input_correct = true;
                    }
                } else {
                    LED_all_off();
                    Buzzer_off();
                    input_feedback_active = false;
                    timer_owner = TIMER_NONE;
                    current_state = STATE_GAME_OVER;
                    state_entry = true;
                }
            }
            break;

            /* =========================
             * TRANSICIÓN ENTRE RONDAS
             * ========================= */
        case STATE_ROUND_TRANSITION:

            LED_all_off();
            Buzzer_off();

            if (timer_owner == TIMER_ROUND_PAUSE && timer_expired()) {
                seq_index = 0;
                show_substate = SHOW_LED_ON;
                timer_owner = TIMER_NONE;
                current_state = STATE_SHOW_SEQUENCE;
                state_entry = true;
            }
            break;

            /* =========================
             * FIN DEL JUEGO
             * ========================= */
        case STATE_GAME_OVER:

            if (state_entry) {
                LED_all_off();
                Buzzer_error_on();
                putsUART("\r\nError. Fin del juego\r\n");
                putsUART("Pulse START para reiniciar\r\n");

                state_entry = false; // 👈 SOLO UNA VEZ
            }

            if (button == BUTTON_START) {
                current_state = STATE_INIT_GAME;
                state_entry = true;
            }

            // Botones de color → IGNORADOS
            break;
    }
}