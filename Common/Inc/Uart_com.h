/*
 * Uart_com.h
 *
 *  Created on: Jul 28, 2026
 *      Author: user
 */

#ifndef INC_UART_COM_H_
#define INC_UART_COM_H_
#include "main.h"



typedef UART_HandleTypeDef             uart_handletypedef;
typedef HAL_StatusTypeDef              MY_StatusTypeDef;


void MY_USART1_UART_Init(void);
void MY_USART2_UART_Init(void);


MY_StatusTypeDef UART1_Transmit(uart_handletypedef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
MY_StatusTypeDef UART1_Receive(uart_handletypedef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);



MY_StatusTypeDef UART2_Transmit(uart_handletypedef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
MY_StatusTypeDef UART2_Receive(uart_handletypedef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);


#endif /* INC_UART_COM_H_ */
