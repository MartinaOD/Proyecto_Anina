#include <xc.h>
#include "leds.h"

/* Delay simple (bloqueante, solo para sesión 1) */
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 10000; j++);
}

int main(void)
{
    initLEDs();

    while (1)
    {
        /* Rojo */
        LED_on(RED);
        delay_ms(1000);

        /* Rojo + Verde */
        LED_on(GREEN);
        delay_ms(1000);

        /* Rojo + Verde + Azul */
        LED_on(BLUE);
        delay_ms(1000);

        /* Rojo + Verde + Azul + Amarillo */
        LED_on(YELLOW);
        delay_ms(1000);

        /* Apagar todos y repetir */
        LED_all_off();
        delay_ms(1000);
    }

    return 0;
}