NAME = volume_detection
CPU = atmega328p
F_CPU = 1000000

CC = avr-gcc
OBJCOPY = avr-objcopy

all: $(NAME).hex

SRCS = \
main.c \
src/HD44780/lcd.c \
src/adc/adc.c \
src/gpio/gpio.c \

INCLUDES = \
-Iinc \
-Isrc \

CFLAGS = -mmcu=$(CPU) -DF_CPU=$(F_CPU) -Os $(INCLUDES) -Werror -Wextra -Wall
LDFLAGS = -Wl,-u,vfprintf -lprintf_flt -lm
OBJS = $(SRCS:.c=.o)

$(OBJS): $(SRCS)

$(NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(NAME).hex: $(NAME).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

flash: $(NAME).hex
	avrdude -p $(CPU) -c usbasp -U flash:w:$<

clean:
	@echo "Cleaning .o, .a, .elf and .hex files"
	@find -name '*.o' -delete
	@find -name '*.a' -delete
	@rm -f *.{hex,elf}
