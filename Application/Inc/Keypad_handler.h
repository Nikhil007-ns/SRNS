/*
 * Keypad_handler.h
 *
 *  Created on: Jul 28, 2026
 *      Author: user
 */

#ifndef INC_KEYPAD_HANDLER_H_
#define INC_KEYPAD_HANDLER_H_

#include "main.h"

typedef struct KeyPad
{
	 uint8_t debounce_flag ;
	 uint32_t prev_tick ;
	 uint8_t press_row;
	 uint8_t press_col;

}keypad_handler;


typedef enum
{
    KEY_IDLE,
    KEY_DEBOUNCE_PRESS,
    KEY_PRESSED,
	KEY_WAIT_RELEASE,
    KEY_DEBOUNCE_RELEASE
}KEY_STATE_t;


uint8_t Keypad_Handler(void);
 void KEYPAD_AllRowsLow(void);
 void KEYPAD_SelectRow(uint8_t row);
 int8_t KEYPAD_ReadColumn(void);
uint8_t KEYPAD_GetKey(void);
uint8_t KEYPAD_IsSameKeyPressed(uint8_t row, uint8_t col );
#endif /* INC_KEYPAD_HANDLER_H_ */
