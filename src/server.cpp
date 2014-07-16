
#include <iostream>
#include <stdlib.h>

#include "Socket.hpp"


int main(void) {

    Socket server;

    std::cout << server.bind("1234") << std::endl;

    std::cout << server.accept() << std::endl;

    char * ret = (char*) malloc(10);
    std::cout << server.recv(ret, 10) << std::endl;

    printf("%s\n", ret);

    free(ret);

    server.close();
}
