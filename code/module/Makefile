NAME = volume_detection
CPU = atmega328p
F_CPU = 8000000

CC = avr-gcc
OBJCOPY = avr-objcopy

all: $(NAME).hex

SRCS = \
main.c \
src/gpio/gpio.c \

INCLUDES = \
-Iinc \
-Isrc \

CFLAGS = -mmcu=$(CPU) -DF_CPU=$(F_CPU) -Os $(INCLUDES)
OBJS = $(SRCS:.c=.o)

$(OBJS): $(SRCS)

$(NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME).hex: $(NAME).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

flash: $(NAME).hex
	avrdude -p $(CPU) -c avrisp2 -P usb -U flash:w:$<

clean:
	@echo "Cleaning .o, .a, .elf and .hex files"
	@find -name '*.o' -delete
	@find -name '*.a' -delete
	@rm -f *.{hex,elf}
