CFLAGS  ?= -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion \
           -fno-common -Wconversion \
           -g3 -Os -ffunction-sections -fdata-sections -I. \
           -mcpu=cortex-m3 -mthumb -msoft-float $(EXTRA_CFLAGS)
LDFLAGS ?= -Tscripts/link.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=$@.map --specs=nosys.specs
SOURCES = src/main.c

ifeq ($(OS),Windows_NT)
  RM = cmd /C del /Q /F
else
  RM = rm -f
endif

build: firmware.bin

firmware.elf: $(SOURCES)
	arm-none-eabi-gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary $< $@

flash: firmware.bin
	st-flash --reset write $< 0x8000000

clean:
	$(RM) firmware.*
