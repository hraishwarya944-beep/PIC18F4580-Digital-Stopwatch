
# Digital Stopwatch using PIC18F4580

## 📌 Project Overview

The Digital Stopwatch is a simple embedded system project developed using the **PIC18F4580 microcontroller**.

The stopwatch uses **Timer0 interrupt** to generate accurate time intervals and displays the elapsed time on a **16x2 Character LCD (CLCD)**.

Two switches are used to control the stopwatch:

* **START/STOP** – starts or pauses the stopwatch
* **RESET** – resets the stopwatch to `00:00`

This project demonstrates the use of **timers, interrupts, GPIO, switch interfacing, and CLCD interfacing** in a microcontroller-based system.

---

## 🎯 Objective

The main objective of this project is to implement a basic digital stopwatch using a PIC18F4580 microcontroller.

The project helps in understanding:

* Timer configuration
* Timer interrupt generation
* Switch interfacing
* GPIO configuration
* CLCD interfacing
* Interrupt Service Routine (ISR)
* `volatile` variables
* Basic time calculation

---

## 🛠️ Hardware Requirements

* PIC18F4580 Microcontroller
* 16x2 Character LCD (CLCD)
* Push buttons / switches
* LED or indicator (optional)
* 20 MHz crystal oscillator
* Resistors
* Breadboard / development board
* Power supply

---

## 💻 Software Requirements

* MPLAB X IDE
* XC8 Compiler
* PIC18F4580 Device Family Pack
* Embedded C

---

## 🔌 Pin Connections

### Switches

| Component  | PIC18F4580 Pin | Purpose                  |
| ---------- | -------------- | ------------------------ |
| START/STOP | RB0            | Start or pause stopwatch |
| RESET      | RB1            | Reset stopwatch          |

### CLCD

| CLCD Signal | PIC18F4580 |
| ----------- | ---------- |
| Data D0-D7  | PORTD      |
| RW          | RC0        |
| RS          | RC1        |
| EN          | RC2        |

---

## ⚙️ Working Principle

The stopwatch works using **Timer0 interrupt**.

### 1. Initialization

Initially:

* PIC18F4580 GPIO is configured.
* CLCD is initialized.
* Timer0 is configured.
* Timer0 interrupt is enabled.
* Global interrupt is enabled.

The CLCD displays:

```text
DIGITAL STOPWATCH
TIME: 00:00
```

### 2. START/STOP

When the START/STOP switch is pressed:

* The switch state changes from HIGH to LOW.
* The program detects the button press.
* The `running` variable is toggled.

If:

```c
running = 1;
```

the stopwatch starts counting.

If:

```c
running = 0;
```

the stopwatch pauses.

### 3. Timer0 Interrupt

Timer0 generates periodic interrupts.

Each interrupt updates the timer count.

After the required number of Timer0 interrupts, approximately **one second** is obtained.

The elapsed seconds are then incremented.

### 4. Display

The elapsed time is converted into:

```text
MM:SS
```

and displayed on the CLCD.

Example:

```text
TIME: 00:01
TIME: 00:02
TIME: 00:03
...
```

### 5. RESET

When the RESET switch is pressed:

```text
running = 0
elapsed time = 0
```

The CLCD again displays:

```text
TIME: 00:00
```

---

## 🔄 Program Flow

```text
          START
            |
            v
     Initialize PIC
            |
            v
      Initialize CLCD
            |
            v
     Configure Timer0
            |
            v
     Enable Interrupt
            |
            v
       Main Loop
            |
       +----+----+
       |         |
       v         v
 START/STOP    RESET
       |         |
       v         v
 Toggle      Clear Time
 running     and Stop
       |
       v
 Timer0 Interrupt
       |
       v
 Count Timer Interrupts
       |
       v
 Generate 1 Second
       |
       v
 Increment Time
       |
       v
 Display MM:SS
```

---

## 🧠 Important Concepts

### Timer

A timer is a hardware peripheral used to generate accurate time delays or periodic events without continuously blocking the CPU.

### Interrupt

An interrupt temporarily stops the normal program execution and transfers control to an **Interrupt Service Routine (ISR)**.

In this project, Timer0 generates the interrupt.

### ISR

The Interrupt Service Routine handles the Timer0 interrupt and updates the stopwatch timing.

### Volatile

The timer variables are declared as `volatile` because their values can be modified inside the ISR and accessed by the main program.

Example:

```c
volatile unsigned int tick_count;
volatile unsigned int elapsed_seconds;
```

### GPIO

GPIO is used to read the START/STOP and RESET switches.

### CLCD

The 16x2 Character LCD is used to display the current stopwatch time.

---

## 📂 Project Files

```text
main.c
    |
    ├── Timer0 configuration
    ├── Interrupt Service Routine
    ├── Switch handling
    ├── Stopwatch calculation
    └── CLCD display

clcd.c
    |
    └── CLCD driver functions

clcd.h
    |
    └── CLCD function declarations
```

---

## 🚀 Applications

The same concept can be extended to:

* Digital timers
* Event counters
* Industrial timing systems
* Sports timing systems
* Embedded control systems
* Vehicle timing applications

---

## 📚 Learning Outcome

Through this project, I gained practical understanding of:

* PIC18F4580 microcontroller
* Timer0 configuration
* Interrupt handling
* ISR implementation
* GPIO and switch interfacing
* CLCD interfacing
* `volatile` variables
* Embedded C programming

---

## 👨‍💻 Author

**Aishwarya H R**

Embedded Systems Trainee | Embedded C | Microcontrollers

