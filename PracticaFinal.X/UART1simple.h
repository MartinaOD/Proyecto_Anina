#ifndef UART_H
#define UART_H

/* ===================== INCLUDES ===================== */
#include <xc.h>
#include <stdint.h>

/* ===================== DEFINES ===================== */
#define TAM_COLA 100
#define PIN_RX 13
#define PIN_TX 7
#define FPB 5000000     // Frecuencia del bus periférico (Hz)

/* ===================== PROTOTIPOS ===================== */

/**
 * Inicializa la UART1 con el baudrate indicado
 * @param baudios Velocidad en baudios (ej: 9600, 115200)
 */
void InicializarUART1(int baudios);

/**
 * Envía una cadena de caracteres por UART (no bloqueante)
 * @param s Cadena terminada en '\0'
 */
void putsUART(char s[]);

/**
 * Lee un carácter recibido por UART
 * @return Carácter recibido o '\0' si no hay datos
 */
char getcUART(void);

/**
 * Rutina de servicio de interrupción de UART1
 */
void InterrupcionUART1(void);

#endif /* UART_H */