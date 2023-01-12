#include <gui/screen_process_screen/screen_processView.hpp>

screen_processView::screen_processView()
{

}

void screen_processView::setupScreen()
{
    screen_processViewBase::setupScreen();
    /*
    SetListMax(3);
    SetListInfo(0,"test1.exe",10);
    SetListInfo(1,"test2.exe",50);
    SetListInfo(2,"test3.exe",100);

    SetCpuUsage(80);
    */
}

void screen_processView::tearDownScreen()
{
    screen_processViewBase::tearDownScreen();
}


void screen_processView::SetListMax(uint8_t count)
{
	scrollList.setNumberOfItems(count);
	scrollList.invalidate();
}

void screen_processView::SetListInfo(uint8_t index,char *name,uint8_t val)
{
	scrollListListItems[index].SetName(name);
	scrollListListItems[index].SetValue(val);
}

void screen_processView::SetCpuUsage(uint8_t val)
{
	customContainer_big_size_usage_cpu.SetValue(val);
}
