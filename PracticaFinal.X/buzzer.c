#include "buzzer.h"
#include <xc.h>
#include <stdint.h>

/* =========================
 * Configuración hardware
 * ========================= */
#define BUZZER_OC_MODULE   1       // OC1
#define BUZZER_PIN_RP      15      // RPB15

/* Clock del sistema (ajustar si es distinto) */
#define PBCLK 40000000UL           // 40 MHz típico en PIC32

/* =========================
 * Inicialización
 * ========================= */
void Buzzer_init(void)
{
    /* ---------- Configurar pin RPB15 como salida OC1 ---------- */
    TRISB &= ~(1 << BUZZER_PIN_RP);

    /* Remapeo PPS: OC1 -> RPB15 */
    RPB15R = 0b0101;   // OC1 function

    /* ---------- Timer2 ---------- */
    T2CON = 0x0;
    TMR2 = 0;
    PR2 = 0;
    T2CONbits.TCKPS = 3;  // Prescaler 1:8
    T2CONbits.ON = 1;

    /* ---------- OC1 ---------- */
    OC1CON = 0x0;
    OC1R = 0;
    OC1RS = 0;
    OC1CONbits.OCTSEL = 0;  // Timer2
    OC1CONbits.OCM = 0b110; // PWM mode
    OC1CONbits.ON = 1;

    Buzzer_off();
}

/* =========================
 * Activar buzzer según color
 * ========================= */
void Buzzer_on(led_color_t color)
{
    uint32_t frequency = 0;

    switch (color)
    {
        case RED:
            frequency = 500;
            break;

        case GREEN:
            frequency = 800;
            break;

        case BLUE:
            frequency = 1200;
            break;

        case YELLOW:
            frequency = 1600;
            break;

        default:
            return;
    }

    /* Calcular PR2 para la frecuencia deseada */
    PR2 = (PBCLK / (frequency * 8)) - 1;

    /* Duty cycle 50% */
    OC1RS = PR2 / 2;
}

/* =========================
 * Apagar buzzer
 * ========================= */
void Buzzer_off(void)
{
    OC1RS = 0;
}