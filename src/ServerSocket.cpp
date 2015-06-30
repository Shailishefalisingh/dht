
#include "ServerSocket.hpp"
#include <iostream>

ServerSocket::ServerSocket() {

  _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
}

bool ServerSocket::bind(const char * port) {

  int err;
  struct addrinfo hints, *servinfo;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  err = getaddrinfo(NULL, port, &hints, &servinfo);

  err = ::bind(_sock_fd, servinfo->ai_addr, servinfo->ai_addrlen);

  freeaddrinfo(servinfo);

  err = ::listen(_sock_fd, SOMAXCONN);

  return err == 0;
}


void ServerSocket::close() {
  ::close(_sock_fd);
}

ClientSocket ServerSocket::accept() {

  unsigned int addrlen;
  struct sockaddr_in address;

  addrlen = sizeof(struct sockaddr_in);
  return ClientSocket(::accept(_sock_fd, (struct sockaddr *)&address, &addrlen));
}
