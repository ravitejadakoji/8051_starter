#include <reg51.h>
#include "stdutils.h"
#include "gpio.h"

void GPIO_PinWrite(gpioPins_et enm_pinNum, uint8_t var_pinVal)
{
	uint8_t v_portNum;
	
	v_portNum = (enm_pinNum >> 3);
	enm_pinNum = enm_pinNum & 0x07;
	
	switch (v_portNum)
	{
		case 0:
			UpdateBit(P0,enm_pinNum,var_pinVal);
			break;
		
		case 1:
			UpdateBit(P1,enm_pinNum,var_pinVal);
			break;
		
		case 2:
			UpdateBit(P2,enm_pinNum,var_pinVal);
			break;
		
		case 3:
			UpdateBit(P3,enm_pinNum,var_pinVal);
			break;
	}
}



uint8_t GPIO_PinRead(gpioPins_et enm_pinNum)
{
	uint8_t v_portNum;
	uint8_t pinStatus = 0;
	
	v_portNum = (enm_pinNum >> 3);
	enm_pinNum = enm_pinNum & 0x07;
	
	switch (v_portNum)
	{
		case 0:
			pinStatus = IsBitSet(P0,enm_pinNum);
			break;
		
		case 1:
			pinStatus = IsBitSet(P1,enm_pinNum);
			break;
		
		case 2:
			pinStatus = IsBitSet(P2,enm_pinNum);
			break;
		
		case 3:
			pinStatus = IsBitSet(P3,enm_pinNum);
			break;
	}
	
	return pinStatus;
}
