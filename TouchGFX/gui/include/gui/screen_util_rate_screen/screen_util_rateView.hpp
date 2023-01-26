#ifndef SCREEN_UTIL_RATEVIEW_HPP
#define SCREEN_UTIL_RATEVIEW_HPP

#include <gui_generated/screen_util_rate_screen/screen_util_rateViewBase.hpp>
#include <gui/screen_util_rate_screen/screen_util_ratePresenter.hpp>

class screen_util_rateView : public screen_util_rateViewBase
{
public:
    screen_util_rateView();
    virtual ~screen_util_rateView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void SetCpuUsage(uint8_t val);
    void SetMemoryUsage(uint8_t val);
    void SetDiskUsage(uint8_t val);
    void SetTotalCpuCore(uint8_t val);
    void SetTotalMemory(char* str);
protected:
};

#endif // SCREEN_UTIL_RATEVIEW_HPP
