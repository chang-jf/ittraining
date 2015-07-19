
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "./googleTTS/tts.h"


/* Use GPIO Pin 23/24, which is Pin 4/5 for wiringPi library*/

#define BUTTON_PIN 4 


char msg[] ="hello world, temperature is 36.5 degree C, humidity is 55.8%.";
char lan_en[] ="en";

volatile int eventCounter = 0;

#if 0 
/* use wiringPi api */
/* for wiringPi install, reference "http://wiringpi.com/download-and-install/" */
/* myInterrupt:  called every time an event occurs */
#include <wiringPi.h>


void myInterrupt(void) {
    eventCounter=1;
    }

int Btn_init(void)
    {

    if (wiringPiSetup () < 0) {
        fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
        return 1;
        }

    /* set Pin  generate an interrupt on high-to-low transitions and attach myInterrupt() to the interrupt*/
    if ( wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0 ) {
          fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
          return 1;
          }
    return 0;
    }
#else
/*shell command "insmod async.ko" to insert modlue in folder "./Btn/"*/
#include<sys/types.h>
#include<fcntl.h>
#include<signal.h>


int fd = 0;
//int buf[30] ;
char dev_name[] = "/dev/myBtn";

void signal_handler(int num){
    //int len = read(fd, buf, 30);
    //buf[5] = '\0';
    //while(len--) buf[len] = '\0';
        eventCounter = 1;
}

int Btn_init(void)
{
     int pid;
     // setup this process that 
     // if accept a signal: SIGIO
     // call func: signal_handler()
     signal(SIGIO, signal_handler);
     fd = open(dev_name ,O_RDONLY);
     if(fd <= 0) {
         fprintf(stderr,"Error: cannot open %s \n",dev_name);
         return -1;
         }
     pid= getpid();
     printf("process with pid %d START!\n", pid);
     fcntl(fd, F_SETOWN, getpid());
     fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);
     printf("process open device %s with fd: %d\n", dev_name , fd);
     return 0;
}
#endif
      

int main(int argc, char* argv[])
{
    char txt[100];
    
    strcpy(txt,msg);

    Btn_init();
    while(1)
        {   	
        if(eventCounter)
            {	
            TxtToSpeech(strlen(txt) , txt, lan_en);
	    eventCounter=0;
            }
        }

}

