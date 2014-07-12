
#include <iostream>
#include <stdlib.h>

#include "Socket.hpp"


int main(void) {

    Socket client;

    std::cout << client.connect("localhost", "1234") << std::endl;
    std::cout << client.send("WORK", 4) << std::endl;

    client.close();
}
