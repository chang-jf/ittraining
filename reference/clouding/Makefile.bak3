CC=gcc
INCLUDE=
#CFLAGS=	-Wall -Werror -ansi
CFLAGS=	-Wall

all: 	main

main:	main.o clouding.o
	$(CC) -o main main.o clouding.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clouding.o: clouding.c
	$(CC) $(CFLAGS) -c clouding.c

clean:
	rm -f main *.o
