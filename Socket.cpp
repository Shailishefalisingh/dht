
#include "Socket.hpp"
#include <iostream>

#define BACKLOG 10

Socket::Socket() {
    
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

bool Socket::connect(const char * addr, const char * port) {
   
    int err = 0;

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo(addr, port, &hints, &res);

    std::cout << this->sockfd << std::endl;

    err = ::connect(this->sockfd, res->ai_addr, res->ai_addrlen);

    if (err < 0) perror("connect");

    freeaddrinfo(res);

    return err == 0;
}

bool Socket::send(const void * data, size_t size) {

    char * d = (char*) data;

    while (size > 0) {
        int bytes_sent = ::send(this->sockfd, d, size, 0);
        if (bytes_sent == 0) {
            return false;
        }
        size -= bytes_sent;
    }

    return true;
}

bool Socket::bind(const char * port) {

    int err;
    struct addrinfo hints, *servinfo;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo(NULL, port, &hints, &servinfo);

    err = ::bind(this->sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    freeaddrinfo(servinfo);
    
    err =::listen(this->sockfd, BACKLOG);

    return err == 0;
}

bool Socket::recv(void * buffer, size_t size) {

    char * b = (char*) buffer;

    int num_bytes = ::recv(this->sockfd, b, size, 0);

    if (num_bytes < 0) perror("rec");

    b[num_bytes] = '\0';

    return num_bytes >= 0;
}

void Socket::close() {
    ::close(sockfd);
}

bool Socket::accept() {
    

    unsigned int addrlen, new_socket;
    struct sockaddr_in address;

    addrlen = sizeof(struct sockaddr_in);
    this->sockfd = ::accept(this->sockfd, (struct sockaddr *)&address, &addrlen);

    return true;
}
