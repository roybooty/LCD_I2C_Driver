#include "../header/stm32f103.h"
#include "../header/utilities.h"

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

void lcd_init() {
    // i2c setup
    I2C->CR2 |= 36;
    I2C->CCR |= 180;
    I2C->TRISE |= 37;
    I2C->CR1 |= (1 << 0);
    I2C->CR1 |= (1 << 8);
    while(!(I2C->SR1 & (1 << 0)));
    I2C->DR = (0x27 << 1);
    while(!(I2C->SR1 & (1 << 1)));
    (void)I2C->SR1;
    (void)I2C->SR2;
    I2C->DR = 0x08;
    while(!(I2C->SR1 & (1 << 7)));

    lcd_pulse(0x30);
    delay(10000);
    lcd_pulse(0x30);
    delay(1000);
    lcd_pulse(0x30);
    lcd_pulse(0x20);

}
