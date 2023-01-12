#ifndef SCREEN_SETTINGPRESENTER_HPP
#define SCREEN_SETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_settingView;

class screen_settingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_settingPresenter(screen_settingView& v);

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

    virtual ~screen_settingPresenter() {};

    void setBuzzerUse(unsigned char value)
    {
    	model->buzzerUse = value;
    }

    void setLcdOnTime(unsigned char value)
	{
		model->lcdOnTime = value;
	}

    unsigned char getBuzzerUse()
    {
    	return model->buzzerUse;
    }

    unsigned char getLcdOnTime()
    {
    	return model->lcdOnTime;
    }
private:
    screen_settingPresenter();

    screen_settingView& view;
};

#endif // SCREEN_SETTINGPRESENTER_HPP
