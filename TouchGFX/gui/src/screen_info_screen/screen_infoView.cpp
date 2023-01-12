#include <gui/screen_info_screen/screen_infoView.hpp>

screen_infoView::screen_infoView()
{

}

void screen_infoView::setupScreen()
{
    screen_infoViewBase::setupScreen();
    /*
    SetDeviceSerialNum("SDT20221212");
    SetDeviceModelName("SDT-ECN-i5");
    SetDeviceAdminName("sgkim");
    SetDeviceGroup("SK-Ecoplant");
    */
}

void screen_infoView::tearDownScreen()
{
    screen_infoViewBase::tearDownScreen();
}

void screen_infoView::SetDeviceSerialNum(char* str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_serial_numBuffer, TEXTAREA_SERIAL_NUM_SIZE);
	textArea_serial_num.invalidate();
}

void screen_infoView::SetDeviceModelName(char* str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_model_nameBuffer, TEXTAREA_MODEL_NAME_SIZE);
	textArea_model_name.invalidate();
}

void screen_infoView::SetDeviceAdminName(char* str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_admin_nameBuffer, TEXTAREA_ADMIN_NAME_SIZE);
	textArea_admin_name.invalidate();
}

void screen_infoView::SetDeviceGroup(char* str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_groupBuffer, TEXTAREA_GROUP_SIZE);
	textArea_group.invalidate();
}

