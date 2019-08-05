#ifndef I2C_H
#define I2C_H

#include <reg51.h>
#include "stdutils.h"


/****************************
I2C Pins (SCL & SDA) Config
*****************************/

sbit SCL_PIN = P0^6;
sbit SDA_PIN = P0^7;

#define SCL_Dir SCL_PIN
#define SDA_Dir SDA_PIN


/*************************
I2C Function Prototypes
**************************/

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t var_I2CData);
uint8_t I2C_Read(uint8_t var_ackOpt);


#endif
