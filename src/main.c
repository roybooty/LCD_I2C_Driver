#include <stdint.h>
#include "../header/stm32f103.h"
#include "../header/lcd_setup.h"
#include "../header/utilities.h"

void write_to_lcd(const char* message) {
    for(uint8_t i = 0;i < sizeof(message);i++){
        lcd_send(((unsigned char)message[i]), RS);
    }
}

int main(void) {
    RCC->APB2ENR |= (1 << 3);
    RCC->APB1ENR |= (1 << 21);

    // GPIO setup
    GPIOB->CRL &= ~(0xFU << 24);
    GPIOB->CRL &= ~(0xFU << 28);

    GPIOB->CRL |= (0xFU << 24);
    GPIOB->CRL |= (0xFU << 28);

    lcd_init();
    lcd_clear();

    write_to_lcd("hi");

    //I2C->CR1 |= (1 << 9);
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
