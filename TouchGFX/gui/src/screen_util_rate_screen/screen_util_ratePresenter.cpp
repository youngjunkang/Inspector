#include <gui/screen_util_rate_screen/screen_util_rateView.hpp>
#include <gui/screen_util_rate_screen/screen_util_ratePresenter.hpp>

screen_util_ratePresenter::screen_util_ratePresenter(screen_util_rateView& v)
    : view(v)
{

}

void screen_util_ratePresenter::activate()
{

}

void screen_util_ratePresenter::deactivate()
{

}

void screen_util_ratePresenter::UtilRate_SetCpuUsage(int val)
{
	view.SetCpuUsage(val);
}

void screen_util_ratePresenter::UtilRate_SetMemoryUsage(int val)
{
	view.SetMemoryUsage(val);
}

void screen_util_ratePresenter::UtilRate_SetDiskUsage(int val)
{
	view.SetDiskUsage(val);
}

void screen_util_ratePresenter::UtilRate_SetTotalCpuCore(int val)
{
	view.SetTotalCpuCore(val);
}

void screen_util_ratePresenter::UtilRate_SetTotalMemory(float val)
{
	view.SetTotalMemory(val);
}
