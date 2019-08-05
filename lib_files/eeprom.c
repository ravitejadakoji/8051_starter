#include "eeprom.h"
#include "i2c.h"
#include "delay.h"

void EEPROM_WriteByte(uint16_t var_eepromAdd, uint8_t var_eepromData)
{
	uint8_t v_eepromLowAdd;
	uint8_t v_eepromPageNum;
	uint8_t v_eepromID = C_EEPROMIDWrite;
	
	#if (C_EEPROMICType > AT24C16)
		uint8_t v_eepromHighAdd;
	#endif
	
	if(var_eepromAdd < C_MaxEEPROMSize)
	{
		v_eepromLowAdd = ExtractByte0To7(var_eepromAdd);
		
		#if (C_EEPROMICType > AT24C16)
			v_eepromHighAdd = ExtractByte8To15(var_eepromAdd);
		
		#else
			v_eepromPageNum = ExtractByte8To15(var_eepromAdd);
			v_eepromID = v_eepromID | (v_eepromPageNum << 1);
		
		#endif
		
		I2C_Start();
		
		I2C_Write(v_eepromID);
		
		#if (C_EEPROMICType > AT24C16)
			I2C_Write(v_eepromHighAdd);
		#endif
		
		I2C_Write(v_eepromLowAdd);
		I2C_Write(var_eepromData);
		
		I2C_Stop();
		
		delay_ms(10);
	}
}

/***********************************************/

uint8_t EEPROM_ReadByte(uint16_t var_eepromAdd)
{
	uint8_t v_eepromLowAdd;
	uint8_t v_eepromPageNum;
	uint8_t v_eepromData = 0x00;
	uint8_t v_eepromID = C_EEPROMIDWrite;
	
	#if (C_EEPROMICType > AT24C16)
		uint8_t v_eepromHighAdd;
	#endif
	
	if(var_eepromAdd < C_MaxEEPROMSize)
	{
		v_eepromLowAdd = ExtractByte0To7(var_eepromAdd);
		
		#if (C_EEPROMICType > AT24C16)
			v_eepromHighAdd = ExtractByte8To15(var_eepromAdd);
		
		#else
			v_eepromPageNum = ExtractByte8To15(var_eepromAdd);
			v_eepromID = v_eepromID | (v_eepromPageNum << 1);
		
		#endif
		
		I2C_Start();
		
		I2C_Write(v_eepromID);
		
		#if (C_EEPROMICType > AT24C16)
			I2C_Write(v_eepromHighAdd);
		#endif
		
		I2C_Write(v_eepromLowAdd);
		
		I2C_Start();
		I2C_Write(v_eepromID | 0x01);
		v_eepromData = I2C_Read(0);
		I2C_Stop();
		delay_us(10);
		
	}
	return v_eepromData;
	
}

/******************************************/


#if (Enable_EEPROM_WriteNBytes == 1)
void EEPROM_WriteNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes)
{
	while(var_noOfBytes != 0)
	{
		EEPROM_WriteByte(var_eepromAdd,*ptr_ramAdd);
		var_eepromAdd++;
		ptr_ramAdd++;
		var_noOfBytes++;
	}
}

#endif

/******************************************/

#if (Enable_EEPROM_ReadNBytes == 1)
void EEPROM_ReadNBytes(uint16_t var_eepromAdd, uint8_t *ptr_ramAdd, uint16_t var_noOfBytes)
{
	while(var_noOfBytes != 0)
	{
		*ptr_ramAdd = EEPROM_ReadByte(var_eepromAdd);
		var_eepromAdd++;
		ptr_ramAdd++;
		var_noOfBytes++;
	}
}

#endif

/*******************************************/

#if (Enable_EEPROM_WriteString == 1)
void EEPROM_WriteString(uint16_t var_eepromAdd, char *ptr_strptr)
{
	do
	{
		EEPROM_WriteByte(var_eepromAdd, *ptr_strptr);
		ptr_strptr++;
		var_eepromAdd++;
	}while(*(ptr_strptr - 1) != 0);
}
#endif

/*******************************************/

#if (Enable_EEPROM_ReadString == 1)
void EEPROM_ReadString(uint16_t var_eepromAdd, char *ptr_strptr)
{
	char v_eepromData;
	do
	{
		v_eepromData = EEPROM_ReadByte(var_eepromAdd);
		*ptr_strptr = v_eepromData;
		ptr_strptr++;
		var_eepromAdd++;
	}while(v_eepromData != 0);
}
#endif

/*******************************************/

#if (Enable_EEPROM_Erase == 1)
void EEPROM_Erase(void)
{
	uint16_t v_eepromAdd;
	
	for(v_eepromAdd=0;v_eepromAdd<C_MaxEEPROMSize;v_eepromAdd++)
	{
		EEPROM_WriteByte(v_eepromAdd,0xFFu);
	}
}
#endif
