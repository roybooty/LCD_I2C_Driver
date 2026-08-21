# Register-Level STM32 I²C LCD Driver

A bare-metal C driver for HD44780 character LCDs connected through a PCF8574 I²C backpack, built specifically for the STM32F103C8T6 "Blue Pill".

This implementation communicates with the STM32 I²C peripheral directly through memory-mapped registers without using STM32 HAL, LL, or third-party libraries.

## Overview

* **Hardware Supported:** STM32F103C8T6, HD44780-compatible LCDs (16x2, 20x4), PCF8574 I²C backpack.
* **Peripheral Mapping:** Standard I²C1 on **PB6** (SCL) and **PB7** (SDA).
* **Architecture:** Pure bare-metal C with a custom Makefile and linker script.

## Motivation

Built to understand lower-level MCU communication protocols by interfacing with external peripherals at the register level instead of hiding hardware details behind abstraction layers. The driver was written directly from the STM32F103 reference manual, I²C protocol specifications, and the HD44780/PCF8574 datasheets.

## Hardware Connections

| PCF8574 Backpack | STM32F103C8T6 Pin | Notes |
| :--- | :--- | :--- |
| **VCC** | 5V / 3.3V | Match LCD module requirements |
| **GND** | GND | Common ground |
| **SCL** | PB6 | I²C1 Clock (Requires 4.7kΩ pull-up) |
| **SDA** | PB7 | I²C1 Data (Requires 4.7kΩ pull-up) |

## Build and Flash

```bash
# Clone the repository
git clone [https://github.com/roybooty/LCD_I2C_Driver.git](https://github.com/roybooty/LCD_I2C_Driver.git)
cd LCD_I2C_Driver

# Compile the firmware
make

# Flash to the target via programmer
make flash

# Clean build artifacts
make clean
