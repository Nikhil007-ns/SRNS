/*
 * Keypad_handler.h
 *
 *  Created on: Jul 28, 2026
 *      Author: user
 */

#ifndef INC_KEYPAD_HANDLER_H_
#define INC_KEYPAD_HANDLER_H_

#include "main.h"


uint8_t Keypad_Handler(void);
 void KEYPAD_AllRowsLow(void);
 void KEYPAD_SelectRow(uint8_t row);
 int8_t KEYPAD_ReadColumn(void);
char KEYPAD_GetKey(void);


#endif /* INC_KEYPAD_HANDLER_H_ */
