
#include "ClientSocket.hpp"
#include <iostream>

ClientSocket::ClientSocket() {
  _sock_fd = socket(AF_INET, SOCK_STREAM, 0);
}

bool ClientSocket::connect(const char * addr, const char * port) {

  int err = 0;

  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  err = getaddrinfo(addr, port, &hints, &res);

  std::cout << _sock_fd << std::endl;

  err = ::connect(_sock_fd, res->ai_addr, res->ai_addrlen);

  if (err < 0) perror("connect");

  freeaddrinfo(res);

  return err == 0;
}


bool ClientSocket::send(const void * data, size_t size) {

  char * d = (char*) data;

  while (size > 0) {
    int bytes_sent = ::send(_sock_fd, d, size, 0);
    if (bytes_sent == 0) {
      return false;
    }
    size -= bytes_sent;
  }

  return true;
}


bool ClientSocket::recv(void * buffer, size_t size) {

  char * b = (char*) buffer;

  int num_bytes = ::recv(_sock_fd, b, size, 0);

  if (num_bytes < 0) perror("rec");

  b[num_bytes] = '\0';

  return num_bytes >= 0;
}

bool ClientSocket::valid() {
  return _sock_fd >= 0;
}

void ClientSocket::close() {
  ::close(_sock_fd);
  _sock_fd = -1;
}
