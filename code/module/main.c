#include <avr/io.h>
#include <util/delay.h>

#include "gpio/gpio.h"


int main(void)
{
    gpio_init(PORT_B, PIN_0, GPIO_OUT);

    while (1) {
        gpio_write(PORT_B, PIN_0, 1);
        _delay_ms(1000);

        gpio_write(PORT_B, PIN_0, 0);
        _delay_ms(1000);
    }
}
