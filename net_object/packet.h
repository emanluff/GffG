#pragma once

struct user_packet
{
    int32_t address_id;
    char msg[50];
    
};

struct packet
{
    user_packet u_packet;
    int port;
    int32_t sender_id;
};

