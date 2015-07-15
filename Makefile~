all: 	lcd tts clouding si7020
CC=gcc
INCLUDE=
#CFLAGS=	-Wall -Werror -ansi
CFLAGS=	-Wall

lcd:

tts:

si7020:

clouding:clouding.o
	$(CC) -o clouding clouding.o

clouding.o:clouding.c clouding.h
	$(CC) $(CFLAGS) -c clouding.c


clean:
	rm -f clouding.o
	rm -f clouding_srv.o
	rm -f clouding
	rm -f clouding_srv

test:clouding_srv
clouding_srv:clouding_srv.o
	$(CC) -o clouding_srv clouding_srv.o
clouding_srv.o:clouding_srv.c
	$(CC) $(CFLAGS) -c clouding_srv.c
