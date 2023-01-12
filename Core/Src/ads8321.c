#define __ADS8321_C__
    #include "ads8321.h"
#undef  __ADS8321_C__

#include "spi.h"

static uint8_t ADS8321_buffer[3];

int16_t ADS8321_Read(void)
{
	uint32_t tmp;

	HAL_GPIO_WritePin(SPI1_CS1_GPIO_Port, SPI1_CS1_Pin, GPIO_PIN_RESET);
	for(volatile i=0; i<10; i++);
	SPI_Read(&hspi1,ADS8321_buffer,3);
	HAL_GPIO_WritePin(SPI1_CS1_GPIO_Port, SPI1_CS1_Pin, GPIO_PIN_SET);

	tmp = ((ADS8321_buffer[0]<<16)|(ADS8321_buffer[1]<<8)|(ADS8321_buffer[2]))>>2;

	return (int16_t)(tmp&0xFFFF);
}

float ADS8321_ReadVolt(void)
{
	float volt;

	volt = 2.5f + ((float)ADS8321_Read()/0x7FFF)*2.5f;

	return volt;
}
