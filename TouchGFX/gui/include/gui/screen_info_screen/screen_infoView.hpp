#ifndef SCREEN_INFOVIEW_HPP
#define SCREEN_INFOVIEW_HPP

#include <gui_generated/screen_info_screen/screen_infoViewBase.hpp>
#include <gui/screen_info_screen/screen_infoPresenter.hpp>

class screen_infoView : public screen_infoViewBase
{
public:
    screen_infoView();
    virtual ~screen_infoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void SetDeviceSerialNum(char* str);
    void SetDeviceModelName(char* str);
    void SetDeviceAdminName(char* str);
    void SetDeviceGroup(char* str);
protected:
};

#endif // SCREEN_INFOVIEW_HPP
