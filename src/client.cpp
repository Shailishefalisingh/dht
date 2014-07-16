
#include <iostream>
#include <stdlib.h>
#include <string>

#include "Socket.hpp"


int main(void) {

    Socket client;

    std::cout << client.connect("localhost", "1234") << std::endl;
    
    int bytes = 1;
    std::string data;
    while (bytes > 0) {
        std::getline(std::cin, data);
        if (data == "quit") {
            printf("quitting...");
            break;
        }
        bytes = client.send(data.c_str(), data.length());
    }

    if (bytes == 0) {
        printf("The remote host has disconnected.\n");
    }

    client.close();
}
