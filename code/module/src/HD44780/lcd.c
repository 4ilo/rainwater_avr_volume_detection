/*
 * lcd.c
 *
 *  Created on: 10/06/2020
 *  Author: Olivier Van den Eede
 */

#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "lcd.h"

#define DELAY(X) _delay_ms(X)
#define VALIDATE_RET(X) (X == 0) ? 0 : -1

#define MAX_BUFFER 11

/************************************** Static declarations **************************************/

static int8_t lcd_write_data(Lcd_HandleTypeDef * lcd, uint8_t data, uint8_t reg);
static int8_t lcd_write(Lcd_HandleTypeDef * lcd, uint8_t data, uint8_t len);


/************************************** Function definitions **************************************/

/**
 * Create new Lcd_HandleTypeDef and initialize the Lcd
 */
Lcd_HandleTypeDef Lcd_create(
    Lcd_PortType port[], Lcd_PinType pin[],
    Lcd_PortType rs_port, Lcd_PinType rs_pin,
    Lcd_PortType en_port, Lcd_PinType en_pin, Lcd_ModeTypeDef mode)
{
    Lcd_HandleTypeDef lcd;

    lcd.mode = mode;

    lcd.en_pin = en_pin;
    lcd.en_port = en_port;

    lcd.rs_pin = rs_pin;
    lcd.rs_port = rs_port;

    lcd.data_pin = pin;
    lcd.data_port = port;

    Lcd_init(&lcd);

    return lcd;
}

/**
 * Initialize 16x2-lcd without cursor
 */
int8_t Lcd_init(Lcd_HandleTypeDef * lcd)
{
    int8_t ret = 0;

    if (lcd->mode == LCD_4_BIT_MODE) {
        ret += lcd_write_data(lcd, 0x33, LCD_COMMAND_REG);
        ret += lcd_write_data(lcd, 0x32, LCD_COMMAND_REG);
        ret += lcd_write_data(lcd, FUNCTION_SET | OPT_N, LCD_COMMAND_REG);      // 4-bit mode
    }
    else {
        ret += lcd_write_data(lcd, FUNCTION_SET | OPT_DL | OPT_N, LCD_COMMAND_REG);
    }

    ret += lcd_write_data(lcd, CLEAR_DISPLAY, LCD_COMMAND_REG);                      // Clear screen
    ret += lcd_write_data(lcd, DISPLAY_ON_OFF_CONTROL | OPT_D, LCD_COMMAND_REG);     // Lcd-on, cursor-off, no-blink
    ret += lcd_write_data(lcd, ENTRY_MODE_SET | OPT_INC, LCD_COMMAND_REG);           // Increment cursor

    return VALIDATE_RET(ret);
}

/**
 * Write a number on the current position
 */
int8_t Lcd_int(Lcd_HandleTypeDef * lcd, int number)
{
    int8_t ret = 0;
    char buffer[MAX_BUFFER];

    ret += snprintf(buffer, MAX_BUFFER, "%d", number);
    ret += Lcd_string(lcd, buffer);

    return VALIDATE_RET(ret);
}

/**
 * Write a string on the current position
 */
int8_t Lcd_string(Lcd_HandleTypeDef * lcd, char * string)
{
    int8_t ret = 0;

    for(uint8_t i = 0; i < strlen(string); i++)
    {
        ret += lcd_write_data(lcd, string[i], LCD_DATA_REG);
    }

    return VALIDATE_RET(ret);
}

/**
 * Set the cursor position
 */
int8_t Lcd_cursor(Lcd_HandleTypeDef * lcd, uint8_t row, uint8_t col)
{
    return lcd_write_data(lcd, SET_DDRAM_ADDR | ((row * 0x40) + col), LCD_COMMAND_REG);
}


/************************************** Static function definition **************************************/

/**
 * Write a byte to the data or command register
 */
int8_t lcd_write_data(Lcd_HandleTypeDef * lcd, uint8_t data, uint8_t reg)
{
    int8_t ret = 0;

    ret = gpio_write(lcd->rs_port, lcd->rs_pin, reg);

    if(lcd->mode == LCD_4_BIT_MODE)
    {
        ret += lcd_write(lcd, data >> 4, LCD_NIB);
        ret += lcd_write(lcd, data & 0x0F, LCD_NIB);
    }
    else
    {
        ret += lcd_write(lcd, data, LCD_BYTE);
    }

    return VALIDATE_RET(ret);
}


/**
 * Set len bits on the bus and toggle the enable line
 */
int8_t lcd_write(Lcd_HandleTypeDef * lcd, uint8_t data, uint8_t len)
{
    uint8_t ret = 0;

    for(uint8_t i = 0; i < len; i++)
    {
        ret += gpio_write(lcd->data_port[i], lcd->data_pin[i], (data >> i) & 0x01);
    }

    ret += gpio_write(lcd->en_port, lcd->en_pin, 1);
    DELAY(10);
    ret += gpio_write(lcd->en_port, lcd->en_pin, 0);         // Data receive on falling edge

    return VALIDATE_RET(ret);
}
