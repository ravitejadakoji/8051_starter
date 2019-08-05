#ifndef __TIMER_H__
#define __TIMER_H__

#include "stdutils.h"

/**************************
Timer Macros and Constants
**************************/

#define Enable_TIMER0_INTR 0
#define Enable_TIMER1_INTR 0
#define Enable_TIMER2_INTR 0

#define MAX_TIMER_DELAY 71000

#define TIMERTICK 1.085 /*11.0592/12 = 1.08592*/

typedef void (*isrFunPtr_t)(void);

/**************************
Timer Function Prototypes
***************************/

void TIMER_Init(uint8_t var_timerNum, uint32_t var_timerIntervalUS);
void TIMER_Start(uint8_t var_timerNum);
void TIMER_Stop(uint8_t var_timerNum);

void TIMER_AttachIntr(uint8_t var_timerNum,isrFunPtr_t funPtr);

void TIMER_SetTime(uint8_t var_timerNum, uint32_t var_timerIntervalUS);
uint32_t TIMER_GetTime(uint8_t var_timerNum);

#endif
