/*
 * Timer_com.c
 *
 *  Created on: Jul 29, 2026
 *      Author: Nikhil
 */
#include "main.h"

/*Application Layer headers*/

/*Common Layer headers*/
#include "Timer_com.h"


TIM_HandleTypeDef htim6;

volatile unsigned int system_tick;
void delay_ms(uint32_t Delay)
{

	 HAL_Delay(Delay);


}

int soft_delay(volatile uint32_t *prev_tick, uint32_t delay_time)
{
    if((system_tick - *prev_tick) >= delay_time)
    {
        *prev_tick = system_tick;

        return 1;
    }

    return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == TIM6)
	{
		system_tick++;

	}

}
void My_TIM_Base_start(void)
{
	 HAL_TIM_Base_Start_IT(&htim6);

}


void MY_TIM6_Init(void)
 {

   /* USER CODE BEGIN TIM6_Init 0 */

   /* USER CODE END TIM6_Init 0 */

   TIM_MasterConfigTypeDef sMasterConfig = {0};

   /* USER CODE BEGIN TIM6_Init 1 */

   /* USER CODE END TIM6_Init 1 */
   htim6.Instance = TIM6;
   htim6.Init.Prescaler = 15;
   htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
   htim6.Init.Period = 999;
   htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
   if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
   {
     Error_Handler();
   }
   sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
   sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
   if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
   {
     Error_Handler();
   }
   /* USER CODE BEGIN TIM6_Init 2 */

   /* USER CODE END TIM6_Init 2 */

 }
