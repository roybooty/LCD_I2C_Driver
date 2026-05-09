#include "../header/stm32f103.h"
#include "lcd_setup.c"
#include <stdint.h>

int main(void) {
    uint8_t message[] = {0x53, 0x61, 0x66, 0x77, 0x61, 0x6e, 0x20,0x74, 0x6f, 0x63, 0x68, 0x20, 0x67, 0x72, 0x61, 0x73, 0x73, 0x0A, 0x73};
    RCC->APB2ENR |= (1 << 3);
    RCC->APB1ENR |= (1 << 21);

    // GPIO setup
    GPIOB->CRL &= ~(0xFU << 24);
    GPIOB->CRL &= ~(0xFU << 28);

    GPIOB->CRL |= (0xFU << 24);
    GPIOB->CRL |= (0xFU << 28);

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

    lcd_send(0x28, 0); // 2 Lines, 5x8 font
    lcd_send(0x0C, 0); // Display ON, Cursor OFF
    lcd_send(0x01, 0); // Clear Display
    delay(50000);      // Clearing takes time!
    lcd_send(0x06, 0); // Entry Mode

    // DISPLAY 'Safwan touch grass'
    for(uint8_t i = 0;i < sizeof(message);i++){
        lcd_send(message[i], RS);
    }

    I2C->CR1 |= (1 << 9);
    return 0;
}

__attribute__((naked, noreturn)) void _reset(void) {
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss;dst < &_ebss;dst++) *dst = 0;
    for (long *dst = &_sdata, *src=&_sidata;dst<&_edata;) *dst++ = *src++;
    main();
    for (;;)(void)0;
}

extern void _estack(void);
__attribute__((section(".vectors"))) void (*const tab[16 + 43])(void) = {
    _estack, _reset,
};
