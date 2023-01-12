#include <gui/containers/CustomContainer_process_check.hpp>

CustomContainer_process_check::CustomContainer_process_check()
{

}

void CustomContainer_process_check::initialize()
{
    CustomContainer_process_checkBase::initialize();
}

void CustomContainer_process_check::SetName(char *str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_process_nameBuffer, TEXTAREA_PROCESS_NAME_SIZE);
	textArea_process_name.invalidate();
}

void CustomContainer_process_check::SetValue(uint8_t val)
{
	Unicode::snprintf(textArea_process_usageBuffer, TEXTAREA_PROCESS_USAGE_SIZE, "%d",val);
	textArea_process_usage.invalidate();
}
