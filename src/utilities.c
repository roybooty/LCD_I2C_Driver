#include <stdint.h>

void delay(volatile uint32_t count) {
    while(count--) __asm("nop");
}
