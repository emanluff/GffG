#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include "../net_object/packet.h"
#include <errno.h>
#define OWNPORT 30000
#define LISTEN_BACKLOG 50



struct link
{
    //is link working?
  bool good;
  //eth card of firts node
  int port1;
  //eth card of second node
  int port2;
  //identity number of sender
  int32_t src_id;
  //"real" number of socket where packet should be sent
  int dest_port;
};

class NetCloud
{
public:
    NetCloud();
    NetCloud(std::string&);
    int run();
    
private:
    std::vector<link> links;
    sockaddr_in nodes_addr;
    int d_socket;
    
};