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
 * main_prueba_fsm_uart_game
 * ========================= */
int main(void)
{
    /* =========================
     * Inicialización hardware
     * ========================= */

    INTCON |= 0x1000;
    asm("ei");
    /* UART (monitorización FSM) */
    InicializarUART1(9600);

    /* Drivers */
    initLEDs();
    initButtons();
    Buzzer_init();
    Timer1_init();

    /* Habilitar interrupciones */
    __builtin_enable_interrupts();

    /* =========================
     * FSM
     * ========================= */
    FSM_init();

    putsUART("--- PROYECTO SIMON DICE ---\r\n");
    putsUART("Sistema inicializado correctamente\r\n");

    /* =========================
     * Bucle principal
     * ========================= */
    while (1)
    {
        FSM_run();
    }

    return 0;
}
