#include <reg51.h>
//#include <reg52.h>
#include "pwm.h"
#include "stdutils.h"

#if (Enable_PWM_0 == 1)
	uint8_t v_pwm0_DutyCycle = 50;
	uint8_t v_pwm0_Enabled = 0;
#endif

#if (Enable_PWM_1 == 1)
	uint8_t v_pwm1_DutyCycle = 50;
	uint8_t v_pwm1_Enabled = 0;
#endif

/*****************************************/

void PWM_Init(void)
{
	RCAP2L = 200;
	RCAP2H = 0xFF;
	ET2 = 1;
}

/****************************************/

void PWM_SetDutyCycle(uint8_t pwmChannel, uint8_t dutyCycle)
{
	if(dutyCycle>100)
		dutyCycle = 100;
	
	switch(pwmChannel)
	{
		#if (Enable_PWM_0 == 1)
		case 0:
			v_pwm0_DutyCycle = dutyCycle;
			break;
		#endif
		
		#if (Enable_PWM_1 == 1)
		case 1:
			v_pwm1_DutyCycle = dutyCycle;
			break;
		#endif
		
	}
}

/**********************************************/

void PWM_Start(uint8_t pwmChannel)
{
	switch(pwmChannel)
	{
		#if (Enable_PWM_0 == 1)
		case 0:
			v_pwm0_Enabled = 1;
			TR2 = 1;
			EnableGlobalInterrupts();
			break;
		#endif
		
		#if (Enable_PWM_1 == 1)
		case 1:
			v_pwm1_Enabled = 1;
			TR2 = 1;
			EnableGlobalInterrupts();
			break;
		#endif
		
	}
	
}

/*******************************************/

void PWM_Stop(uint8_t pwmChannel)
{
	uint8_t pwm_EnDis = 0;
	
	switch(pwmChannel)
	{
		#if (Enable_PWM_0 == 1)
		case 0:
			v_pwm0_Enabled = 0;
			break;
		#endif
		
		#if (Enable_PWM_1 == 1)
		case 1:
			v_pwm1_Enabled = 0;
			break;
		#endif
		
	}
	
	#if (Enable_PWM_0 == 1)
		pwm_EnDis |= v_pwm0_Enabled;
	#endif
	
	#if (Enable_PWM_1 == 1)
		pwm_EnDis |= v_pwm1_Enabled;
	#endif
	
	TR2 = pwm_EnDis;
	
}

/******************
Timer2 ISR
******************/

#if ((Enable_PWM_0 == 1) || (Enable_PWM_1 == 1))
volatile uint8_t cycleTime = 0;
void timer_isr() interrupt 5
{
	TF2 = 0;
	if(cycleTime >= 100)
	{
		cycleTime = 0;
	}
	
	else 
	{
		cycleTime++;
	}
	
	#if (Enable_PWM_0 == 1)
		if(v_pwm0_Enabled == 1)
		{
			if(cycleTime == v_pwm0_DutyCycle)
			{
				PWM0_PIN = 0;
			}
			else if(cycleTime == 0)
			{
				PWM0_PIN = 1;
			}
		}
	#endif
		
	#if (Enable_PWM_1 == 1)
		if(v_pwm1_Enabled == 1)
		{
			if(cycleTime == v_pwm1_DutyCycle)
			{
				PWM1_PIN = 0;
			}
			else if(cycleTime == 0)
			{
				PWM1_PIN = 1;
			}
		}
	#endif
		
}
#endif
