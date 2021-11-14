.PHONY: clean all server client

all: clean server client

GCCFLAGS=-g3 -ggdb -m64 -fno-exceptions -Wall -ffreestanding -fno-common -std=c99 -fno-stack-protector
GCC=gcc

server:
	$(GCC) $(GCCFLAGS) server.c -o server
	touch .RUN_ME
	objcopy --add-section .RUN_ME=.RUN_ME  server
	rm .RUN_ME
client:
	$(GCC) $(GCCFLAGS) client.c -o client

clean:
	rm -rf *.o server client
