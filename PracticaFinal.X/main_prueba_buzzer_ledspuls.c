#include <xc.h>

#include "Pic32Ini.h"
#include "buttons.h"
#include "leds.h"
#include "buzzer.h"

/* =========================================
 * Prueba de Botones + LEDs + Buzzer
 *
 * - Pulsar botón:
 *      LED asociado ON
 *      Buzzer suena (frecuencia por color)
 * - Soltar botón:
 *      LED OFF
 *      Buzzer OFF
 * ========================================= */
int main(void)
{
    /* Inicialización de periféricos */
    initButtons();
    initLEDs();
    Buzzer_init();

    __builtin_enable_interrupts();

    button_t last_button = BUTTON_NONE;

    while (1)
    {
        button_t button = ButtonsPressed();

        /* Nueva pulsación (detección de flanco) */
        if (button != BUTTON_NONE && button != last_button)
        {
            LED_all_off();
            Buzzer_off();

            switch (button)
            {
                case BUTTON_RED:
                    LED_on(RED);
                    Buzzer_on(RED);
                    break;

                case BUTTON_GREEN:
                    LED_on(GREEN);
                    Buzzer_on(GREEN);
                    break;

                case BUTTON_BLUE:
                    LED_on(BLUE);
                    Buzzer_on(BLUE);
                    break;

                case BUTTON_YELLOW:
                    LED_on(YELLOW);
                    Buzzer_on(YELLOW);
                    break;

                default:
                    break;
            }
        }

        /* Botón soltado → apagar todo */
        if (button == BUTTON_NONE)
        {
            LED_all_off();
            Buzzer_off();
        }

        last_button = button;
    }

    return 0;
}