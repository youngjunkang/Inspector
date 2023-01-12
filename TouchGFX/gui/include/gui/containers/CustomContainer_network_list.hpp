#ifndef CUSTOMCONTAINER_NETWORK_LIST_HPP
#define CUSTOMCONTAINER_NETWORK_LIST_HPP

#include <gui_generated/containers/CustomContainer_network_listBase.hpp>

class CustomContainer_network_list : public CustomContainer_network_listBase
{
public:
    CustomContainer_network_list();
    virtual ~CustomContainer_network_list() {}

    virtual void initialize();

    void SetNetworkName(char *str);
    void SetIpAddress(char *str);
protected:
};

#endif // CUSTOMCONTAINER_NETWORK_LIST_HPP
