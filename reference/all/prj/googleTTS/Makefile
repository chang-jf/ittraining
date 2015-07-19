
all: mytest
CC = gcc
INSTDIR = /usr/local/bin
INCLUDE = .
CFLAGS = -g -Wall   
LIBS =  -lmpg123 -lao -lcurl -lwiringPi

mytest: test_.o tts_url.o 
	$(CC) -o mytest test_.o tts_url.o $(LIBS)
main.o: test_.c 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c test_.c
tts_url.o: tts_url.c  
	$(CC) -I$(INCLUDE) $(CFLAGS) -c tts_url.c 


clean:
	rm test_.o tts_url.o 
