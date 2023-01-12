#ifndef SCREEN_STORAGEPRESENTER_HPP
#define SCREEN_STORAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_storageView;

class screen_storagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_storagePresenter(screen_storageView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~screen_storagePresenter() {};

    virtual void Storage_SetListMax(int count);
    virtual void Storage_SetListInfo(int index,char *name, int val);
private:
    screen_storagePresenter();

    screen_storageView& view;
};

#endif // SCREEN_STORAGEPRESENTER_HPP
