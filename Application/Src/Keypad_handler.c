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
#include "Uart_com.h"
extern uart_handletypedef huart2;

/*Application Layer headers*/
#include "keypad_handler.h"



/* Driver Interface */

static uint8_t KEYPAD_GetKey(void);
static uint8_t KEYPAD_Scan(void);

/* Internal Hardware Interface */

static void KEYPAD_SelectRow(uint8_t row);
static int8_t KEYPAD_ReadColumn(void);

static void KEYPAD_AllRowsLow(void);

static uint8_t KEYPAD_IsSameKeyPressed(uint8_t row, uint8_t col);

static void KEYPAD_Debounce_Press_check(void);
static void KEYPAD_Debounce_Release_check(void);

char buf[30];
extern volatile uint32_t system_tick;

static KEY_STATE_t key_state = KEY_IDLE;
static keypad_handler_t KeypadContext;

	static const char keypad[4][4] =
	{
	    {'1','2','3','A'},
	    {'4','5','6','B'},
	    {'7','8','9','C'},
	    {'*','0','#','D'}
	};


uint8_t KEYPAD_Handler(void){

	return KEYPAD_GetKey();

}


/*designed for single key detection*/
static uint8_t KEYPAD_GetKey(void)
{
    switch(key_state)
    {

        /* IDLE STATE */
        case KEY_IDLE:  /*when key not pressed , allowing to scan keypad*/

            if(KEYPAD_Scan())
            {
            	KeypadContext.prev_tick = system_tick;
                key_state = KEY_DEBOUNCE_PRESS;
            }

//								for(row = 0; row < 4; row++)
//								{
//									KEYPAD_SelectRow(row);
//
//									col = KEYPAD_ReadColumn();
//
//									if(col != -1)
//									{
//										KeypadPress.press_row = row;
//										KeypadPress.press_col = col;
//										KeypadPress.prev_tick = system_tick;
//
//										key_state = KEY_DEBOUNCE_PRESS;
//
//										break;
//									}
//								}

								break;

        /* DEBOUNCE STATE */
        case KEY_DEBOUNCE_PRESS: /*when any key pressed , changed idle state to keydebouncepress state , 20 ms elapsed for debounce*/

								if(soft_delay(&KeypadContext.prev_tick,KEYPAD_DEBOUNCE_TIME_MS))
								{
									KEYPAD_Debounce_Press_check();
								}

								break;

        /* KEY PRESSED */
        case KEY_PRESSED: /*after debounce , changed to key_pressed state here setting state to keywait_for_relese state and returning key only once avoiding repeated scan*/

									key_state = KEY_WAIT_RELEASE;

									sprintf(buf, "%d\r\n",keypad[KeypadContext.press_row][KeypadContext.press_col]);
									UART2_Transmit(&huart2, buf, strlen(buf), 1000);

									return keypad[KeypadContext.press_row][KeypadContext.press_col];//if not returning , every time scanning returning keypad data continously

        /* WAIT UNTIL RELEASE */
        case KEY_WAIT_RELEASE: /*purely waiting to release the key and checking during this it is purely checking first pressed key to relese*/
        					   /*while press and hold first key if we pressed any other key  keypad_isanykeypressed () will not detect this press */
        						/*while holding 2nd key if we relese 1st key then this condition becomes true*/

//								if(KEYPAD_IsSameKeyPressed(KeypadPress.press_row, KeypadPress.press_col ) == 0)
//								{
//									KeypadPress.prev_tick = system_tick;
//									key_state = KEY_DEBOUNCE_RELEASE;
//								}
//
//								break;

								 if(!KEYPAD_IsSameKeyPressed(KeypadContext.press_row,
										 	 	 	 	 	 KeypadContext.press_col))
								    {
									 KeypadContext.prev_tick = system_tick;
								        key_state = KEY_DEBOUNCE_RELEASE;
								    }
								 /* if we return also , every time scan will receive keypad press value only to avoid this in pressed state returning data
								  *  sprintf(buf, "%d\r\n",keypad[KeypadContext.press_row][KeypadContext.press_col]);
								  *  UART2_Transmit(&huart2, buf, strlen(buf), 1000);
								  *  return keypad[KeypadContext.press_row][KeypadContext.press_col];
								  *
								  */
								 break;
        case KEY_DEBOUNCE_RELEASE:	if(soft_delay(&KeypadContext.prev_tick,KEYPAD_DEBOUNCE_TIME_MS))
									{
        								KEYPAD_Debounce_Release_check();
									}

									break;
         default:
        			key_state = KEY_IDLE;
        			break;

    }

    return 0;
}
static uint8_t KEYPAD_Scan(void)
{
    int8_t row, col;

    for(row = 0; row < KEYPAD_ROWS; row++)
    {
        KEYPAD_SelectRow(row);

        col = KEYPAD_ReadColumn();

        if(col != -1)
        {
        	KeypadContext.press_row = row;
        	KeypadContext.press_col = col;
            return 1;
        }
    }

    return 0;
}
static uint8_t KEYPAD_IsSameKeyPressed(uint8_t row, uint8_t col )
{
	  KEYPAD_SelectRow(row);

	    return (KEYPAD_ReadColumn() == col);

//         if(KEYPAD_ReadColumn() == col)
//         {
//            return 1;   // Same key is still pressed
//         }
//          return 0;                // No key is pressed

}
static void KEYPAD_Debounce_Release_check(void)
{


	   if(KEYPAD_IsSameKeyPressed(KeypadContext.press_row, KeypadContext.press_col))
	   {
		/* Release was not stable (bounce) */
		key_state = KEY_WAIT_RELEASE;
	   }
	   else
	   {
		   /* Release confirmed */
		key_state = KEY_IDLE;
       }
}

