/*
 * Keypad_handler.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Nikhil
 */
#include "main.h"

/*Common Layer headers*/
#include "Gpio_com.h"
#include "Timer_com.h"

/*Application Layer headers*/
#include "keypad_handler.h"


static KEY_STATE_t key_state = KEY_IDLE;
extern volatile unsigned int system_tick;
keypad_handler KeypadPress;
int8_t row, col;

	static const char keypad[4][4] =
	{
	    {'1','2','3','A'},
	    {'4','5','6','B'},
	    {'7','8','9','C'},
	    {'*','0','#','D'}
	};


uint8_t Keypad_Handler(void){

	return KEYPAD_GetKey();

}


/*designed for single key detection*/
uint8_t KEYPAD_GetKey(void)
{
    switch(key_state)
    {

        /* IDLE STATE */
        case KEY_IDLE:  /*when key not pressed , allowing to scan keypad*/

            for(row = 0; row < 4; row++)
            {
                KEYPAD_SelectRow(row);

                col = KEYPAD_ReadColumn();

                if(col != -1)
                {
                	KeypadPress.press_row = row;
                	KeypadPress.press_col = col;

                	KeypadPress.prev_tick = system_tick;

                    key_state = KEY_DEBOUNCE_PRESS;

                    break;
                }
            }

            break;

        /* DEBOUNCE STATE */
        case KEY_DEBOUNCE_PRESS: /*when any key pressed , changed idle state to keydebouncepress state , 20 ms elapsed for debounce*/

            if(soft_delay(&KeypadPress.prev_tick,20))
            {
                KEYPAD_SelectRow(KeypadPress.press_row);

                if(KEYPAD_ReadColumn() == KeypadPress.press_col) /*checking same key pressed during this time , if not debounce goes to else condition set to idle*/
                {
                    key_state = KEY_PRESSED;
                }
                else
                {
                    key_state = KEY_IDLE;
                }
            }

            break;

        /* KEY PRESSED */
        case KEY_PRESSED: /*after debounce , changed to key_pressed state here setting state to keywait_for_relese state and returning key only once avoiding repeated scan*/

            key_state = KEY_WAIT_RELEASE;

            return keypad[KeypadPress.press_row][KeypadPress.press_col];

        /* WAIT UNTIL RELEASE */
        case KEY_WAIT_RELEASE: /*purely waiting to relese the key and checking during this it is purely checking first pressed key to relese*/
        					   /*while press and hold first key if we pressed any other key  keypad_isanykeypressed () will not detect this press */
        						/*while holding 2nd key if we relese 1st key then this condition becomes true*/
            if(KEYPAD_IsSameKeyPressed(KeypadPress.press_row, KeypadPress.press_col ) == 0)
            {
                key_state = KEY_IDLE;
            }

            break;
    }

    return 0;
}
uint8_t KEYPAD_IsSameKeyPressed(uint8_t row, uint8_t col )
{


    KEYPAD_SelectRow(row);

        if(KEYPAD_ReadColumn() == col)
        {
            return 1;   // Same key is still pressed
        }

        return 0;                // No key is pressed
}
/*
uint8_t KEYPAD_GetKey(void)
{

    for(row = 0; row < 4; row++)
    {
        KEYPAD_SelectRow(row);

        col = KEYPAD_ReadColumn();

        if(col != -1)
        {
        	delay_ms(20);      //Debounce

            while(KEYPAD_ReadColumn() != -1);//This prevents repeated characters while the key is held.

            return keypad[row][col];
        }
    }

    return 0;
}
*/
 void KEYPAD_AllRowsLow(void)
{
    MY_GPIO_WritePin(ROW1_PORT, ROW1_PIN, gpio_pin_reset);
    MY_GPIO_WritePin(ROW2_PORT, ROW2_PIN, gpio_pin_reset);
    MY_GPIO_WritePin(ROW3_PORT, ROW3_PIN, gpio_pin_reset);
    MY_GPIO_WritePin(ROW4_PORT, ROW4_PIN, gpio_pin_reset);
}


 void KEYPAD_SelectRow(uint8_t row)
{
    KEYPAD_AllRowsLow();

    switch(row)
    {
        case 0:
            MY_GPIO_WritePin(ROW1_PORT, ROW1_PIN, gpio_pin_set);
            break;

        case 1:
            MY_GPIO_WritePin(ROW2_PORT, ROW2_PIN, gpio_pin_set);
            break;

        case 2:
            MY_GPIO_WritePin(ROW3_PORT, ROW3_PIN, gpio_pin_set);
            break;

        case 3:
            MY_GPIO_WritePin(ROW4_PORT, ROW4_PIN, gpio_pin_set);
            break;
    }
}
 int8_t KEYPAD_ReadColumn(void)
{
    if(MY_GPIO_ReadPin(COL1_PORT, COL1_PIN) == gpio_pin_set)
        return 0;

    if(MY_GPIO_ReadPin(COL2_PORT, COL2_PIN) == gpio_pin_set)
        return 1;

    if(MY_GPIO_ReadPin(COL3_PORT, COL3_PIN) == gpio_pin_set)
        return 2;

    if(MY_GPIO_ReadPin(COL4_PORT, COL4_PIN) == gpio_pin_set)
        return 3;

    return -1;
}
