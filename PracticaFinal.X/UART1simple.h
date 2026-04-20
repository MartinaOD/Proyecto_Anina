#ifndef UART_H
#define UART_H

#include <xc.h>
#include <stdint.h>

#define TAM_COLA 100
#define PIN_RX 13
#define PIN_TX 7
#define FPB 5000000 // Frecuencia del bus periférico (Hz)


// Inicializa la UART1 con el baudrate indicado
void InicializarUART1(int baudios);

// Envía una cadena de caracteres por UART (no bloqueante)
void putsUART(char s[]);

// Lee un carácter recibido por UART
char getcUART(void);

// Rutina de servicio de interrupción de UART1
void InterrupcionUART1(void);

#endif
