#ifndef UART_H
#define UART_H

#include <reg51.h>
#include "stdutils.h"

/*****************************
UART Baud Rate Config
****************************/

#define C_MaxBaudRate 115200UL
#define C_MinBaudRate 2400
#define CPU_F 11059200UL
#define C_ControllerPrescale 387U

#define M_GetBaudRateValue(baudrate) -(CPU_F / (C_ControllerPrescale * baudrate))


/***********************************
Configs to Enable/Disable UART API's
*************************************/

#define Enable_UART_TXSTR 1
#define Enable_UART_RXSTR 1
#define Enable_UART_TXNum 1
#define Enable_UART_TXFloat 1
#define Enable_UART_Printf 1


/****************************************
			UART Constants and Macros
****************************************/

#define C_DefaultDigitsToTX 0xFFu
#define C_MaxDigitsToTX 10u
#define C_BinaryBitsToTX 16u
#define C_MaxDigitsToTXPrintf C_DefaultDigitsToTX


/************************
UART Function Prototypes
************************/

void UART_Init(uint32_t var_baudRate);
void UART_SetBaudRate(uint32_t var_baudRate);

void UART_TXChar(char var_txData);
char UART_RXChar(void);

void UART_TXSTR(char *ptr_str);
uint8_t UART_RXSTR(char *ptr_str);

void UART_TXNum(uint8_t var_numSys, uint32_t var_number_32, uint8_t var_numOfDigitsToTX);
void UART_TXFloat(float var_floatNum_32);

void UART_Printf(const char *argList, ...);

#endif