static void KEYPAD_Debounce_Press_check(void)
{
	   if(KEYPAD_IsSameKeyPressed(KeypadContext.press_row,
			   	   	   	   	   	  KeypadContext.press_col))
	    {
	        /* Valid key press */
	        key_state = KEY_PRESSED;
	    }
	    else
	    {
	        /* Press bounce */
	        key_state = KEY_IDLE;
	    }

//	KEYPAD_SelectRow(KeypadPress.press_row);
//
//	if(KEYPAD_ReadColumn() == KeypadPress.press_col) /*checking same key pressed during this time , if not debounce goes to else condition set to idle*/
//	{
//		key_state = KEY_PRESSED;
//	}
//	else
//	{
//		key_state = KEY_IDLE;
//	}
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
 static void KEYPAD_AllRowsLow(void)
{
    MY_GPIO_WritePin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, gpio_pin_reset);
    MY_GPIO_WritePin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, gpio_pin_reset);
    MY_GPIO_WritePin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, gpio_pin_reset);
    MY_GPIO_WritePin(KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN, gpio_pin_reset);
}


static void KEYPAD_SelectRow(uint8_t row)
{
    KEYPAD_AllRowsLow();

    switch(row)
    {
        case 0:
            MY_GPIO_WritePin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, gpio_pin_set);
            break;

        case 1:
            MY_GPIO_WritePin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, gpio_pin_set);
            break;

        case 2:
            MY_GPIO_WritePin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, gpio_pin_set);
            break;

        case 3:
            MY_GPIO_WritePin(KEYPAD_ROW4_PORT, KEYPAD_ROW4_PIN, gpio_pin_set);
            break;
    }
}

static int8_t KEYPAD_ReadColumn(void)
{
    if(MY_GPIO_ReadPin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN) == gpio_pin_set)
        return 0;

    if(MY_GPIO_ReadPin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN) == gpio_pin_set)
        return 1;

    if(MY_GPIO_ReadPin(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN) == gpio_pin_set)
        return 2;

    if(MY_GPIO_ReadPin(KEYPAD_COL4_PORT, KEYPAD_COL4_PIN) == gpio_pin_set)
        return 3;

    return -1;
}
