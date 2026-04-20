#include <xc.h>
#include <stdint.h>
#include "Pic32Ini.h" // Aquí se define PBCLK
#include "UART1simple.h"


/* Recepcion y transmision */

#define TAM_COLA 100 
#define PIN_RX 13 
#define PIN_TX 7 
#define FPB 5000000 // El reloj interno 

static int icab_rx = 0, icol_rx = 0, icab_tx = 0, icol_tx = 0;
static char cola_rx[TAM_COLA], cola_tx[TAM_COLA];

void InicializarUART1(int baudios) {

    ANSELB &= ~(1 << PIN_RX);
    TRISB |= (1 << PIN_RX);

    ANSELB &= ~(1 << PIN_TX);
    TRISB &= ~(1 << PIN_TX);
    LATB |= (1 << PIN_RX);

    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 1; // U1TX a RB7 
    U1RXR = 3; // U1RX a RB13 
    SYSKEY = 0x1CA11CA1;

    // Definimos la velocidad: 
    if (baudios > 38400) {
        // Divisor por 4 
        U1MODEbits.BRGH = 1;
        U1BRG = (unsigned int) lround(((double) FPB) / (4.0 *
                (double) baudios) - 1.0);

    } else {
        // Divisor por 16 
        U1MODEbits.BRGH = 0;
        U1BRG = (unsigned int) lround(((double) FPB) / (16.0 *
                (double) baudios) - 1.0);
    }

    IFS1 &= ~0x300; // Borro los flags de Tx y Rx
    IEC1 |= 0x100; // Habilito solo la interrupción de Rx 
    IPC8bits.U1IP = 3;
    IPC8bits.U1IP = 1;

    U1STA = 0x9400; // Interrupción Rx al llegar 1 char, Tx cuando FIFO vacía
    U1MODE |= 0x8000; // Arranco la UART 

}

void putsUART(char s[]) {
    // Para introducir cadenas de caracteres en la cola 
    while (*s != '\0') {
        if ((icab_tx + 1 == icol_tx) || (icab_tx + 1 == TAM_COLA && icol_tx
                == 0)) {
            break; // La cola está llena. Se aborta el envío de datos  
        } else {
            cola_tx[icab_tx] = *s; // Copia el dato en la cola 
            s++;
            icab_tx++;
            if (icab_tx == TAM_COLA) {
                icab_tx = 0;
            }
        }
    }
    // Se habilitan las interrupciones del transmisor para comenzar a enviar
    IEC1bits.U1TXIE = 1;
}

char getcUART() {
    char c;
    // Para extraer un caracter de la cola 
    if (icol_rx != icab_rx) { // Hay datos nuevos  
        c = cola_rx[icol_rx];
        icol_rx++;
        if (icol_rx == TAM_COLA) {
            icol_rx = 0;
        }
    } else {
        c = '\0'; // No ha llegado nada  
    }
    return c;
}

__attribute__((vector(32), interrupt(IPL3SOFT), nomips16))
voidInterrupcionUART1(void) {
    if ((IFS1 & 0x100) == 0x100) {
        // Interrumpió Rx 
        if ((icab_rx + 1 == icol_rx) || (icab_rx + 1 == TAM_COLA && icol_rx
                == 0)) {
            // La cola está llena  
            //break; 
        } else {
            cola_rx[icab_rx] = U1RXREG; // Lee dato de la UART  
            icab_rx++;
            if (icab_rx == TAM_COLA) {
                icab_rx = 0;
            }
        }
    }
    if ((IFS1 & 0x200) == 0x200) {
        // Interrumpió Tx 
        if (icol_tx != icab_tx) { // Hay datos nuevos  
            U1TXREG = cola_tx[icol_tx];
            icol_tx++;
            if (icol_tx == TAM_COLA) {
                icol_tx = 0;
            }
        } else { // Se ha vaciado la cola. 
            IEC1bits.U1TXIE = 0; // Para evitar bucle sin fin  
        }
    }
    IFS1 &= ~0x300; // Borro flags 
}
