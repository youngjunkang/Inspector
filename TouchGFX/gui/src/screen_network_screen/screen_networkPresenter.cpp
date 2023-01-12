#include <gui/screen_network_screen/screen_networkView.hpp>
#include <gui/screen_network_screen/screen_networkPresenter.hpp>

screen_networkPresenter::screen_networkPresenter(screen_networkView& v)
    : view(v)
{

}

void screen_networkPresenter::activate()
{

}

void screen_networkPresenter::deactivate()
{

}

void screen_networkPresenter::Network_SetListMax(int count)
{
	view.SetListMax(count);
}

void screen_networkPresenter::Network_SetListData(int index,char *name,char *ip)
{
	view.SetListData(index,name,ip);
}
