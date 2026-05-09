Register-Level STM32 I2C LCD Driver
A high-performance, zero-HAL driver for HD44780 LCDs via PCF8574. Written entirely using STM32 registers for the Blue Pill (F103C8).

🚀 Why this exists
No HAL/LL: Built from the datasheet up.

Lightweight: Tiny binary footprint.

Register-Direct: High-speed I2C.

🛠️ Hardware
MCU: STM32F103C8T6

Display: 16x2 or 20x4 LCD with I2C Backpack

Protocol: I2C (PB6/SCL, PB7/SDA)
