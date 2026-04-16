#include "buzzer.h"
#include <xc.h>
#include <stdint.h>

/* =========================
 * Configuración hardware
 * ========================= */
#define BUZZER_PIN_RP 15        // RPB15
#define PBCLK 5000000UL         // 🔴 CLAVE
#define PRESCALER 8             // Timer2 prescaler

/* =========================
 * Inicialización
 * ========================= */
void Buzzer_init(void)
{
    /* RPB15 como salida OC1 */
    TRISB &= ~(1 << BUZZER_PIN_RP);

    /* PPS: OC1 -> RPB15 */
    RPB15R = 0b0101;

    /* Timer2 */
    T2CON = 0x0;
    TMR2 = 0;
    T2CONbits.TCKPS = 3;   // 1:8
    PR2 = 0;
    T2CONbits.ON = 1;

    /* OC1 */
    OC1CON = 0x0;
    OC1R = 0;
    OC1RS = 0;
    OC1CONbits.OCTSEL = 0; // Timer2
    OC1CONbits.OCM = 0b110; // PWM

    Buzzer_off();
}

/* =========================
 * Encender buzzer por color
 * ========================= */
void Buzzer_on(led_color_t color)
{
    uint32_t frequency;

    switch (color)
    {
        case RED:     frequency = 500;  break;
        case GREEN:   frequency = 800;  break;
        case BLUE:    frequency = 1200; break;
        case YELLOW:  frequency = 1600; break;
        default: return;
    }

    PR2 = (PBCLK / (frequency * PRESCALER)) - 1;
    OC1RS = (PR2 * 7) / 8;   // ~87 %
    OC1CONbits.ON = 1;         // 🔴 activar OC1
}

/* =========================
 * Apagar buzzer
 * ========================= */
void Buzzer_off(void)
{
    OC1CONbits.ON = 0;         // 🔴 apagar OC1
    OC1RS = 0;
}