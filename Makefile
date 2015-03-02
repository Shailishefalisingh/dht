
CC=clang

all: clean
	$(MAKE) -C src $@

clean:
	rm -rf obj
	rm -rf bin
	mkdir obj
	mkdir bin
