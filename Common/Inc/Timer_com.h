/*
 * Timer_com.h
 *
 *  Created on: Jul 29, 2026
 *      Author: Nikhil
 */

#ifndef INC_TIMER_COM_H_
#define INC_TIMER_COM_H_

#include "main.h"


void delay_ms(uint32_t Delay);
int soft_delay(volatile uint32_t *prev_tick, uint32_t delay_time);
void My_TIM_Base_start(void);

void MY_TIM6_Init(void);




#endif /* INC_TIMER_COM_H_ */
