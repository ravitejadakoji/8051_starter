#include <reg51.h>
#include "timer.h"
#include "stdutils.h"

#if (Enable_TIMER0_INTR == 1)
	uint16_t v_timer0_reloadVal = 0;
	uint16_t v_timer0_ovfCount = 0;
	isFunPtr_t Timer0_UserCallBack = NULL;
#endif

#if (Enable_TIMER1_INTR == 1)
	uint16_t v_timer1_reloadVal = 0;
	uint16_t v_timer1_ovfCount = 0;
	isFunPtr_t Timer1_UserCallBack = NULL;
#endif

#if (Enable_TIMER2_INTR == 1)
	uint16_t v_timer2_reloadVal = 0;
	uint16_t v_timer2_ovfCount = 0;
	isFunPtr_t Timer2_UserCallBack = NULL;
#endif

/***************************************/

void TIMER_Init(uint8_t var_timerNum, uint32_t var_timerIntervalUS)
{
	TIMER_SetTime(var_timerNum,var_timerIntervalUS);
	
}

/***************************************/

void TIMER_Start(uint8_t var_timerNum)
{
	switch(var_timerNum)
	{
		#if (Enable_TIMER0_INTR == 1)
		case 0:
			v_timer0_ovfCount = 0;
			TMOD |= 0x01;
			TL0 = (v_timer0_reloadVal & 0xFF);
			TH0 = ((v_timer0_reloadVal >> 8) & 0xFF);
			TR0 = 1;
			ET0 = 1;
			break;
		#endif
		
		#if (Enable_TIMER1_INTR == 1)
		case 1:
			v_timer1_ovfCount = 0;
			TMOD |= 0x10;
			TL1 = (v_timer1_reloadVal & 0xFF);
			TH1 = ((v_timer1_reloadVal >> 8) & 0xFF);
			TR1 = 1;
			ET1 = 1;
			break;
		#endif
		
		#if (Enable_TIMER2_INTR == 1)
		case 2:
			v_timer1_ovfCount = 0;
			TMOD |= 0x01;
			RCAP2L = (v_timer2_reloadVal & 0xFF);
			RCAP2H = ((v_timer2_reloadVal >> 8) & 0xFF);
			TR2 = 1;
			ET2 = 1;
			break;
		#endif
		
	}
	
}

/*********************************************/

void TIMER_Stop(uint8_t var_timerNum)
{
	switch(var_timerNum)
	{
		#if (Enable_TIMER0_INTR == 1)
		case 0:
			TR0 = 0;
			break;
		#endif
		
		#if (Enable_TIMER1_INTR == 1)
		case 1:
			TR1 = 0;
			break;
		#endif
		
		#if (Enable_TIMER2_INTR == 1)
		case 2:
			TR2 = 0;
			break;
		#endif
		
	}
	
}

/***************************************/

void TIMER_AttachIntr(uint8_t var_timerNum, isrFunPtr_t funPtr)
{
	switch(var_timerNum)
	{
		#if (Enable_TIMER0_INTR == 1)
		case 0:
			Timer0_UserCallBack = funPtr;
			break;
		#endif
		
		#if (Enable_TIMER1_INTR == 1)
		case 1:
			Timer1_UserCallBack = funPtr;
			break;
		#endif
		
		#if (Enable_TIMER2_INTR == 1)
		case 2:
			Timer2_UserCallBack = funPtr;
			break;
		#endif
		
	}
	
}

/*******************************************/

void TIMER_SetTime(uint8_t var_timerNum,uint32_t var_timerIntervalUS)
{
	uint16_t reloadVal;
	if(var_timerIntervalUS <= MAX_TIMER_DELAY)
	{
		reloadVal = (uint32_t)65536 - (var_timerIntervalUS / TIMERTICK);
		switch(var_timerNum)
		{
			#if (Enable_TIMER0_INTR == 1)
			case 0:
				v_timer0_reloadVal = reloadVal;
				break;
			#endif
				
			#if (Enable_TIMER1_INTR == 1)
			case 1:
				v_timer1_reloadVal = reloadVal;
				break;
			#endif
				
			#if (Enable_TIMER2_INTR == 1)
			case 2:
				v_timer2_reloadVal = reloadVal;
				break;
			#endif
		
		}
	}
}

/*******************************************/

uint32_t TIMER_GetTime(uint8_t timerNum)
{
	uint32_t timerDelay = 0;
	uint32_t timerCount = 0;
	
	switch(timerNum)
	{
		#if (Enable_TIMER0_INTR == 1)
		case 0:
			timerDelay = (v_timer0_reloadVal * v_timer0_ovfCount);
			timerCount = (((uint16_t)TH0<<8) + TL0);
			if(timerCount > v_timer0_reloadVal)
			{
				timerDelay = timerDelay + timerCount;
			}
			break;
		#endif
			
		#if (Enable_TIMER1_INTR == 1)
		case 1:
			timerDelay = (v_timer1_reloadVal * v_timer1_ovfCount);
			timerCount = (((uint16_t)TH1<<8) + TL1);
			if(timerCount > v_timer1_reloadVal)
			{
				timerDelay = timerDelay + timerCount;
			}
			break;
		#endif

		#if (Enable_TIMER2_INTR == 1)
		case 2:
			timerDelay = (v_timer2_reloadVal * v_timer2_ovfCount);
			timerCount = (((uint16_t)RCAP2H<<8) + RCAP2L);
			if(timerCount > v_timer2_reloadVal)
			{
				timerDelay = timerDelay + timerCount;
			}
			break;
		#endif			
	}
	
	timerDelay = timerDelay * TIMERTICK;
	return timerDelay;
}

/**************************************************************/


#if (Enable_TIMER0_INTR == 1)
void timer0_isr() interrupt 1
{
	TL0 = (v_timer0_reloadVal & 0xFF);
	TH0 = ((v_timer0_reloadVal >> 8) & 0xFF);)
	v_timer0_ovfCount++;
	
	if(Timer0_UserCallBack != NULL)
	{
		Timer0_UserCallBack();
	}
}
#endif


#if (Enable_TIMER1_INTR == 1)
void timer1_isr() interrupt 3
{
	TL1 = (v_timer1_reloadVal & 0xFF);
	TH1 = ((v_timer1_reloadVal >> 8) & 0xFF);)
	v_timer1_ovfCount++;
	
	if(Timer1_UserCallBack != NULL)
	{
		Timer1_UserCallBack();
	}
}
#endif


#if (Enable_TIMER2_INTR == 1)
void timer2_isr() interrupt 5
{
	RCAP2L = (v_timer2_reloadVal & 0xFF);
	RCAP2H = ((v_timer2_reloadVal >> 8) & 0xFF);)
	TF2 = 0;
	v_timer2_ovfCount++;
	
	if(Timer2_UserCallBack != NULL)
	{
		Timer2_UserCallBack();
	}
}
#endif

