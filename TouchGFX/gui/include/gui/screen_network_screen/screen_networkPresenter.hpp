#ifndef SCREEN_NETWORKPRESENTER_HPP
#define SCREEN_NETWORKPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_networkView;

class screen_networkPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_networkPresenter(screen_networkView& v);

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

    virtual ~screen_networkPresenter() {};

    virtual void Network_SetListMax(int count);
    virtual void Network_SetListData(int index,char *name,char *ip);
private:
    screen_networkPresenter();

    screen_networkView& view;
};

#endif // SCREEN_NETWORKPRESENTER_HPP
