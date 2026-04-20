#include <xc.h>

#include "Pic32Ini.h"
#include "UART1simple.h"
#include "leds.h"
#include "buttons.h"
#include "buzzer.h"
#include "timers.h"
#include "fsm.h"
#include "game.h"

#include <stdlib.h>

/* =========================
 * Main
 * ========================= */
int main(void)
{
    /* =========================
     * Inicialización hardware
     * ========================= */
    INTCON |= 0x1000;
    asm("ei");

    InicializarUART1(9600);

    initLEDs();
    initButtons();
    Buzzer_init();
    Timer1_init();      // Base de tiempos (ticks)

    /* =========================
     * FSM
     * ========================= */
    FSM_init();

    putsUART("\r\n--- PROYECTO SIMON DICE ---\r\n");
    putsUART("\r\nSistema inicializado correctamente\r\n");

    /* =========================
     * Bucle principal
     * ========================= */
    while (1)
    {
        FSM_run();
        /* NO delays, NO waits */
    }

    return 0;
}