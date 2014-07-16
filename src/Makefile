
CC=g++
CFLAGS=-std=c++11 -pthread -Wall
LFLAGS=

SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,../obj/%.o,$(SRCS))

test_client: $(OBJS)
    $(CC) $(CFLAGS) -o ../bin/test_client $(OBJS) $(LFLAGS)

test_server: $(OBJS)
    $(CC) $(CFLAGS) -o ../bin/test_server $(OBJS) $(LFLAGS)

../obj/%.o: %.c
    $(CC) $(CFLAGS) -c -o $@ $<

