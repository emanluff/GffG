#include <stdio.h>
#include <stdlib.h>
#include "host.h"

int main(int argc, char **argv)
{
	if(argc<6)
        return -1;
    
    std::string name = argv[1];
    int nr_port = atoi(argv[2]);
    int net_port = atoi(argv[3]);
    int object_id = atoi(argv[4]);
    int mode = atoi(argv[5]);
    Host h(name, nr_port,net_port, object_id);
    if(mode==0)
        h.send_test();
    else
        h.recv_test();
    printf("hello end of world\n");
	return 0;
}
