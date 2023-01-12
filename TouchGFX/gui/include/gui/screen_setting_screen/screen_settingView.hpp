#ifndef SCREEN_SETTINGVIEW_HPP
#define SCREEN_SETTINGVIEW_HPP

#include <gui_generated/screen_setting_screen/screen_settingViewBase.hpp>
#include <gui/screen_setting_screen/screen_settingPresenter.hpp>

class screen_settingView : public screen_settingViewBase
{
public:
    screen_settingView();
    virtual ~screen_settingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void Set_Buzzer_Use_function();
    virtual void Set_Lcd_On_Time_function();
    virtual void SysParamSave_function();

    void SetBuzzerUse(uint8_t value);
    void SetLcdOnTime(uint8_t value);
protected:
};

#endif // SCREEN_SETTINGVIEW_HPP
