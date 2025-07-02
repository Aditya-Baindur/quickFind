CC = gcc
CFLAGS = -Wall -Wextra -O2
PREFIX ?= /usr/local
BIN_DIR = $(PREFIX)/bin

all: quickfind qfcd-init

quickfind: quickfind.c
	$(CC) $(CFLAGS) -o quickfind quickfind.c

qfcd-init: qfcd-init.c
	$(CC) $(CFLAGS) -o qfcd-init qfcd-init.c

install: all
	@echo "Installing to $(BIN_DIR)..."
	mkdir -p $(DESTDIR)$(BIN_DIR)
	cp quickfind $(DESTDIR)$(BIN_DIR)/
	cp qfcd-init $(DESTDIR)$(BIN_DIR)/
	@echo
	@echo "✅ Installation complete."
	@echo
	@echo "🧠 NOTE: To use 'qfcd' in your current shell session, run:"
	@echo "    . /etc/profile.d/qfcd.sh"
	@echo
	@echo "💡 It will be auto-loaded in all future login shells."

uninstall:
	@echo "Uninstalling quickfind and qfcd..."
	sudo rm -f $(BIN_DIR)/quickfind
	sudo rm -f $(PROFILE_SCRIPT)
ifeq ($(a),true)
	@echo "Removing alias database..."
	rm -rf ~/.quickfind
endif
	@echo "Uninstallation complete."

clean:
ifeq ($(force),true)
	$(MAKE) uninstall a=true
	rm -f quickfind qfcd-init
else
	rm -f quickfind qfcd-init
endif
