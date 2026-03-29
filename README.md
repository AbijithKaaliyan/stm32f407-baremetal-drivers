# STM32F407 Bare-Metal Device Drivers (No HAL)

## 📌 Overview

This repository contains a set of **bare-metal device drivers** developed for the STM32F407 microcontroller using **direct register-level programming** without relying on any vendor HAL libraries.

The goal of this project is to demonstrate a deep understanding of:

* Microcontroller architecture
* Memory-mapped registers
* Peripheral control
* Embedded C programming

---

## 🚀 Features

* GPIO driver (input/output, interrupt handling)
* UART driver (TX/RX, baud rate configuration)
* SPI driver (full-duplex communication)
* I2C driver (master mode communication)
* RCC driver (clock configuration)
* Timer and PWM configuration (basic)

---

## 🛠️ Tools & Hardware

* STM32F407 Discovery Board
* STM32CubeIDE
* Logic Analyzer (for protocol validation)

---

## 📊 Validation

Peripheral communication protocols were verified using a logic analyzer:

* UART timing and baud rate accuracy
* SPI clock polarity and phase behavior
* I2C start/stop and acknowledgment sequences

Screenshots are available in the `/logic_analyzer` folder.

---

## 📂 Project Structure

* `stm32f407_drivers/drivers/` → Peripheral driver implementations
* `stm32f407_drivers/Src/` → Example applications using drivers
* `logic_analyzer/` → Signal validation screenshots
* `docs/` → Additional documentation and notes

---

## 🎯 Learning Outcomes

* Developed reusable driver interfaces for STM32 peripherals
* Understood bus architecture (AHB, APB1, APB2)
* Implemented interrupt-driven communication
* Practiced bitwise operations and register manipulation
* Gained experience in hardware debugging and validation

---

## ⚡ Key Highlight

All drivers are implemented **without using HAL or middleware**, showcasing low-level control and understanding of embedded systems.

---

## 📌 Future Work

* Integration with FreeRTOS
* DMA-based data transfer
* Porting drivers to other MCU platforms (e.g., TI LaunchPad)

---

## 👨‍💻 Author

Abijith Radhakrishnan
Embedded Software Engineer
