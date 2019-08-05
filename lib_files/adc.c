#include "adc.h"
#include "delay.h"
#include "stdutils.h"


void ADC_Init()
{
	ADC_START = 0;
	ADC_ALE = 0;
	ADC_OE = 0;
	ADC_EOC = 1;
	
	ADC_DataBus = 0xFF;
}

uint16_t ADC_GetADCVal(uint8_t var_adcCha)
{
	uint16_t adc_result;
	
	ADC_A = ((var_adcCha >> 0)&0x01);
	ADC_B = ((var_adcCha >> 1)&0x01);
	ADC_C = ((var_adcCha >> 2)&0x01);
	
	ADC_ALE = 1;
	delay_us(50);
	ADC_START = 1;
	delay_us(50);
	
	ADC_ALE = 0;
	delay_us(50);
	ADC_START = 0;
	
	while(ADC_EOC == 0);
	
	ADC_OE = 1;
	delay_us(25);
	adc_result = ADC_DataBus;
	ADC_OE = 0;
	
	return (adc_result);
}
