
CC=g++
CFLAGS=-std=c++11 -pthread -Wall
LFLAGS=

SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,../obj/%.o,$(SRCS))

all: test_client test_server

test_client: $(OBJS)
	$(CC) $(CFLAGS) -o ../bin/test_client $(OBJS) $(LFLAGS)

test_server: $(OBJS)
	$(CC) $(CFLAGS) -o ../bin/test_server $(OBJS) $(LFLAGS)

../obj/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

