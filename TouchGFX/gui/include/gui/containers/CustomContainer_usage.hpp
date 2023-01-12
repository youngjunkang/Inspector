#ifndef CUSTOMCONTAINER_USAGE_HPP
#define CUSTOMCONTAINER_USAGE_HPP

#include <gui_generated/containers/CustomContainer_usageBase.hpp>

class CustomContainer_usage : public CustomContainer_usageBase
{
public:
    CustomContainer_usage();
    virtual ~CustomContainer_usage() {}

    virtual void initialize();

    void SetValue(uint8_t val);
protected:
};

#endif // CUSTOMCONTAINER_USAGE_HPP
