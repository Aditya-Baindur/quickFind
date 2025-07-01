CC=gcc
CFLAGS=-Wall

all:
	gcc -Wall -o quickfind quickfind.c

install:
	sudo cp quickfind /usr/local/bin/

uninstall:
	sudo rm -f /usr/local/bin/quickfind

clean:
	rm -f quickfind

