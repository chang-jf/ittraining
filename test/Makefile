all:clouding_srv
CC=gcc
INCLUDE=
#CFLAGS=	-Wall -Werror -ansi
CFLAGS=	-Wall


test:clouding_srv

clouding_srv:clouding_srv.o
	$(CC) -o clouding_srv clouding_srv.o
clouding_srv.o:clouding_srv.c
	$(CC) $(CFLAGS) -c clouding_srv.c
clean:
	rm -f clouding_srv *.o
