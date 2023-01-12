#ifndef SCREEN_GNBVIEW_HPP
#define SCREEN_GNBVIEW_HPP

#include <gui_generated/screen_gnb_screen/screen_gnbViewBase.hpp>
#include <gui/screen_gnb_screen/screen_gnbPresenter.hpp>

class screen_gnbView : public screen_gnbViewBase
{
public:
    screen_gnbView();
    virtual ~screen_gnbView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_GNBVIEW_HPP
