#define TSC2007_C_
	#include "tsc2007.h"
#undef TSC2007_C_

#define TSC2007_I2CADDR_DEFAULT (0x48<<1)

typedef enum {
  MEASURE_TEMP0 = 0,
  MEASURE_AUX = 2,
  MEASURE_TEMP1 = 4,
  ACTIVATE_X = 8,
  ACTIVATE_Y = 9,
  ACTIVATE_YPLUS_X = 10,
  SETUP_COMMAND = 11,
  MEASURE_X = 12,
  MEASURE_Y = 13,
  MEASURE_Z1 = 14,
  MEASURE_Z2 = 15
} adafruit_tsc2007_function;

typedef enum {
  POWERDOWN_IRQON = 0,
  ADON_IRQOFF = 1,
  ADOFF_IRQON = 2,
} adafruit_tsc2007_power;

typedef enum {
  ADC_12BIT = 0,
  ADC_8BIT = 1,
} adafruit_tsc2007_resolution;

static I2C_HandleTypeDef hi2c1;

static void Calibraion(void);
static void writeCmd(uint8_t data);
static uint16_t readCmd(adafruit_tsc2007_function func, adafruit_tsc2007_power pwr,adafruit_tsc2007_resolution res);

static void MX_I2C1_Init(void);
static uint8_t I2C1_ReadData(uint8_t Addr, uint8_t Reg);
static void I2C1_WriteData(uint8_t Addr, uint8_t Value);
static void I2C1_ReadBuffer(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length);

static float kx[3],ky[3];

void TSC2007_Init(void)
{
	 GPIO_InitTypeDef   GPIO_InitStructure;

	/* Enable GPIOA clock */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* Configure PA0 pin as input floating */
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_11;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	MX_I2C1_Init();

	writeCmd(0xB1);
	Calibraion();
}

uint8_t TSC2007_DetectTouch(void)
{
	return !HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11);
}

void TSC2007_Read(uint16_t *x, uint16_t *y)
{
	uint16_t _x, _y;

	_x = readCmd(MEASURE_X, ADON_IRQOFF, ADC_12BIT);
	_y = readCmd(MEASURE_Y, ADON_IRQOFF, ADC_12BIT);
	readCmd(MEASURE_TEMP0, POWERDOWN_IRQON, ADC_12BIT);

	//*x = _x;
	//*y = _y;
	*x = kx[0]*_x + kx[1]*_y + kx[2];
	*y = ky[0]*_x + ky[1]*_y + ky[2];
}

static void writeCmd(uint8_t data)
{
	I2C1_WriteData(TSC2007_I2CADDR_DEFAULT,data);
}

static uint16_t readCmd(adafruit_tsc2007_function func, adafruit_tsc2007_power pwr,adafruit_tsc2007_resolution res)
{
	uint8_t cmd = (uint8_t)func << 4;
	cmd |= (uint8_t)pwr << 2;
	cmd |= (uint8_t)res << 1;

	uint8_t reply[2];

	I2C1_ReadBuffer(TSC2007_I2CADDR_DEFAULT,cmd,reply,2);

	return ((uint16_t)reply[0] << 4) | (reply[1] >> 4); // 12 bits
}

static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_DISABLE) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void I2C1_WriteData(uint8_t Addr, uint8_t Value)
{
	HAL_I2C_Master_Transmit(&hi2c1,Addr,&Value,1,100);
}

static uint8_t I2C1_ReadData(uint8_t Addr, uint8_t Reg)
{
	uint8_t value = 0;

	HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);

	return value;
}


static void I2C1_ReadBuffer(uint8_t Addr, uint8_t Reg, uint8_t *pBuffer, uint16_t Length)
{
	HAL_I2C_Mem_Read(&hi2c1, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, pBuffer, Length, 100);
}

static void Calibraion(void)
{
	float x0,x1,x2,y0,y1,y2;
	float xb0,xb1,xb2,yb0,yb1,yb2;
	float k;

	x0 = 20;//20;
	y0 = 300;//20;
	x1 = 20;//20;
	y1 = 20;//220;
	x2 = 220;//300;
	y2 = 20;//220;

	xb0 = 3440;//3423;
	yb0 = 420;//378;
	xb1 = 3440;//551;
	yb1 = 3480;//421;
	xb2 = 520;//541;
	yb2 = 3480;//3450;

	k = (xb0 - xb2)*(yb1 - yb2) - (xb1 - xb2)*(yb0 - yb2);

	kx[0] = ((x0 - x2)*(yb1 - yb2) - (x1 - x2)*(yb0 - yb2))/k;
	kx[1] = ((x1 - x2)*(xb0 - xb2) - (x0 - x2)*(xb1 - xb2))/k;
	kx[2] = ( yb0*(xb2*x1 - xb1*x2) + yb1*(xb0*x2 - xb2*x0) + yb2*(xb1*x0 - xb0*x1) )/k;

	ky[0] = ((y0 - y2)*(yb1 - yb2) - (y1 - y2)*(yb0 - yb2))/k;
	ky[1] = ((y1 - y2)*(xb0 - xb2) - (y0 - y2)*(xb1 - xb2))/k;
	ky[2] = ( yb0*(xb2*y1 - xb1*y2) + yb1*(xb0*y2 - xb2*y0) + yb2*(xb1*y0 - xb0*y1) )/k;
}
