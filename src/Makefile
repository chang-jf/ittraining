CC = gcc
SRCS = main.c clouding.c
OBJS = $(SRCS:.c=.o)
INCLUDES = /usr/include
LIBDIRS =
LIBS = -lparse -ljansson
#CFLAGS=	-Wall -Werror -ansi
CFLAGS=
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(LIBDIRS) $(OBJS) -o $(TARGET) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -fR $(TARGET) $(OBJS)

