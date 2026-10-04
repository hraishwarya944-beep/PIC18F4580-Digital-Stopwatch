/*
 * Project 4 - Digital Stopwatch using PIC18F4580
 * Hardware: PIC18F4580 + 16x2 CLCD + START/STOP/RESET switches
 * Clock: 20 MHz
 *
 * RB0 -> START / STOP switch (active LOW)
 * RB1 -> RESET switch (active LOW)
 * CLCD: PORTD data, RC0=RW, RC1=RS, RC2=EN
 */


#include <xc.h>
#include "clcd.h"

volatile unsigned int tick_count = 0;
volatile unsigned int elapsed_elapsed_seconds = 0;
volatile unsigned char running = 0;

static void init_timer0(void)
{
    T08BIT = 1;     // Timer0 as 8-bit
    T0CS = 0;       // Internal instruction clock (Fosc/4)
    PSA = 1;        // No prescaler
    TMR0 = 6;       // 250 counts -> 50 us at 20 MHz

    TMR0IF = 0;
    TMR0IE = 1;
}

static void __interrupt() isr(void)
{
    if (TMR0IF)
    {
        TMR0IF = 0;
        TMR0 = 6;

        if (running)
        {
            tick_count++;

            // 50 us x 20000 = 1 second
            if (tick_count >= 20000)
            {
                tick_count = 0;
                elapsed_seconds++;

                if (elapsed_seconds >= 6000)
                    elapsed_elapsed_seconds = 0;
            }
        }
    }
}

static void init_config(void)
{
    ADCON1 = 0x0F;      // All required pins as digital

    TRISB0 = 1;         // START/STOP input
    TRISB1 = 1;         // RESET input

    INTCON2bits.RBPU = 0;   // Enable PORTB weak pull-ups

    init_clcd();
    init_timer0();

    PEIE = 1;
    GIE = 1;
}

static void display_time(void)
{
    unsigned char min, sec;

    min = elapsed_seconds / 60;
    sec = elapsed_seconds % 60;

    clcd_putch('0' + min, LINE2(4));
    clcd_putch(':',        LINE2(5));
    clcd_putch('0' + (sec / 10), LINE2(6));
    clcd_putch('0' + (sec % 10), LINE2(7));
}

void main(void)
{
    unsigned char old_start = 1;
    unsigned char old_reset = 1;

    init_config();

    clcd_print("DIGITAL STOPWATCH", LINE1(0));
    clcd_print("TIME: 00:00", LINE2(0));

    while (1)
    {
        // START/STOP: detect button press (1 -> 0)
        if (old_start == 1 && RB0 == 0)
        {
            running = !running;
            __delay_ms(20);     // simple debounce
        }
        old_start = RB0;

        // RESET: detect button press (1 -> 0)
        if (old_reset == 1 && RB1 == 0)
        {
            running = 0;
            tick_count = 0;
            elapsed_seconds = 0;
            __delay_ms(20);
        }
        old_reset = RB1;

        display_time();
    }
}
