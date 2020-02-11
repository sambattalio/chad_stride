
LIB= -lncurses
CC = gcc

chad_stride: chad_stride.c
	$(CC) $(LIB) $^ -o chad_stride
