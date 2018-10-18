#include <stdio.h>
#include "NetCloud.h"
int main(int argc, char **argv)
{
    std::string f_name="links";
    NetCloud net_cloud(f_name);
    net_cloud.run();
	printf("hello world\n");
	return 0;
}
