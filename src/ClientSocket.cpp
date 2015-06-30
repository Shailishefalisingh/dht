
#include "ClientSocket.hpp"
#include <iostream>

ClientSocket::ClientSocket() {
  _sock_fd = -1;
}

bool ClientSocket::connect(const char * addr, const char * port) {

  int err = 0;

  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  err = getaddrinfo(addr, port, &hints, &res);

  _sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  err = ::connect(_sock_fd, res->ai_addr, res->ai_addrlen);

  if (err < 0) perror("connect");

  freeaddrinfo(res);

  return err == 0;
}


bool ClientSocket::send(const void * data, size_t size) {

  char * d = (char*) data;
  int bytes_sent = 0;

  while (bytes_sent < size) {
    int sent = ::send(_sock_fd, d + bytes_sent, size, 0);
    if (sent < 1) {
      return false;
    }
    bytes_sent += sent;
  }

  return true;
}


int ClientSocket::recv(void * buffer, size_t size) {

  char * b = (char*) buffer;

  int num_bytes = ::recv(_sock_fd, b, size, 0);

  if (num_bytes < 0) perror("recv");

  return num_bytes;
}

bool ClientSocket::valid() {
  return _sock_fd >= 0;
}

void ClientSocket::close() {
  ::close(_sock_fd);
  _sock_fd = -1;
}
