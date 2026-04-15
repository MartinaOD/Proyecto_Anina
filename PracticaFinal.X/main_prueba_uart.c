/*
 * File:   main8.c
 * Author: laboratorios
 *
 * Created on 10 de marzo de 2026, 19:30
 */


#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h"
// Programa principal que haga Eco enviando "X" 
 
#include "UART1simple.h" 
 
# define BAUDIOS 9600 

int main(void) {

    INTCON |= 0x1000;
    asm("ei");
    InicializarUART1(BAUDIOS);

    unsigned char c[2];
    c[1] = '\0';

    while (1) {
        char rx = getcUART(); // Leemos carácter de la cola Rx 
        if (rx != '\0') {
            c[0] = rx;
            putsUART(c);
        }
    }
} 

