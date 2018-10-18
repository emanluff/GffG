#include "host.h"

Host::Host(std::string& name, int socket_nr, int net_socket_nr, int32_t object_id) :
        net_object( socket_nr ,net_socket_nr, name,object_id)
        {
            
        };
        
int Host::send_test()
{
    user_packet data_packet;
    data_packet.address_id=2;
    char msg[]="ala ma kota\n";
    memcpy(  &data_packet.msg, msg, strlen(msg)+1);
    return _send_packet(data_packet);
    
}

int Host::recv_test()
{
    user_packet u_packet;
    if(_recv_packet(&u_packet)==1)
    {
        std::cout<<u_packet.msg;
        return 0;
    }
    else
        return -1;
}