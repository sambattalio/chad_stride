CC= 	gcc
CFLAGS=	-Wall -std=gnu99 -O3
LIB= 	-lncurses
PREFIX= /usr/local

chad_stride: 	chad_stride.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

install: 	chad_stride
	mkdir -p $(PREFIX)/bin
	install -m 755 chad_stride $(PREFIX)/bin/chad_stride
	mkdir -p $(PREFIX)/share/man/man1
	install -m644 chad_stride.1 $(PREFIX)/share/man/man1/chad_stride.1
	ln -sf $(PREFIX)/bin/chad_stride $(PREFIX)/bin/cs

uninstall:
	rm -f $(PREFIX)/bin/chad_stride
	rm -f $(PREFIX)/share/man/man1/chad_stride.1
	rm -f $(PREFIX)/bin/cs

clean:
	rm -f chad_stride
