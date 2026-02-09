# Embedded Puzzle Box - Bare metal project


## 🎯 Project Purpose
This project was developed as a core part of my Embedded Systems education. The primary goal was to move beyond high-level libraries
and master C programming and Bare Metal development on the AVR architecture.

## 🚀 Overview
* **Memory Game (Simon Says):** Logic-based pattern recognition using tactile buttons and LEDs.
* **Analog Challenge:** High-precision input handling using 4x Potentiometers (ADC).
* **Proximity Task:** Distance measurement using Ultrasonic sensor (Input Capture/Interrupts).
* **User Interface:** Real-time feedback via a 4-digit 7-segment display driven by a 74HC595 shift register (SPI logic).
* **Actuator:** PWM-controlled servo motor for the locking bolt.

## 🛠️ Tech Stack & Hardware
* **Microcontroller:** ATmega328P (8-bit AVR)
* **Language:** C
* **Protocols:** SPI (Shift Register), PWM (Servo), ADC (Potentiometers), UART (Debugging).
* **Key Components:** 74HC595, SG90 Servo, HC-SR04, 3461AS-1 Display.

## 📁 Project Structure


```bash
.
├── 📂 app            # Main logic & State Machine
│   └── main.c        # Entry point
├── 📂 drivers        # Hardware Abstraction Layer (HAL)
│   ├── display.c     # 7-segment & 74HC595 driver
│   └── servo.c       # PWM & Timer driver
├── 📂 src            # Implementation of puzzles
│   └── functions.c   # Core algorithms & logic
├── 📂 include        # Header files (.h)
│   ├── display.h
│   └── functions.h
├── 📄 .gitignore     # Files to ignore (hex, obj)
├── 📄 LICENSE        # MIT License
├── 📝 NOTES.md       # Pinout & Scratchpad
└── ⚙️ Makefile      # Build configuration


