#include <gui/containers/CustomContainer_usage.hpp>

CustomContainer_usage::CustomContainer_usage()
{

}

void CustomContainer_usage::initialize()
{
    CustomContainer_usageBase::initialize();
}

void CustomContainer_usage::SetValue(uint8_t val)
{
	circleProgress_value.setValue(val);
	circleProgress_value.invalidate();

	Unicode::snprintf(textArea_valueBuffer, TEXTAREA_VALUE_SIZE, "%d",val);
	textArea_value.invalidate();
}
