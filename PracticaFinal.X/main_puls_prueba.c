#include <xc.h>
#include "Pic32Ini.h"
#include "buttons.h"

#define LED_ROJO        0   // RC0
#define LED_VERDE       1   // RC1
#define LED_AZUL        2   // RC2
#define LED_AMARILLO    3   // RC3
#define LED_START       4   // RC4

void initLeds(void) {
    TRISC &= ~((1 << LED_ROJO) |
            (1 << LED_VERDE) |
            (1 << LED_AZUL) |
            (1 << LED_AMARILLO) |
            (1 << LED_START));

    LATC |= ((1 << LED_ROJO) |
            (1 << LED_VERDE) |
            (1 << LED_AZUL) |
            (1 << LED_AMARILLO) |
            (1 << LED_START));
}

void testLed(button_t b) {

    /* Apagar todos */
    LATC |= ((1 << LED_ROJO) |
            (1 << LED_VERDE) |
            (1 << LED_AZUL) |
            (1 << LED_AMARILLO) |
            (1 << LED_START));

    switch (b) {
        case BUTTON_RED:
            LATC &= ~(1 << LED_ROJO);
            break;
        case BUTTON_GREEN:
            LATC &= ~(1 << LED_VERDE);
            break;
        case BUTTON_BLUE:
            LATC &= ~(1 << LED_AZUL);
            break;
        case BUTTON_YELLOW:
            LATC &= ~(1 << LED_AMARILLO);
            break;
        case BUTTON_START:
            LATC &= ~(1 << LED_START);
            break;
        default:
            break;
    }
}

int main(void) {
    initButtons(); // TU buttons.c
    initLeds();

    button_t button;

    while (1) {

        button = ButtonsPressed();

        if (button != BUTTON_NONE) {
            testLed(button); // indica qué botón se ha pulsado
        }
    }
}