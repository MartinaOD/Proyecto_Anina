#include "leds.h"
#include <xc.h>

/* Definición de pines */
#define PIN_LEDRED     6   // RC6
#define PIN_LEDGREEN  7   // RC7
#define PIN_LEDBLUE   8   // RC8
#define PIN_LEDYELLOW 9   // RC9

/* =========================
 * Inicialización de LEDs
 * ========================= */
void initLEDs(void) {
    /* Configurar pines como salida */
    TRISC &= ~(1 << PIN_LEDRED);
    TRISC &= ~(1 << PIN_LEDGREEN);
    TRISC &= ~(1 << PIN_LEDBLUE);
    TRISC &= ~(1 << PIN_LEDYELLOW);

    /* Apagar todos los LEDs */
    LED_all_off();
}

/* =========================
 * Control individual ON
 * ========================= */
void LED_off(led_color_t color) {
    switch (color) {
        case RED:
            LATC |= (1 << PIN_LEDRED);
            break;

        case GREEN:
            LATC |= (1 << PIN_LEDGREEN);
            break;

        case BLUE:
            LATC |= (1 << PIN_LEDBLUE);
            break;

        case YELLOW:
            LATC |= (1 << PIN_LEDYELLOW);
            break;

        default:
            break;
    }
}

/* =========================
 * Control individual OFF
 * ========================= */
void LED_on(led_color_t color) {
    switch (color) {
        case RED:
            LATC &= ~(1 << PIN_LEDRED);
            break;

        case GREEN:
            LATC &= ~(1 << PIN_LEDGREEN);
            break;

        case BLUE:
            LATC &= ~(1 << PIN_LEDBLUE);
            break;

        case YELLOW:
            LATC &= ~(1 << PIN_LEDYELLOW);
            break;

        default:
            break;
    }
}

/* =========================
 * Encender todos los LEDs
 * ========================= */
void LED_all_off(void) {
    LATC |= (1 << PIN_LEDRED);
    LATC |= (1 << PIN_LEDGREEN);
    LATC |= (1 << PIN_LEDBLUE);
    LATC |= (1 << PIN_LEDYELLOW);
}

/* =========================
 * Apagar todos los LEDs
 * ========================= */
void LED_all_on(void) {
    LATC &= ~(1 << PIN_LEDRED);
    LATC &= ~(1 << PIN_LEDGREEN);
    LATC &= ~(1 << PIN_LEDBLUE);
    LATC &= ~(1 << PIN_LEDYELLOW);
}

/* =========================
 * Toggle LED 
 * ========================= */
void LED_toggle(led_color_t color) {
    switch (color) {
        case RED:
            LATC ^= (1 << PIN_LEDRED);
            break;

        case GREEN:
            LATC ^= (1 << PIN_LEDGREEN);
            break;

        case BLUE:
            LATC ^= (1 << PIN_LEDBLUE);
            break;

        case YELLOW:
            LATC ^= (1 << PIN_LEDYELLOW);
            break;

        default:
            break;
    }
}