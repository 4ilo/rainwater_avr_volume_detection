#include <avr/io.h>
#include <util/delay.h>

#include "gpio/gpio.h"
#include "HD44780/lcd.h"


int main(void)
{
    gpio_init(PORT_B, PIN_0, GPIO_OUT);

    gpio_init(PORT_C, 0, GPIO_OUT);
    gpio_init(PORT_C, 1, GPIO_OUT);
    gpio_init(PORT_C, 2, GPIO_OUT);
    gpio_init(PORT_C, 3, GPIO_OUT);
    gpio_init(PORT_C, 4, GPIO_OUT);
    gpio_init(PORT_C, 5, GPIO_OUT);

    gpio_init(PORT_C, 0, GPIO_OUT);
    gpio_init(PORT_D, 7, GPIO_OUT);
    gpio_init(PORT_D, 6, GPIO_OUT);
    gpio_init(PORT_D, 5, GPIO_OUT);

    //Lcd_PortType ports[] = {PORT_B, PORT_D, PORT_D, PORT_D,
    //                         PORT_C, PORT_C, PORT_C, PORT_C};
    //Lcd_PinType pins[] = {0, 7, 6, 5,
    //                        2, 3, 4, 5};
    Lcd_PortType ports[] = {PORT_C, PORT_C, PORT_C, PORT_C};
    Lcd_PinType pins[] = {2, 3, 4, 5};
    Lcd_HandleTypeDef lcd;

    lcd = Lcd_create(ports, pins, PORT_C, PIN_0, PORT_C, PIN_1, LCD_4_BIT_MODE);

    Lcd_cursor(&lcd, 1, 0);
    Lcd_string(&lcd, "Hello");

    while (1) {
//        gpio_write(PORT_B, PIN_0, 1);
        _delay_ms(1000);
//
//        gpio_write(PORT_B, PIN_0, 0);
//        _delay_ms(1000);
    }
}
