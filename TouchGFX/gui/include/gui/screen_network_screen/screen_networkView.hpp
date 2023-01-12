#ifndef SCREEN_NETWORKVIEW_HPP
#define SCREEN_NETWORKVIEW_HPP

#include <gui_generated/screen_network_screen/screen_networkViewBase.hpp>
#include <gui/screen_network_screen/screen_networkPresenter.hpp>

class screen_networkView : public screen_networkViewBase
{
public:
    screen_networkView();
    virtual ~screen_networkView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void SetListMax(uint8_t count);
    void SetListData(uint8_t index,char *name,char *ip);
protected:
};

#endif // SCREEN_NETWORKVIEW_HPP
