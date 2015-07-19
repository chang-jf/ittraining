#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>              /* for O_RDWR */
#include <string.h>             /* for memcpy */
#include <sys/ioctl.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include <errno.h>

#include "./LCD/disp.h"
#include "./am2320/am2320b.h"   
#include "./googleTTS/tts.h"


	struct ioctl_mesg msg;
//	const char *ioctl_command;
//	char command;
	int fd; //for LCD
	char temp[10],hum[10];

        st_am2321 measured;



/* Use GPIO Pin 23/24, which is Pin 4/5 for wiringPi library*/

#define BUTTON_PIN 4


char amsg[] ="hello world, temperature is 36.5 degree C, humidity is 55.8%.";
char lan_en[] ="en";

volatile int eventCounter = 0;

#if 0
/* use wiringPi api */
/* for wiringPi install, reference "http://wiringpi.com/download-and-install/" */
/* myInterrupt:  called every time an event occurs */
#include <wiringPi.h>

nterrupt(void) {
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


int fd_b = 0;
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
     signal(SIGIO, signal_handler);
     fd_b = open(dev_name ,O_RDONLY);
     if(fd_b <= 0) {
          fprintf(stderr,"Error: cannot open %s \n",dev_name);
          return -1;
          }
     pid= getpid();
     printf("process with pid %d START!\n", pid);
     fcntl(fd_b, F_SETOWN, getpid());
     fcntl(fd_b, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);
     printf("process open device %s with fd: %d\n", dev_name , fd);
     return 0;
}


void Btn_exit(void)
    {
  close(fd_b); /* close /device/klcd   */
    }
#endif


void sound_out(void)
{

    char txt[100];

    strcpy(txt,amsg);

	    TxtToSpeech(strlen(txt) , txt, lan_en);
}

lcd_putStr_at(uint8_t line, uint8_t row, char *str)
{
	
	strncpy( msg.kbuf, str,  MAX_BUF_LENGTH);
	msg.lineNumber   = line; 
	msg.nthCharacter = row; 
	if( ioctl( fd, (unsigned int) IOCTL_PRINT_WITH_POSITION, &msg) < 0)
				perror("[ERROR] IOCTL_PRINT_WITH_POSITION \n");
}


void lcd_format()
{
lcd_putStr_at(1,0,"T:      ");
lcd_putStr_at(1,8,"C        ");
lcd_putStr_at(2,0,"H:      ");
lcd_putStr_at(2,8,"%        ");	
}

void lcd_disp (void)
{
    
    /* send temperature & humidity to LCD module*/	
		sprintf(temp,"%d", am2321_temperature_integral( measured ));
		lcd_format();
		lcd_putStr_at(1,3,temp);
		lcd_putStr_at(1,5,".");
		sprintf(temp,"%d", am2321_temperature_fraction( measured ));
		lcd_putStr_at(1,6,temp);		
		
		sprintf(hum, "%d", am2321_humidity_integral( measured ));
		lcd_putStr_at(2,3,hum);
	    lcd_putStr_at(2,5,".");
	    sprintf(hum, "%d", am2321_humidity_fraction( measured ));
		lcd_putStr_at(2,6,hum);
}

int LCD_init(void)
    {

/* open /dev/klcd */
	fd = open("/dev/klcd", O_WRONLY | O_NDELAY);
	if(fd < 0){
		printf("[User level Debug] ERR: Unable to open klcd \n");
		return -1;
	}
    }


void LCD_exit(void)
    {
  close(fd); /* close /device/klcd   */
    }



int main( int argc, char* argv[] ) {
    int options;



    if(Btn_init() < 0)
	    return -1;


   if(LCD_init() < 0) 
	  return -1 ; 
     

/* measure 1th temperature and humidity */
   
    while(1){
	 
	if(eventCounter)
	    {
            sound_out();
	    eventCounter=0;
	    }
	        
	/* measure temperature and humidity */
	//measured = ! is_opt_stub( options ) ? am2321() : am2321_stub();
	 measured = am2321();
	
	 print_am2321( measured );	 /* print temperature & Humidity to terminal */
	
        lcd_disp();

        sleep(5);
        }
    LCD_exit(); 
    Btn_exit();
  return 0;
}
