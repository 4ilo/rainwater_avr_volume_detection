#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

enum Ports {
    PORT_B = 0,
    PORT_C,
    PORT_D,
    MAX_PORT,
};

enum Mode {
    GPIO_IN = 0,
    GPIO_OUT,
    MAX_MODE,
};

enum Pins {
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    MAX_PIN,
};

int8_t gpio_init(enum Ports port, enum Pins pin, enum Mode mode);
int8_t gpio_write(enum Ports port, enum Pins pin, uint8_t value);

#endif // _GPIO_H_
