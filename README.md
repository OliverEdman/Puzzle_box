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

## 📁 Project Structure.
├── 📂 app            # The "Application layer"
│   └── main.c        # Main & Game State Machine
├── 📂 drivers        # Hardware Abstraction Layer (HAL)
│   ├── display.c     # 74HC595 & 7-Segment multiplexing logic
│   ├── servo.c       # PWM signal generation for SG90
│   └── (other peripheral drivers...)
├── 📂 src            # The "Engine Room"
│   └── functions.c   # Core logic implementation & puzzle algorithms
├── 📂 include        # The "Map" (Header files)
│   ├── display.h     # Driver interfaces
│   ├── morse.h       # Morse code logic definitions
│   └── functions.h   # Function prototypes for src/
├── 📄 .gitignore     # Prevents build artifacts (hex/obj) from being tracked
├── 📄 LICENSE        # Project licensing information
├── 📝 NOTES.md       # Dev logs, pin-maps, and brainstormed ideas
└── 📘 README.md      # Project documentation


