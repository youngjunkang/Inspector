#ifndef SCREEN_PROCESSVIEW_HPP
#define SCREEN_PROCESSVIEW_HPP

#include <gui_generated/screen_process_screen/screen_processViewBase.hpp>
#include <gui/screen_process_screen/screen_processPresenter.hpp>

class screen_processView : public screen_processViewBase
{
public:
    screen_processView();
    virtual ~screen_processView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void SetListMax(uint8_t count);
    void SetListInfo(uint8_t index,char *name,uint8_t val);
    void SetCpuUsage(uint8_t val);
protected:
};

#endif // SCREEN_PROCESSVIEW_HPP
