#include <gui/screen_storage_screen/screen_storageView.hpp>
#include <gui/screen_storage_screen/screen_storagePresenter.hpp>

screen_storagePresenter::screen_storagePresenter(screen_storageView& v)
    : view(v)
{

}

void screen_storagePresenter::activate()
{

}

void screen_storagePresenter::deactivate()
{

}

void screen_storagePresenter::Storage_SetListMax(int count)
{
	view.SetListMax(count);
}

void screen_storagePresenter::Storage_SetListInfo(int index,char *name, int val)
{
	view.SetListInfo(index,name,val);
}
