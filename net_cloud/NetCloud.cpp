#include "NetCloud.h"

NetCloud::NetCloud()
{
    
        nodes_addr.sin_family= AF_INET;
        nodes_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
  
        
        sockaddr_in own_addr;
        own_addr.sin_family= AF_INET;
        own_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        own_addr.sin_port=htons(OWNPORT);
        d_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if(d_socket<0)
            std::cerr<<"ERROR";
        else
        {
            if(bind(d_socket, (sockaddr*) &own_addr,  sizeof(own_addr))!=0)
                std::cerr<<"ERROR2";
        
        link t_link;
        t_link.good=true;
        t_link.port1=1;
        t_link.port2=1;
        t_link.src_id=1;
        t_link.dest_port=30002;
        links.push_back(t_link);
        }
      std::cerr<<"finish netcloud init";  
        
};




 NetCloud::NetCloud(std::string& file_name)
{
    std::ifstream i_file(file_name.c_str());
    link t_link;
        t_link.good=true;
        std::string s_temp;
    if(i_file.is_open())
    {
        std::getline( i_file,s_temp);
        int own_port;
        i_file>>own_port;
        std::getline( i_file,s_temp);
        sockaddr_in own_addr;
        own_addr.sin_family= AF_INET;
        own_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        own_addr.sin_port=htons(own_port);
        
        d_socket = socket(AF_INET, SOCK_DGRAM, 0);
        
        if(d_socket<0)
            std::cerr<<"ERROR";
        else
        {
            if(bind(d_socket, (sockaddr*) &own_addr,  sizeof(own_addr))!=0)
                std::cerr<<"ERROR2";
        }
        
        
        nodes_addr.sin_family= AF_INET;
        nodes_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    while(i_file.good())
    {
        i_file>>t_link.port1>>t_link.port2>>t_link.src_id>>t_link.dest_port;
        
        links.push_back(t_link);
        std::getline( i_file,s_temp);
    }
    }
    i_file.close();
};

int NetCloud::run()
{
    
    packet r_packet;
    
    while(1)
    {
     
        int recv_c = recvfrom(d_socket, (void*) &r_packet, sizeof(r_packet),0,NULL,NULL );
        std::cerr<<std::endl<<"recv"<<std::endl;
        if(recv_c!=-1)
        {
            for(std::vector<link>::iterator it=links.begin(); it<links.end(); it++)
            {
                std::cerr<<"loop"<<std::endl;
                if(it->src_id==r_packet.sender_id && it->port1==r_packet.port)
                {
                    std::cerr<<"found link"<<std::endl;
                    r_packet.port=it->port2;
                    
                    nodes_addr.sin_port=htons(it->dest_port);
                    
                    int sent=sendto(d_socket, (void*) &r_packet, sizeof(packet), 0, (sockaddr*) &nodes_addr, sizeof(sockaddr));
                    
                    if(sent<0)
                        std::cerr<<"error";
                    else    
                        std::cerr<<"send\n";
                }
                else
                    std::cerr<<"link unfound"<<std::endl;
            }
            
            
            
        }
        else
        {
            std::cerr<<"recv -1, hyperloop..."<<std::endl;
            std::cerr<<strerror(errno);
            return -1;
        }
       
        }
        
    }
