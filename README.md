
# Register-Level STM32 I²C LCD Driver

A bare-metal C driver for HD44780 character LCDs connected through a PCF8574 I²C backpack, built for the STM32F103C8T6 Blue Pill.

This project implements the STM32 I²C peripheral directly through memory-mapped registers. It does not use STM32 HAL or LL libraries.

## What it supports

- STM32F103C8T6
- HD44780-compatible 16x2 and 20x4 LCDs
- PCF8574 I²C backpack
- I²C on PB6/SCL and PB7/SDA
- Bare-metal C implementation
- Custom Makefile and linker script

## Why I built it

I wanted to understand how an STM32 communicates with an external peripheral at register level instead of hiding the hardware behind an abstraction layer. The driver was built from the STM32F103 reference manual, the I²C protocol, and the LCD and PCF8574 documentation.

## Hardware

- STM32F103C8T6 Blue Pill
- HD44780-compatible LCD, 16x2 or 20x4
- PCF8574 I²C backpack
- ST-Link or another compatible programmer

## Connections

| Signal | STM32F103C8T6 |
| I²C SCL | PB6 |
| I²C SDA | PB7 |

Add the LCD power, ground, and pull-up details here once you confirm the exact wiring.

## Build and flash

bash
git clone https://github.com/roybooty/LCD_I2C_Driver.git
cd LCD_I2C_Driver
make


Add the exact flashing command and required tools here, for example OpenOCD or st-flash, once you have verified them on your setup.

## Example usage

Add a short code example showing the actual public API, such as:

c
lcd_init();
lcd_clear();
lcd_set_cursor(0, 0);
write_to_lcd("Hello, STM32");


Replace those function names with the real functions in your source code.

## Design notes

The driver handles the communication between the STM32 I²C peripheral and the PCF8574 backpack, which then controls the HD44780 LCD data and control lines. The implementation focuses on direct register access, a small dependency fo…
