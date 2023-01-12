#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "timers.h"
#include "cmsis_os.h"
#include "tim.h"
#include "ili9341.h"
#include "SysParam.h"
#include "rtc.h"
#include "ads8321.h"

#define NUM_TIMERS 2

typedef enum BuzzerState_t
{
	IS_TOUCHED = 0,
	BUZZER_ON,
	IS_NOT_TOUCHED,
}BuzzerState_t;


static uint32_t TouchedCount;

static BuzzerState_t BuzzerState;

TimerHandle_t xTimers[ NUM_TIMERS ];


static void RTC_Test(void);

static uint32_t GetLcdOnTimeTick(void);
static void Check_LCD_OnOff(void);
static void BuzzerAction(void);
static uint8_t IsTouched(void);
void vTimerCallback( TimerHandle_t xTimer );

uint8_t pwrSW = 0;
uint8_t rstSW = 0;
int16_t ads8321Value;
float ads8321Volt;
void System_Task(void *argument)
{
  /* USER CODE BEGIN System_Task */
	BuzzerState = IS_TOUCHED;
	xTimers[0] = xTimerCreate( "BuzzerTim" ,10,pdTRUE,( void * )0, vTimerCallback);
	xTimers[1] = xTimerCreate( "ScrTim" ,100,pdTRUE,( void * )0, vTimerCallback);
	xTimerStart( xTimers[0], 0 );
	xTimerStart( xTimers[1], 0 );

	/* Infinite loop */
	for(;;)
	{
		/*
		HAL_GPIO_WritePin(GPIOC, POWER_SW_Pin, pwrSW);
		HAL_GPIO_WritePin(GPIOC, RESET_SW_Pin, rstSW);
		RTC_Test();
		MX_USART1_WriteBytes("test\r\n",6);
		MX_USART4_WriteBytes("test\r\n",6);
		*/
		ads8321Value = ADS8321_Read();
		ads8321Volt = ADS8321_ReadVolt();
		osDelay(10);
	}
  /* USER CODE END System_Task */
}

uint8_t timeStr[20];
uint8_t dateStr[20];
static void RTC_Test(void)
{
	RTC_CalendarShow(timeStr,dateStr);
}



static uint8_t IsTouched(void)
{
	static uint8_t prevVal = 0;
	uint8_t val = TSC2007_DetectTouch();
	uint8_t ret = 0;

	if(prevVal != val)
	{
		prevVal = val;
		ret = 1;
	}

	return ret;
}


int TimerCount = 0;
void vTimerCallback( TimerHandle_t xTimer )
{
	if(xTimer == xTimers[0])
	{
		if(SysParam.buzzerUse)
			BuzzerAction();
	}

	if(xTimer == xTimers[1])
	{
		Check_LCD_OnOff();
	}
}

static uint32_t GetLcdOnTimeTick(void)
{
	uint32_t timeTickSec;

	switch(SysParam.lcdOnTime)
	{
	case LCD_OFF_TIME_10_SEC : timeTickSec = 10; break;
	case LCD_OFF_TIME_30_SEC : timeTickSec = 30; break;
	case LCD_OFF_TIME_1_MIN  : timeTickSec = 60; break;
	case LCD_OFF_TIME_5_MIN  : timeTickSec = 300; break;
	case LCD_OFF_TIME_30_MIN : timeTickSec = 1800; break;
	case LCD_OFF_TIME_1_HOUR : timeTickSec = 3600; break;
	case LCD_OFF_TIME_ALWAYS : timeTickSec = 0xFFFFFFFF; break;
	default : timeTickSec = 10;
	}

	timeTickSec *= 10;
}
static void Check_LCD_OnOff(void)
{
	static int SecondCount = 0;

	if(TSC2007_DetectTouch())
	{
		SecondCount = 0;
		LCD_IO_WriteReg(LCD_DISPLAY_ON);
	}else
	{
		if(SecondCount == GetLcdOnTimeTick())
		{
			LCD_IO_WriteReg(LCD_DISPLAY_OFF);
		}
		else
		{
			SecondCount++;
		}
	}
}

static void BuzzerAction(void)
{
	switch(BuzzerState)
	{
	case IS_TOUCHED :
		if(TSC2007_DetectTouch())
		{
			if(TouchedCount++ > 0)
			{
				TouchedCount = 0;
				BuzzerState = BUZZER_ON;
				Buzzer_On();
			}
		}
		else TouchedCount = 0;
		break;
	case BUZZER_ON :
		if(TouchedCount++ > 4)
		{
			TouchedCount = 0;
			BuzzerState = IS_NOT_TOUCHED;
			Buzzer_Off();
		}
		break;
	case IS_NOT_TOUCHED :
		if(!TSC2007_DetectTouch())
		{
			if(TouchedCount++ > 4)
			{
				BuzzerState = IS_TOUCHED;
			}
		}
		else
			TouchedCount = 0;

		break;
	}
}
