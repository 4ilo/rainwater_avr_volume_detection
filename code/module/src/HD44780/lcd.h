/*
 * lcd.h
 *
 *  Created on: 10/06/2020
 *  Author: Olivier Van den Eede
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include "gpio/gpio.h"

/************************************** Command register **************************************/
#define CLEAR_DISPLAY 0x01

#define RETURN_HOME 0x02

#define ENTRY_MODE_SET 0x04
#define OPT_S	0x01					// Shift entire display to right
#define OPT_INC 0x02					// Cursor increment

#define DISPLAY_ON_OFF_CONTROL 0x08
#define OPT_D	0x04					// Turn on display
#define OPT_C	0x02					// Turn on cursor
#define OPT_B	0x01					// Turn on cursor blink

#define CURSOR_DISPLAY_SHIFT 0x10		// Move and shift cursor
#define OPT_SC 0x08
#define OPT_RL 0x04

#define FUNCTION_SET 0x20
#define OPT_DL 0x10						// Set interface data length
#define OPT_N 0x08						// Set number of display lines
#define OPT_F 0x04						// Set alternate font

#define SET_DDRAM_ADDR 0x80				// Set DDRAM address


/************************************** LCD defines **************************************/
#define LCD_NIB 4
#define LCD_BYTE 8
#define LCD_DATA_REG 1
#define LCD_COMMAND_REG 0

#define Lcd_PortType uint8_t
#define Lcd_PinType uint8_t

typedef enum {
    LCD_4_BIT_MODE,
    LCD_8_BIT_MODE
} Lcd_ModeTypeDef;


typedef struct {
    Lcd_PortType * data_port;
    Lcd_PinType * data_pin;

    Lcd_PortType rs_port;
    Lcd_PinType rs_pin;

    Lcd_PortType en_port;
    Lcd_PinType en_pin;

    Lcd_ModeTypeDef mode;
} Lcd_HandleTypeDef;


/************************************** Public functions **************************************/
int8_t Lcd_init(Lcd_HandleTypeDef * lcd);
int8_t Lcd_int(Lcd_HandleTypeDef * lcd, int number);
int8_t Lcd_string(Lcd_HandleTypeDef * lcd, char * string);
int8_t Lcd_cursor(Lcd_HandleTypeDef * lcd, uint8_t row, uint8_t col);
Lcd_HandleTypeDef Lcd_create(
    Lcd_PortType port[], Lcd_PinType pin[],
    Lcd_PortType rs_port, Lcd_PinType rs_pin,
    Lcd_PortType en_port, Lcd_PinType en_pin, Lcd_ModeTypeDef mode);



#endif /* LCD_H_ */
