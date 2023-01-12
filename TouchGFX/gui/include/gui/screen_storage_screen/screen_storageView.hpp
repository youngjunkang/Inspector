#ifndef SCREEN_STORAGEVIEW_HPP
#define SCREEN_STORAGEVIEW_HPP

#include <gui_generated/screen_storage_screen/screen_storageViewBase.hpp>
#include <gui/screen_storage_screen/screen_storagePresenter.hpp>

class screen_storageView : public screen_storageViewBase
{
public:
    screen_storageView();
    virtual ~screen_storageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void SetListMax(uint8_t count);
    void SetListInfo(uint8_t index,char *name,uint8_t val);
protected:
};

#endif // SCREEN_STORAGEVIEW_HPP
