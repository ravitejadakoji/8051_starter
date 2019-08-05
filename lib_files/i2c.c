#include "i2c.h"
#include "delay.h"


/*****************************
I2C Local Function Prototypes
*****************************/

static void i2c_Clock(void);
static void i2c_Ack(void);
static void i2c_Noack(void);

/****************************
I2C Local Functions
****************************/

static void i2c_Clock(void)
{
	delay_us(1);
	SCL_PIN = 1;
	delay_us(1);
	SCL_PIN = 0;
}

/*****************************/

static void i2c_Ack(void)
{
	SDA_PIN = 0;
	i2c_Clock();
	SDA_PIN = 1;
}

/*****************************/

static void i2c_Noack(void)
{
	SDA_PIN = 1;
	i2c_Clock();
	SCL_PIN = 1;
}

/****************************/

/***************************
I2C Functions
***************************/

void I2C_Init(void)
{
	
}


/***************************/

void I2C_Start(void)
{
	SCL_PIN = 0;
	SDA_PIN = 1;
	delay_us(1);
	SCL_PIN = 1;
	delay_us(1);
	SDA_PIN = 0;
	delay_us(1);
	SCL_PIN = 0;
	
}

/***************************/

void I2C_Stop(void)
{
	SCL_PIN = 0;
	delay_us(1);
	SDA_PIN = 0;
	delay_us(1);
	SCL_PIN = 1;
	delay_us(1);
	SDA_PIN = 1;
}

/***************************/

void I2C_Write(uint8_t var_I2CData)
{
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		SDA_PIN = (var_I2CData & 0x80);
		i2c_Clock();
		var_I2CData = var_I2CData << 1;
	}
	
	i2c_Clock();
}

/***************************/

uint8_t I2C_Read(uint8_t var_ackOpt)
{
	uint8_t i, v_I2CData = 0x00;
	
	SDA_PIN = 1;
	
	for (i=0;i<8;i++)
	{
		delay_us(1);
		SCL_PIN = 1;
		delay_us(1);
		
		v_I2CData = v_I2CData << 1;
		v_I2CData = v_I2CData | SDA_PIN;
		
		SCL_PIN = 0;
	}
	
	if(var_ackOpt == 1)
	{
		i2c_Ack();
	}
	
	else
	{
		i2c_Noack();
	}
	
	return v_I2CData;
}

