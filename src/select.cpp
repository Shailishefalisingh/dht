
#include <sys/select.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <list>
#include <thread>
#include <mutex>

#include <sys/time.h>
#include <sys/types.h>

#include "ClientSocket.hpp"
#include "ServerSocket.hpp"

int main(void) {
    // start handling incoming connections 
    ServerSocket s;
    s.bind("1234");
    while (true) {
        ClientSocket sock = s.accept();
        if (!sock.valid()) {
            perror("accept()");
            continue;
        }
        // TODO start thread to handle sock
    }

    return 0;
}
