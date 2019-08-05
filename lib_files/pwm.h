#ifndef __PWM_H__
#define __PWM_H__

#include <reg51.h>
#include "stdutils.h"

/*************************
PWM Pins & Config
*************************/

#define Enable_PWM_0 1
#define Enable_PWM_1 1

sbit PWM0_PIN = P3^6;
sbit PWM1_PIN = P3^7;

/***********************
PWM Function Prototypes
***********************/

void PWM_Init(void);
void PWM_SetDutyCycle(uint8_t pwmChannel, uint8_t dutyCycle);
void PWM_Start(uint8_t pwmChannel);
void PWM_Stop(uint8_t pwmChannel);

#endif
