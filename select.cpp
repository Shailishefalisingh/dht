
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

#include "Socket.hpp"

    
std::list<int> readers;
std::mutex readers_mutex;

void accept_connections() {
    
    Socket s;
    s.bind("1234");
    int sockfd;
    while (true) {
        sockfd = s.accept();
        if (sockfd < 0) {
            perror("accept()");
            continue;
        }
        readers.push_back(sockfd);
        printf("accepted connection sockfd=%d\n", sockfd);
    }
}

int main(void) {
    
    fd_set read_fds;
    struct timeval tv;
    int fdmax, retval;

    // start accepting connections
    std::thread acceptor(accept_connections);

    while (true) {
        // start setting stuff up for the select() call
        FD_ZERO(&read_fds);
        fdmax = 0;

        readers_mutex.lock();
        for (std::list<int>::iterator it = readers.begin();
                it != readers.end(); ++it) {
            if (*it > fdmax)
                fdmax = *it;
            // printf("Setting socket %d\n", *it);
            FD_SET(*it, &read_fds);
        }
        readers_mutex.unlock();

        // wait up to 5 seconds
        tv.tv_sec = 0;
        tv.tv_usec = 10000;
        
        retval = select(fdmax + 1, &read_fds, NULL, NULL, &tv);
        
        if (retval < 0) {
            perror("select()");
        } else if (retval > 0) {
            // printf("Data is available now!\n");
            readers_mutex.lock();
            for (std::list<int>::iterator i = readers.begin();
                    i != readers.end(); ++i) {
                if (FD_ISSET(*i, &read_fds)) {
                    char * buf = (char*)malloc(20);
                    int b = recv(*i, buf, 20, 0);
                    printf("Bytes=%d\n", b);
                    printf("Data recieved: %s\n", buf);
                    free(buf);
                    if (b == 0 || *i < 0) {
                        printf("Disconnection on sockfd=%d\n", *i);
                        close(*i);
                        readers.erase(i++);
                    }
                }
            }
            readers_mutex.unlock();
        } else {
            // printf("No data recieved.\n");
        }
    }

    acceptor.join();

    return 0;
}
