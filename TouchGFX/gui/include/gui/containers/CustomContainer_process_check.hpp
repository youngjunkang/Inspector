#ifndef CUSTOMCONTAINER_PROCESS_CHECK_HPP
#define CUSTOMCONTAINER_PROCESS_CHECK_HPP

#include <gui_generated/containers/CustomContainer_process_checkBase.hpp>

class CustomContainer_process_check : public CustomContainer_process_checkBase
{
public:
    CustomContainer_process_check();
    virtual ~CustomContainer_process_check() {}

    virtual void initialize();

    void SetName(char *str);
    void SetValue(uint8_t val);
protected:
};

#endif // CUSTOMCONTAINER_PROCESS_CHECK_HPP
