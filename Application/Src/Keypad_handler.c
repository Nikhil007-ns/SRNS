/*
 * Keypad_handler.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Nikhil
 */
#include "main.h"
#include "Gpio_com.h"
#include "keypad_handler.h"

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


char KEYPAD_GetKey(void)
{

    for(row = 0; row < 4; row++)
    {
        KEYPAD_SelectRow(row);

        col = KEYPAD_ReadColumn();

        if(col != -1)
        {
            HAL_Delay(20);      // Debounce

            while(KEYPAD_ReadColumn() != -1);

            return keypad[row][col];
        }
    }

    return 0;
}
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
