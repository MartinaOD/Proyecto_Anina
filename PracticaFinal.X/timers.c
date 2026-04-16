#include "timers.h"
#include <xc.h>
#include <sys/attribs.h>

/* =========================
 * Configuración
 * ========================= */
#define PBCLK 5000000UL
#define TIMER1_PRESCALER 256

#define PR1_VALUE (PBCLK / TIMER1_PRESCALER / 1000)

/* =========================
 * Variables internas
 * ========================= */
static volatile uint32_t timer_ticks = 0;
static volatile uint32_t system_ticks = 0;   // ⬅️ NUEVO

/* =========================
 * Inicialización Timer1
 * ========================= */
void Timer1_init(void)
{
    T1CON = 0x0000;
    TMR1 = 0;

    T1CONbits.TCKPS = 3;    // Prescaler 1:256
    PR1 = PR1_VALUE;

    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    IPC1bits.T1IP = 3;

    T1CONbits.ON = 1;
}

/* =========================
 * Arranque temporizador
 * ========================= */
void timer_start(uint32_t ticks)
{
    timer_ticks = ticks;
}

/* =========================
 * ¿Ha expirado?
 * ========================= */
bool timer_expired(void)
{
    return (timer_ticks == 0);
}

/* =========================
 * Acceso a ticks globales
 * ========================= */
uint32_t Timer1_getTicks(void)
{
    return system_ticks;
}

/* =========================
 * ISR Timer1 (cada 1 ms)
 * ========================= */
void __ISR(_TIMER_1_VECTOR, IPL3SOFT) Timer1ISR(void)
{
    system_ticks++;

    if (timer_ticks > 0)
    {
        timer_ticks--;
    }

    IFS0bits.T1IF = 0;
}
