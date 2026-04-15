#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>
#include <stdbool.h>

/* Inicialización del Timer1 */
void Timer1_init(void);

/* Arranca un temporizador en ticks */
void timer_start(uint32_t ticks);

/* Devuelve true cuando el temporizador ha expirado */
bool timer_expired(void);

#endif