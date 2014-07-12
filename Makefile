
CC=g++
CFLAGS=-c -Wall

all: client server

client: Socket.o client.o
	$(CC) Socket.o client.o -o client

server: Socket.o server.o
	$(CC) Socket.o server.o -o server

client.o: 
	$(CC) $(CFLAGS) client.cpp

server.o:
	$(CC) $(CFLAGS) server.cpp

Socket.o:
	$(CC) $(CFLAGS) Socket.cpp

clean:
	rm -f *.o server client


