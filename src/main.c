#include "clouding.h"

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
        srand(time(NULL));
        Humidity=rand()%100;
        Temperature=rand()%20+20;
        //write(fd, "GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n", strlen("GET /update?key=WFVT9X78TAM164OX&field1=125.0&field2=80\r\n")); // write(fd, char[]*, len);  
        //write(fd, "GET /channels/46080/feed.json?key=WFVT9X78TAM164OX\r\n", strlen("GET /channels/46080/feed.json?key=WFVT9X78TAM164OX\r\n")); // write(fd, char[]*, len);  
        sprintf(command, "GET /update?key=WFVT9X78TAM164OX&field1=%d&field2=%d\r\n", Humidity, Temperature);
        printf("inserting command:\n%s", command);
        write(fd, command, strlen(command)); // write(fd, char[]*, len);  

        bzero(buffer, BUFFER_SIZE);

        while(read(fd, buffer, BUFFER_SIZE - 1) != 0){
            fprintf(stderr, "Server response:%s\n", buffer);
            bzero(buffer, BUFFER_SIZE);
        }
        sleep(RATE_LIMIT);

        shutdown(fd, SHUT_RDWR); 
        close(fd); 

    }


    return 0;
}
