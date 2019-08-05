#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "gpio.h"
#include "stdutils.h"

/**************************
Keypad Row/Column Configs
**************************/

#define C_MaxRows (4)
#define C_MaxCols (4)
#define C_DebounceMicro (10)
#define C_DefaultKey ('x')


/***************************
Keypad Function Prototypes
****************************/

uint8_t KEYPAD_GetKet();
void KEYPAD_Init(
			gpioPins_et row_0,
			gpioPins_et row_1,
			gpioPins_et row_2,
			gpioPins_et row_3,
			gpioPins_et col_0,
			gpioPins_et col_1,
			gpioPins_et col_2,
			gpioPins_et col_3);

#endif
