PROJECT 4 - DIGITAL STOPWATCH

PIC18F4580, 20 MHz, 16x2 CLCD, Timer0 interrupt.

Connections:
RB0 -> START/STOP switch (active LOW)
RB1 -> RESET switch (active LOW)
PORTD -> CLCD data D0-D7
RC0 -> CLCD RW
RC1 -> CLCD RS
RC2 -> CLCD EN

Concepts:
GPIO, Timer0, interrupt, volatile variables, switch polling/debounce, CLCD.
