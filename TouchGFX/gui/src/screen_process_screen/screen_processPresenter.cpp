#include <gui/screen_process_screen/screen_processView.hpp>
#include <gui/screen_process_screen/screen_processPresenter.hpp>

screen_processPresenter::screen_processPresenter(screen_processView& v)
    : view(v)
{

}

void screen_processPresenter::activate()
{

}

void screen_processPresenter::deactivate()
{

}

void screen_processPresenter::Process_SetListMax(int count)
{
	view.SetListMax(count);
}

void screen_processPresenter::Process_SetListInfo(int index,char *name, int val)
{
	view.SetListInfo(index,name,val);
}

void screen_processPresenter::Process_SetCpuUsage(int val)
{
	view.SetCpuUsage(val);
}
