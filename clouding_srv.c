#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


char httpHeader[1000] = "HTTP/1.1 200 OK\n"
                        "Content-Type: text/html\n";
//a
char httpBody[1000] = "<html><body>hello 234</body></html>";

int main(int argc, char *argv[])
{
    int sockServer, sockClient;
    struct sockaddr_in sa;
    int optval, ret;
    //unsigned char data[1000];
    char data[1000];

    if( (sockServer=socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror("socket()");
        return -1;
    }

    optval = 1;
    if( setsockopt(sockServer, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) != 0 )
    {
        perror("setsockopt()");
        return -1;
    }

    sa.sin_family = AF_INET;
    sa.sin_port = htons(80);
    sa.sin_addr.s_addr = inet_addr("0.0.0.0");

    if( bind(sockServer, (struct sockaddr*)&sa, sizeof(sa)) < 0 )
    {
        perror("socket()");
        return -1;
    }

    if ( listen(sockServer, 1) < 0 )
    {
        perror("socket()");
        return -1;
    }

    while(1)
    {
        if( (sockClient=accept(sockServer, NULL, NULL)) < 0 )
        {
            perror("socket()");
            return -1;
        }
       
        if( (ret=recv(sockClient, data, sizeof(data)-1, 0)) > 0 )
        {
            data[ret] = '\0';
            printf("%s\n", data);

            sprintf(data, "%s\n%s", httpHeader, httpBody);
            send(sockClient, data, strlen(data), 0);
        }
        else
        {
            perror("recv()");
            return -1;
        }

        close(sockClient);
    }

    close(sockServer);    
    return 0;
}

