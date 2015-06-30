
#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

/* A socket for sending and receiving data over a connection */
class ClientSocket {
  public:

    /* Creates a new socket to be used. */
    ClientSocket();

    /* Creates a ClientSocket wrapper around an existing
     * socket file descriptor.
     */
    ClientSocket(int socket_fd) : _sock_fd(socket_fd) {}

    /* Connects to addr:port, returns false if fails */
    bool connect(const char * addr, const char * port);

    /* Sends data to socket. Returns false if fails */
    bool send(const void * data, size_t size);

    /* Recieve at most size bytes of data into buffer. 
     * Returns actual amount of bytes recv'd. 
     * Returns -1 on error, 0 on connection closed.
     */
    bool recv(void * buffer, size_t size);

    /* Checks if the socket is valid for using. */
    bool valid();

    /* Close the socket */
    void close();

  private:
    int _sock_fd;
};
