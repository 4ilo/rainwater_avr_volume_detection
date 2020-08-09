
#include "gpio.h"
#include <avr/io.h>

#define SET_PIN(port, pin) (port |= (1 << pin))
#define CLEAR_PIN(port, pin) (port &= ~(1 << pin))

volatile uint8_t *port_mapping[MAX_PORT] = {&PORTB, &PORTC, &PORTD};
volatile uint8_t *ddr_mapping[MAX_PORT] = {&DDRB, &DDRC, &DDRD};


int8_t gpio_init(enum Ports port, enum Pins pin, enum Mode mode)
{
    if (port < 0 || port >= MAX_PORT) {
        return -1;
    }

    if (pin < 0 || pin >= MAX_PIN) {
        return -1;
    }

    if (mode == GPIO_OUT) {
        SET_PIN(*ddr_mapping[port], pin);
    } else {
        CLEAR_PIN(*ddr_mapping[port], pin);
    }

    return 0;
}

int8_t gpio_write(enum Ports port, enum Pins pin, uint8_t value)
{
    if (port < 0 || port >= MAX_PORT) {
        return -1;
    }

    if (pin < 0 || pin >= MAX_PIN) {
        return -1;
    }

    if (value) {
        SET_PIN(*port_mapping[port], pin);
    } else {
        CLEAR_PIN(*port_mapping[port], pin);
    }

    return 0;
}
