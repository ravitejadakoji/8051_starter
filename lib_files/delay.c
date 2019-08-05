#include "delay.h"

void delay_us(uint16_t var_Count_us)
{
	while(var_Count_us != 0)
	{
		var_Count_us--;
	}
}

void delay_ms(uint16_t var_Count_ms)
{
	while(var_Count_ms != 0)
	{
		delay_us(C_OneMSDelayCount);
		var_Count_ms--;
	}
}

#if (ENABLE_DELAY_SEC == 1)
void delay_sec(uint16_t var_Count_sec)
{
	while(var_Count_sec != 0)
	{
		delay_ms(1000);
		var_Count_sec--;
	}
}

#endif
