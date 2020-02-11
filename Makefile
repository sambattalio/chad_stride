CC= 	gcc
LIB= 	-Wall -lncurses
PREFIX= /usr/local
OPTIMIZATIONS= O3

chad_stride: 	chad_stride.c
	$(CC) -$(OPTIMIZATIONS) -o $@ $^ $(LIB)

install: 	chad_stride
	install -m 755 -D chad_stride $(PREFIX)/bin/chad_stride

uninstall:
	rm -f $(PREFIX)/bin/chad_stride

clean:
	rm -f chad_stride
