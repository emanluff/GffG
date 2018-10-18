#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include "packet.h"
class net_object
{
public:
    net_object(int, int , std::string&, int32_t);
       
protected:
    int d_socket;
    int d_network_socket;
    sockaddr_in cloud_addr;
    int nr_socket;
    int nr_network_socket;
    std::string name;
    std::vector<std::string> eth_card;
    int32_t object_id;
    int _send_packet(user_packet);
    int _recv_packet(user_packet*);
};