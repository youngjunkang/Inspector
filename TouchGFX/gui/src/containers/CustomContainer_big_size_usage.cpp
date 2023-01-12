#include <gui/containers/CustomContainer_big_size_usage.hpp>

CustomContainer_big_size_usage::CustomContainer_big_size_usage()
{

}

void CustomContainer_big_size_usage::initialize()
{
    CustomContainer_big_size_usageBase::initialize();
}

void CustomContainer_big_size_usage::SetValue(uint8_t val)
{
	Unicode::snprintf(textArea_valueBuffer, TEXTAREA_VALUE_SIZE, "%d",val);
	circleProgress_value.setValue(val);

	textArea_value.invalidate();
	circleProgress_value.invalidate();
}
