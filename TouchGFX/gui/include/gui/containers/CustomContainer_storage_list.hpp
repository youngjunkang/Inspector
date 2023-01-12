#ifndef CUSTOMCONTAINER_STORAGE_LIST_HPP
#define CUSTOMCONTAINER_STORAGE_LIST_HPP

#include <gui_generated/containers/CustomContainer_storage_listBase.hpp>

class CustomContainer_storage_list : public CustomContainer_storage_listBase
{
public:
    CustomContainer_storage_list();
    virtual ~CustomContainer_storage_list() {}

    virtual void initialize();

    void SetDriveName(char *str);
    void SetUsedRate(int num);
protected:
};

#endif // CUSTOMCONTAINER_STORAGE_LIST_HPP
