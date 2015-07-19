
all: mytest
CC = gcc
INSTDIR = /usr/local/bin
INCLUDE = .
CFLAGS = -g -Wall   
LIBS =  -lmpg123 -lao -lcurl

mytest: main.o tts_url.o am2320b.o  
	$(CC) -o mytest main.o tts_url.o am2320b.o  $(LIBS)
main.o: main.c 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c main.c
tts_url.o: ./googleTTS/tts_url.c  
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ./googleTTS/tts_url.c
am2320b.o: ./am2320/am2320b.c  
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ./am2320/am2320b.c



clean:
	rm main.o tts_url.o am2320b.o  
