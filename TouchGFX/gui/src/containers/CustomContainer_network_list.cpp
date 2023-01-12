#include <gui/containers/CustomContainer_network_list.hpp>

CustomContainer_network_list::CustomContainer_network_list()
{

}

void CustomContainer_network_list::initialize()
{
    CustomContainer_network_listBase::initialize();
}

void CustomContainer_network_list::SetNetworkName(char *str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_net_nameBuffer, TEXTAREA_NET_NAME_SIZE);
	textArea_net_name.invalidate();
}

void CustomContainer_network_list::SetIpAddress(char *str)
{
	Unicode::fromUTF8((const uint8_t*)str, textArea_net_ipBuffer, TEXTAREA_NET_IP_SIZE);
	textArea_net_ip.invalidate();
}
