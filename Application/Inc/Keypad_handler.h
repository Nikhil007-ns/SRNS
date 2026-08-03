/*
 * Keypad_handler.h
 *
 *  Created on: Jul 28, 2026
 *      Author: user
 */

#ifndef INC_KEYPAD_HANDLER_H_
#define INC_KEYPAD_HANDLER_H_

#include "main.h"

#define KEYPAD_ROWS   		4u
#define KEYPAD_COLUMNS 		4u

#define KEYPAD_DEBOUNCE_TIME_MS    20U

typedef struct
{
	 uint8_t debounce_flag ;
	 uint32_t prev_tick ;
	 uint8_t press_row;
	 uint8_t press_col;

}keypad_handler_t;


typedef enum
{
    KEY_IDLE = 0,
    KEY_DEBOUNCE_PRESS,
    KEY_PRESSED,
	KEY_WAIT_RELEASE,
    KEY_DEBOUNCE_RELEASE
}KEY_STATE_t;



/* Application Interface */
uint8_t KEYPAD_Handler(void);







#endif /* INC_KEYPAD_HANDLER_H_ */
