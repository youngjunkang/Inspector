#ifndef SCREEN_PROCESSPRESENTER_HPP
#define SCREEN_PROCESSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_processView;

class screen_processPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_processPresenter(screen_processView& v);

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

    virtual ~screen_processPresenter() {};

    virtual void Process_SetListMax(int count);
    virtual void Process_SetListInfo(int index,char *name, int val);
    virtual void Process_SetCpuUsage(int val);
private:
    screen_processPresenter();

    screen_processView& view;
};

#endif // SCREEN_PROCESSPRESENTER_HPP
