
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

class Socket {
    
    public:

        Socket();

        /* Prepares to send data to addr:port, returns false if fails */
        bool connect(const char * addr, const char * port);

        /* Sends data to destination chosen by the connect method. Returns false if fails */
        bool send(const void * data, size_t size);

        /* Binds to port. Returns false if fails */
        bool bind(const char * port);

        /* Recieve size bytes of data into buffer from port that you are listening on. Returns false if fails. */
        bool recv(void * buffer, size_t size);

        bool accept();

        /* close the socket */
        void close();

    private:

        int sockfd;
};
