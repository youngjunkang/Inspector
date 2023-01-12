#include <gui/screen_info_screen/screen_infoView.hpp>
#include <gui/screen_info_screen/screen_infoPresenter.hpp>

screen_infoPresenter::screen_infoPresenter(screen_infoView& v)
    : view(v)
{

}

void screen_infoPresenter::activate()
{
	//info_SetDeviceSerialNum("123456");
}

void screen_infoPresenter::deactivate()
{

}

void screen_infoPresenter::info_SetDeviceSerialNum(char* str)
{
	view.SetDeviceSerialNum(str);
}

void screen_infoPresenter::info_SetDeviceModelName(char* str)
{
	view.SetDeviceModelName(str);
}

void screen_infoPresenter::info_SetDeviceAdminName(char* str)
{
	view.SetDeviceAdminName(str);
}

void screen_infoPresenter::info_SetDeviceGroup(char* str)
{
	view.SetDeviceGroup(str);
}
