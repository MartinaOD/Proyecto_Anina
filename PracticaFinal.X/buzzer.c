#include <xc.h>

#include "Pic32Ini.h"
#include "UART1simple.h"
#include "leds.h"
#include "buttons.h"
#include "buzzer.h"
#include "timers.h"
#include "fsm.h"
#include "game.h"
#include "dificultad.h"

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
    /* UART  */
    InicializarUART1(9600);

    putsUART("\r\nSeleccione dificultad (1-3):\r\n");

    char c;

    // Bloque hasta que el usuario me pase algo:
    c = getcUART();

    while(c == '\0'){
        c = getcUART();
    }

    // Salgo del while una vez el usuario haya introducido un valor

    /*if (c < '1' || c > '3'){
        // En caso de ser un valor incorrecto, configuro la velocidad normal:
        c = '2';
    }*/ //Ya en dificultad.c aunq posible doble seguro

    dificultad_configurar(c);

    putsUART("Dificultad configurada\r\n");


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
