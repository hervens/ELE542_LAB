CC=gcc
CFLAGS= -Wall -Wformat=0 -ansi -I.
LDFLAGS=
EXEC=util

all: $(EXEC)

util: binary_operations.o sizeof_type.o main.o
		$(CC) -o util binary_operations.o sizeof_type.o main.o $(LDFLAGS)

sizeof_type.o: sizeof_type.c
		$(CC) -o sizeof_type.o -c sizeof_type.c $(CFLAGS)

binary_operations.o: binary_operations.c
		$(CC) -o binary_operations.o -c binary_operations.c $(CFLAGS)

main.o: main.c binary_operations.h sizeof_type.h
		$(CC) -o main.o -c main.c $(CFLAGS)

clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
