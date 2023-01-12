#include <gui/screen_setting_screen/screen_settingView.hpp>
#include <string.h>
#include "cmsis_os2.h"
#include "AppData.h"

extern osMessageQueueId_t GuiTaskMBoxHandle;

screen_settingView::screen_settingView()
{

}

void screen_settingView::setupScreen()
{
    screen_settingViewBase::setupScreen();
	unsigned char buzzerUse = presenter->getBuzzerUse();
	unsigned char lcdOffTime = presenter->getLcdOnTime();

	SetBuzzerUse(buzzerUse);
	SetLcdOnTime(lcdOffTime);
}

void screen_settingView::tearDownScreen()
{
    screen_settingViewBase::tearDownScreen();
}

void screen_settingView::Set_Buzzer_Use_function()
{
	unsigned char buzzerUse = presenter->getBuzzerUse();

	buzzerUse ^= 1;
	SetBuzzerUse(buzzerUse);
	presenter->setBuzzerUse(buzzerUse);
}

void screen_settingView::Set_Lcd_On_Time_function()
{
	unsigned char lcdOffTime = presenter->getLcdOnTime();
	lcdOffTime++;
	lcdOffTime %= 7;
	SetLcdOnTime(lcdOffTime);

	presenter->setLcdOnTime(lcdOffTime);
}

void screen_settingView::SysParamSave_function()
{
	GuiMessage_t msg;
	msg.eventType = GUI_EVENT_SAVE_PARAM;
	msg.data = 0;
	osMessageQueuePut(GuiTaskMBoxHandle,&msg,0,0);
}

void screen_settingView::SetBuzzerUse(uint8_t value)
{
	char str[10];

	if(value) strcpy(str,"ON");
	else	  strcpy(str,"OFF");

	Unicode::fromUTF8((const uint8_t*)str, flexButton_buzzer_useBuffer, FLEXBUTTON_BUZZER_USE_SIZE);
	flexButton_buzzer_use.invalidate();
}

void screen_settingView::SetLcdOnTime(uint8_t value)
{
	char str[10];

	switch(value)
	{
	case 0 : strcpy(str,"10sec"); break;
	case 1 : strcpy(str,"30sec"); break;
	case 2 : strcpy(str,"1min"); break;
	case 3 : strcpy(str,"5min"); break;
	case 4 : strcpy(str,"30min"); break;
	case 5 : strcpy(str,"1hour"); break;
	case 6 : strcpy(str,"Always"); break;
	}

	Unicode::fromUTF8((const uint8_t*)str, flexButton_lcd_on_timeBuffer, FLEXBUTTON_LCD_ON_TIME_SIZE);
	flexButton_lcd_on_time.invalidate();
}
