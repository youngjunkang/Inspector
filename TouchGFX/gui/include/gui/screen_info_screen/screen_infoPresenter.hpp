#ifndef SCREEN_INFOPRESENTER_HPP
#define SCREEN_INFOPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_infoView;

class screen_infoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_infoPresenter(screen_infoView& v);

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

    virtual ~screen_infoPresenter() {};

    virtual void info_SetDeviceSerialNum(char* str);
    virtual void info_SetDeviceModelName(char* str);
    virtual void info_SetDeviceAdminName(char* str);
    virtual void info_SetDeviceGroup(char* str);

private:
    screen_infoPresenter();

    screen_infoView& view;
};

#endif // SCREEN_INFOPRESENTER_HPP
