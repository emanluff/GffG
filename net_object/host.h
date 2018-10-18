#include "net_object.h"
#include "packet.h"
class Host : public net_object
{
public:
    Host(std::string &, int , int , int32_t );
    Host();
    int send_test();
    int recv_test();
private:
    
} ;