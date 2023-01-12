#ifndef CUSTOMCONTAINER_BIG_SIZE_USAGE_HPP
#define CUSTOMCONTAINER_BIG_SIZE_USAGE_HPP

#include <gui_generated/containers/CustomContainer_big_size_usageBase.hpp>

class CustomContainer_big_size_usage : public CustomContainer_big_size_usageBase
{
public:
    CustomContainer_big_size_usage();
    virtual ~CustomContainer_big_size_usage() {}

    virtual void initialize();

    void SetValue(uint8_t val);
protected:
};

#endif // CUSTOMCONTAINER_BIG_SIZE_USAGE_HPP
