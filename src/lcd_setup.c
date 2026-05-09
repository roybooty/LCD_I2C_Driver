#include "../header/stm32f103.h"
#include "delay.c"

void lcd_pulse(uint8_t val) {
    I2C->DR = val | EN | BL;            // Set Data + Enable HIGH
    while(!(I2C->SR1 & (1 << 7)));
    delay(2000);

    I2C->DR = val | BL;                 // Drop Enable LOW (LCD reads now)
    while(!(I2C->SR1 & (1 << 7)));
    delay(2000);
}

// 4. Send a full byte (Command or Data) in two nibbles
void lcd_send(uint8_t value, uint8_t mode) {
    uint8_t high = value & 0xF0;
    uint8_t low = (value << 4) & 0xF0;
    lcd_pulse(high | mode);
    lcd_pulse(low | mode);
}
