#include <gui/screen_util_rate_screen/screen_util_rateView.hpp>
#include <stdio.h>

screen_util_rateView::screen_util_rateView()
{

}

void screen_util_rateView::setupScreen()
{
    screen_util_rateViewBase::setupScreen();

    /*
    SetCpuUsage(10);
    SetMemoryUsage(20);
    SetDiskUsage(30);
    SetTotalCpuCore(12);
    SetTotalMemory(16.5f);
    */
}

void screen_util_rateView::tearDownScreen()
{
    screen_util_rateViewBase::tearDownScreen();
}

void screen_util_rateView::SetCpuUsage(uint8_t val)
{
	customContainer_usage_cpu.SetValue(val);
}

void screen_util_rateView::SetMemoryUsage(uint8_t val)
{
	customContainer_usage_memory.SetValue(val);
}

void screen_util_rateView::SetDiskUsage(uint8_t val)
{
	customContainer_usage_disk.SetValue(val);
}

void screen_util_rateView::SetTotalCpuCore(uint8_t val)
{
	Unicode::snprintf(textArea_Core_CountBuffer, TEXTAREA_CORE_COUNT_SIZE, "%d",val);
	textArea_Core_Count.invalidate();
}

void screen_util_rateView::SetTotalMemory(char* str)
{
	char tmp[20];

	sprintf(tmp,"%s",str);
	Unicode::fromUTF8((const uint8_t*)tmp, textArea_total_memoryBuffer, TEXTAREA_TOTAL_MEMORY_SIZE);
	//Unicode::snprintfFloat(textArea_total_memoryBuffer, TEXTAREA_TOTAL_MEMORY_SIZE, "%3.1f", val);
	textArea_total_memory.invalidate();
}
