#ifndef _ADC_H
#define _ADC_H

#include <reg51.h>
#include "stdutils.h"

/*****************************
ADC Pin Configurations
*****************************/

#define ADC_DataBus P2

sbit ADC_A = P1^0;
sbit ADC_B = P1^1;
sbit ADC_C = P1^2;

sbit ADC_ALE 		= P1^3;
sbit ADC_START 	= P1^4;
sbit ADC_EOC 		= P1^5;
sbit ADC_OE 		= P1^6;


/*****************************
ADC Function Prototypes
*****************************/

void ADC_Init();
uint16_t ADC_GetADCVal(uint8_t var_adcCha);

#endif
