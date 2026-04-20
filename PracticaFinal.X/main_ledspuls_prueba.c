#include <xc.h>
#include "buttons.h"
#include "leds.h"

int main(void)
{
    /* Inicializaciones */
    initButtons();
    initLEDs();

    while (1)
    {
        button_t button = ButtonsPressed();

        switch (button)
        {
            case BUTTON_RED:
                LED_all_off();
                LED_on(RED);
                break;

            case BUTTON_GREEN:
                LED_all_off();
                LED_on(GREEN);
                break;

            case BUTTON_BLUE:
                LED_all_off();
                LED_on(BLUE);
                break;

            case BUTTON_YELLOW:
                LED_all_off();
                LED_on(YELLOW);
                break;

            case BUTTON_START:
                // Opcional: apagar todo al pulsar START
                LED_all_off();
                break;

            case BUTTON_NONE:
            default:
                // No hacer nada
                break;
        }
    }

    return 0;
}