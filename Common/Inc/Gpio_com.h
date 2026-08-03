/*
 * Gpio_com.h
 *
 *  Created on: Jul 28, 2026
 *      Author: Nikhil
 */

#ifndef INC_GPIO_COM_H_
#define INC_GPIO_COM_H_


/* Rows */
#define  KEYPAD_ROW1_PORT 		 GPIOA
#define  KEYPAD_ROW1_PIN     	 GPIO_PIN_0

#define KEYPAD_ROW2_PORT  		 GPIOA
#define KEYPAD_ROW2_PIN     	 GPIO_PIN_1

#define KEYPAD_ROW3_PORT    	 GPIOA
#define KEYPAD_ROW3_PIN     	 GPIO_PIN_4

#define KEYPAD_ROW4_PORT       	 GPIOA
#define KEYPAD_ROW4_PIN     	 GPIO_PIN_5




/* Columns */
#define KEYPAD_COL1_PORT    	 GPIOB
#define KEYPAD_COL1_PIN     	 GPIO_PIN_0

#define KEYPAD_COL2_PORT    	 GPIOB
#define KEYPAD_COL2_PIN     	 GPIO_PIN_1

#define KEYPAD_COL3_PORT    	 GPIOB
#define KEYPAD_COL3_PIN     	 GPIO_PIN_2

#define KEYPAD_COL4_PORT    	 GPIOB
#define KEYPAD_COL4_PIN     	 GPIO_PIN_4

typedef enum
{
  gpio_pin_reset= 0,
  gpio_pin_set
}gpio_pinstate;


typedef enum
{
  hal_OK       = 0x00U,
  hal_ERROR    = 0x01U,
  hal_BUSY     = 0x02U,
  hal_TIMEOUT  = 0x03U
} hal_statustypedef;





typedef GPIO_TypeDef      gpio_typedef;

/* GPIO APIs */
gpio_pinstate MY_GPIO_ReadPin(gpio_typedef* GPIOx, uint16_t GPIO_Pin);
void MY_GPIO_WritePin(gpio_typedef* GPIOx, uint16_t GPIO_Pin, gpio_pinstate PinState);


/* System APIs */
void MY_GPIO_Init(void);
void MY_SystemClock_Config(void);



#endif /* INC_GPIO_COM_H_ */
