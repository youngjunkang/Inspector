#include <gui/screen_storage_screen/screen_storageView.hpp>

screen_storageView::screen_storageView()
{

}

void screen_storageView::setupScreen()
{
    screen_storageViewBase::setupScreen();

    /*
    SetListMax(3);

    SetListInfo(0,"A :",10);
    SetListInfo(1,"B :",50);
    SetListInfo(2,"C :",90);
    */
}

void screen_storageView::tearDownScreen()
{
    screen_storageViewBase::tearDownScreen();
}

void screen_storageView::SetListMax(uint8_t count)
{
	scrollList.setNumberOfItems(count);
	scrollList.invalidate();
}

void screen_storageView::SetListInfo(uint8_t index,char *name,uint8_t val)
{
	scrollListListItems[index].SetDriveName(name);
	scrollListListItems[index].SetUsedRate(val);
}
