
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tts.h"
   
/*
char msg[] ="hello world";//, today's temperature is 36 degree C, humidity 55%."
char lan_en[] ="en";


int TxtToSpeech(int txt_len, char* txt ,char * lan);

int main(int argc, char* argv[])
{
    char txt[100];
    
strcpy(txt,msg);
   
TxtToSpeech(strlen(txt) , txt, lan_en);


}
*/

int TxtToSpeech(int txt_len, char* txt, char* lan)
{
  //  char txt_uwrl[200];
    char url_tts[200] = "mpg123 -q \"http://translate.google.com/translate_tts"; 
    char txt_b[100];

    //strcp(txt, url_tts_head);

    strcat(url_tts, "?tl=");
    strcat(url_tts, lan);
    strcat(url_tts, "&q=");
    {
    int i;
        for(i = 0;i<txt_len; i++)
            {
     
            if(*(txt+i) ==0)
            //    txt_b[i] = '\"';
            //    txt_b[i+1]=0;
               break; 
            else if(*(txt+i) == ' ')
                txt_b[i] = '+';
            else
                txt_b[i] = *(txt+i);
            }
            txt_b[i] = '\"';
            txt_b[i+1]=0;
    }
    strcat(url_tts, txt_b);
//    strcat(url_tts, " -O /tmp/tts_tmp.mp3");
//    printf((char*) url_tts);          
    system(url_tts);

//    usleep(1);
//    system("mpg123 -q /tmp/tts_tmp.mp3");
 
}






