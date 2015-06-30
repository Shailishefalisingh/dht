
CC=clang++
CFLAGS=-std=c++11 -Wall
LFLAGS=-lcurses -lreadline

SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,../obj/%.o,$(SRCS))

all: test_server

test_server: $(OBJS)
	$(CC) $(CFLAGS) -o ../bin/test_server $(OBJS) $(LFLAGS)

../obj/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

