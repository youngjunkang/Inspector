#include <gui/screen_network_screen/screen_networkView.hpp>

screen_networkView::screen_networkView()
{

}

void screen_networkView::setupScreen()
{
    screen_networkViewBase::setupScreen();
    /*
    SetListMax(2);

    SetListData(0,"SDT 7#","192.168.0.1");
    SetListData(1,"SDT 10#","192.168.0.2");
    */
}

void screen_networkView::tearDownScreen()
{
    screen_networkViewBase::tearDownScreen();
}

void screen_networkView::SetListMax(uint8_t count)
{
	scrollList.setNumberOfItems(count);
	scrollList.invalidate();
}

void screen_networkView::SetListData(uint8_t index,char *name,char *ip)
{
	scrollListListItems[index].SetNetworkName(name);
	scrollListListItems[index].SetIpAddress(ip);
}
