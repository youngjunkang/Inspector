#include <gui/containers/CustomContainer_storage_list.hpp>
#include <stdlib.h>

CustomContainer_storage_list::CustomContainer_storage_list()
{

}

void CustomContainer_storage_list::initialize()
{
    CustomContainer_storage_listBase::initialize();
}

void CustomContainer_storage_list::SetDriveName(char *str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_drive_nameBuffer, TEXTAREA_DRIVE_NAME_SIZE);
	textArea_drive_name.invalidate();
}

void CustomContainer_storage_list::SetUsedRate(int num)
{
	Unicode::snprintf(textArea_used_rateBuffer, TEXTAREA_USED_RATE_SIZE, "%d",num);
	textArea_used_rate.invalidate();

	lineProgress_used_rate.setValue(num);
	lineProgress_used_rate.invalidate();
}
