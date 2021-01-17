#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "gpio/gpio.h"
#include "HD44780/lcd.h"
#include "adc/adc.h"


int main(void)
{
    gpio_init(PORT_C, PIN_1, GPIO_OUT);

    gpio_init(PORT_D, 0, GPIO_OUT);
    gpio_init(PORT_D, 1, GPIO_OUT);
    gpio_init(PORT_D, 2, GPIO_OUT);
    gpio_init(PORT_D, 3, GPIO_OUT);
    gpio_init(PORT_D, 4, GPIO_OUT);
    gpio_init(PORT_D, 5, GPIO_OUT);

    Lcd_PortType ports[] = {PORT_D, PORT_D, PORT_D, PORT_D};
    Lcd_PinType pins[] = {3, 2, 1, 0};
    Lcd_HandleTypeDef lcd;

    lcd = Lcd_create(ports, pins, PORT_D, PIN_5, PORT_D, PIN_4, LCD_4_BIT_MODE);

    adc_init();
    uint16_t value = 0;
    float current = 0;
    float pressure = 0;

    while (1) {
        value = adc_read(0);
        current = value * 0.02034505208;      // ((value * 5V)/1204)/240ohm * 1000mA

        char buffer[16];
        snprintf(buffer, 16, "I=%05.2fmA", current);
        Lcd_cursor(&lcd, 0, 0);
        Lcd_string(&lcd, buffer);

        pressure = (0.0125 * current) - 0.05;
        snprintf(buffer, 16, "p=%0.4fBar", pressure);
        Lcd_cursor(&lcd, 1, 0);
        Lcd_string(&lcd, buffer);


        _delay_ms(500);
    }
}
