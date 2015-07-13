/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
*/
#include "clouding.h"

/*#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
*/

//#define rate_limit      17      //thingspeak limit of an update per channel every 15 seconds

int socket_connect(char *host, in_port_t port){
        struct hostent *hp;
        struct sockaddr_in addr;
        int on = 1, sock;
        
        if((hp = gethostbyname(host)) == NULL){
                herror("gethostbyname");
                exit(1);
        }
        bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));
        
        if(sock == -1){
                perror("setsockopt");
                exit(1);
        }
        
        if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
                perror("connect");
                exit(1);
                
        }
        return sock;
}

#define BUFFER_SIZE 1024

 int main(int argc, char *argv[]){
        int fd;
        char buffer[BUFFER_SIZE];
        char command[BUFFER_SIZE];
        int Humidity=0;
        int Temperature=0;
        
        if(argc < 3){
                //fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
                fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
                fprintf(stderr, "eg: ./socket api.thingspeak.com 80\n");
                exit(1); 
        }
               

while(1){

        fd = socket_connect(argv[1], atoi(argv[2])); 
        //write(fd, "GET /\r\n", strlen("GET /\r\n")); // write(fd, char[]*, len);  
        //
        //write: GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n
        //read: GET /channels/46079/feed.json?key=WFVT9X78TAM164OX\r\n
        //
        //write(fd, "GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n", strlen("GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n")); // write(fd, char[]*, len);  
        //write(fd, "GET /channels/46080/feed.json?key=WFVT9X78TAM164OX\r\n", strlen("GET /channels/46080/feed.json?key=WFVT9X78TAM164OX\r\n")); // write(fd, char[]*, len);  
        //Humidity 0~100
        //Temperature 20~40
        srand(time(NULL));
        Humidity=rand()%100;
        Temperature=rand()%20+20;
        sprintf(command, "GET /update?key=WFVT9X78TAM164OX&field1=%d&field2=%d\r\n", Humidity, Temperature);
        printf("inserting command:\n%s", command);
        //write(fd, "GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n", strlen("GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n")); // write(fd, char[]*, len);  
        write(fd, command, strlen(command)); // write(fd, char[]*, len);  

        bzero(buffer, BUFFER_SIZE);
                
        while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
                fprintf(stderr, "Server response:%s\n", buffer);
                bzero(buffer, BUFFER_SIZE);
        }
        /*
        read(fd, buffer, BUFFER_SIZE - 1);
        fprintf(stderr, "%s", buffer);
        bzero(buffer, BUFFER_SIZE);
        */

        /*
        printf("%s", command);
        */
        sleep(RATE_LIMIT);
        /*
        i++;
        */
        
        shutdown(fd, SHUT_RDWR); 
        close(fd); 

}

        
        return 0;
}
