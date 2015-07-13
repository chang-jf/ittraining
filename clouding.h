#ifndef _THINGSPEAK_H
#define _THINGSPEAK_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define RATE_LIMIT          17      //thingspeak limit of an update per channel every 15 seconds
#define BUFFER_SIZE         1024

int socket_connect(char *host, in_port_t port);
#endif // for #ifndef _THINGSPEAK_H
