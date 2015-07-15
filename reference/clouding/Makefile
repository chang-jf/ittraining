CC = gcc
SRCS = main.c
OBJS = $(SRCS:.c=.o)
INCLUDES = /usr/include
LIBDIRS =
LIBS = -lparse
#CFLAGS=	-Wall -Werror -ansi
CFLAGS=	-Wall
TARGET = quickstart

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(LIBDIRS) $(OBJS) -o $(TARGET) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -fR $(TARGET) $(OBJS)

