#ifndef __LCD_SETUP__
#define __LCD_SETUP__

#include <stdint.h>

void lcd_pulse(uint8_t val);
void lcd_send(uint8_t value, uint8_t mode);
void lcd_init();
void lcd_clear();
void write_to_lcd(const char* message);

#endif
