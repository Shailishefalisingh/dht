
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "ClientSocket.hpp"

/* A socket for listening and accepting connections. */
class ServerSocket {

  public:
    /* Creates a new socket for binding and accepting. */
    ServerSocket();

    /* Binds to port and begins listening. Returns false if fails */
    bool bind(const char * port);

    /* Accepts an incoming connection.
     * Returns a ClientSocket for recv'ing and
     * sending data with this connection.
     */
    ClientSocket accept();

    /* close the socket */
    void close();

  private:
    int _sock_fd;
};
