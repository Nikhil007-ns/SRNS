/*
 * Gpio_com.h
 *
 *  Created on: Jul 28, 2026
 *      Author: Nikhil
 */

#ifndef INC_GPIO_COM_H_
#define INC_GPIO_COM_H_


/* Rows */
#define ROW1_PORT    GPIOA
#define ROW1_PIN     GPIO_PIN_0

#define ROW2_PORT    GPIOA
#define ROW2_PIN     GPIO_PIN_1

#define ROW3_PORT    GPIOA
#define ROW3_PIN     GPIO_PIN_4

#define ROW4_PORT    GPIOA
#define ROW4_PIN     GPIO_PIN_5




/* Columns */
#define COL1_PORT    GPIOB
#define COL1_PIN     GPIO_PIN_0

#define COL2_PORT    GPIOB
#define COL2_PIN     GPIO_PIN_1

#define COL3_PORT    GPIOB
#define COL3_PIN     GPIO_PIN_2

#define COL4_PORT    GPIOB
#define COL4_PIN     GPIO_PIN_4

typedef enum
{
  gpio_pin_reset= 0,
  gpio_pin_set
}gpio_pinstate;




typedef GPIO_TypeDef      gpio_typedef;



gpio_pinstate MY_GPIO_ReadPin(gpio_typedef* GPIOx, uint16_t GPIO_Pin);
void MY_GPIO_WritePin(gpio_typedef* GPIOx, uint16_t GPIO_Pin, gpio_pinstate PinState);



void MY_GPIO_Init(void);
void MY_SystemClock_Config(void);



#endif /* INC_GPIO_COM_H_ */
