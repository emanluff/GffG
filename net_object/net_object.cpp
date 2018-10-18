#include "net_object.h"

net_object(int socket_nr, int net_socket_nr, std::string &name, int32_t obj_id):
        nr_socket(socket_nr), nr_network_socket(net_socket_nr), name(name), object_id(obj_id)
        {
        sockaddr_in own_addr;
        own_addr.sin_family= AF_INET;
        own_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        own_addr.sin_port=htons(socket_nr);
        d_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if(d_socket<0) std::cout<<"ERROR";
        else
        {
           if(bind(d_socket, (sockaddr*) &own_addr,  sizeof(own_addr))!=0)
                std::cout<<"ERROR2";
            else
            {
            cloud_addr.sin_family= AF_INET;
            cloud_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
            cloud_addr.sin_port=htons(net_socket_nr);
            }
        }    
        }; 


int net_object::_send_packet(user_packet u_packet )
{
   packet to_send_packet;
   to_send_packet.u_packet = u_packet;
   to_send_packet.port=1;
   to_send_packet.sender_id=object_id;
   int sent=sendto(d_socket, (void*)&to_send_packet, sizeof(to_send_packet),0, (sockaddr*) &cloud_addr, sizeof(cloud_addr));
    if(sent == sizeof(to_send_packet))
        return sent;
    else
        return -1;
};

int net_object::_recv_packet(user_packet * u_packet)
{
    packet r_packet;
     int recv_c= recvfrom(d_socket, (void*) &r_packet, sizeof(r_packet),0, NULL, NULL);
        if(recv_c!=-1)
        {
        *u_packet =r_packet.u_packet;
        std::cerr<<"received packet\n";
        return r_packet.port;
        
        }
        else
            {
                std::cerr<<"error recv";
                return recv_c;
            }
}