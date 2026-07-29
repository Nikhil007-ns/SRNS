/*
 * Uart_com.c
 *
 *  Created on: Jul 28, 2026
 *      Author: Nikhil
 */

#include "main.h"

/*Application Layer headers*/

/*Common Layer headers*/
#include "Uart_com.h"


uart_handletypedef huart1;
uart_handletypedef huart2;


MY_StatusTypeDef UART2_Transmit(uart_handletypedef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return HAL_UART_Transmit(huart, pData, Size, Timeout);

}


MY_StatusTypeDef UART2_Receive(uart_handletypedef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return HAL_UART_Transmit(huart, pData, Size, Timeout);

}


MY_StatusTypeDef UART1_Transmit(uart_handletypedef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return HAL_UART_Transmit(huart, pData, Size, Timeout);

}


MY_StatusTypeDef UART1_Receive(uart_handletypedef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	return HAL_UART_Transmit(huart, pData, Size, Timeout);

}

void MY_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void MY_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
