#ifndef SCREEN_UTIL_RATEPRESENTER_HPP
#define SCREEN_UTIL_RATEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_util_rateView;

class screen_util_ratePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_util_ratePresenter(screen_util_rateView& v);

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

    virtual ~screen_util_ratePresenter() {};

    virtual void UtilRate_SetCpuUsage(int val);
    virtual void UtilRate_SetMemoryUsage(int val);
    virtual void UtilRate_SetDiskUsage(int val);
    virtual void UtilRate_SetTotalCpuCore(int val);
    virtual void UtilRate_SetTotalMemory(char* str);
private:
    screen_util_ratePresenter();

    screen_util_rateView& view;
};

#endif // SCREEN_UTIL_RATEPRESENTER_HPP
