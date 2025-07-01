CC=gcc
CFLAGS=-Wall

all:
	gcc -Wall -o quickfind quickfind.c

install:
	gcc -Wall -o quickfind quickfind.c
	sudo cp quickfind /usr/local/bin/

uninstall:
	@echo "Uninstalling quickfind..."
	sudo rm -f /usr/local/bin/quickfind
ifeq ($(a),true)
	@echo "Removing alias database..."
	rm -rf ~/.quickfind
endif
	@echo "Uninstallation complete."


clean:
ifeq ($(force),true)
	$(MAKE) uninstall
	rm -f quickfind
else
	rm -f quickfind
endif

build:
	gcc -Wall -o quickfind quickfind.c
	sudo cp quickfind /usr/local/bin