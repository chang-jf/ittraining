#include <string.h>
#include <curl/curl.h>
#include <mpg123.h>
#include <ao/ao.h>

#include "tts.h"


#define BITS 8

static mpg123_handle *mh = NULL;
static ao_device *dev = NULL;

size_t play_stream(void *buffer, size_t size, size_t nmemb, void *userp)
{
    int err;
    off_t frame_offset;
    unsigned char *audio;
    size_t done;
    ao_sample_format format;
    int channels, encoding;
    long rate;

    mpg123_feed(mh, (const unsigned char*) buffer, size * nmemb);
    do {
        err = mpg123_decode_frame(mh, &frame_offset, &audio, &done);
        switch(err) {
            case MPG123_NEW_FORMAT:
                mpg123_getformat(mh, &rate, &channels, &encoding);
                format.bits = mpg123_encsize(encoding) * BITS;
                format.rate = rate;
                format.channels = channels;
                format.byte_format = AO_FMT_NATIVE;
                format.matrix = 0;
                dev = ao_open_live(ao_default_driver_id(), &format, NULL);
                break;
            case MPG123_OK:
                ao_play(dev, (char*)audio, done);
                break;
            case MPG123_NEED_MORE:
                break;
            default:
                break;
        }
    } while(done > 0);

    return size * nmemb;
}


void str_url(char* url_tts , int txt_len, char* txt, char* lan )
{
    char* url_tts_h = "http://translate.google.com/translate_tts";
    char txt_b[100];

    strcpy(url_tts, url_tts_h);
    strcat(url_tts, "?tl=");
    strcat(url_tts, lan);
    strcat(url_tts, "&q=");
    {
    int i;
        for(i = 0;i<txt_len; i++)
            {

            if(*(txt+i) ==0)
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
}

int TxtToSpeech(int txt_len, char* txt, char* lan)
{
    char url_tts[200];/* = "http://translate.google.com/translate_tts";*/

    str_url(url_tts , txt_len,  txt,  lan );

    ao_initialize();
    
    mpg123_init();
    mh = mpg123_new(NULL, NULL);
    mpg123_open_feed(mh);

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, play_stream);
/*    curl_easy_setopt(curl, CURLOPT_USERAGENT,"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:27.0) Gecko/20100101 Firefox/27.0");*/
/*    curl_easy_setopt(curl, CURLOPT_USERAGENT,"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:7.0.1) Gecko/20100101 Firefox/7.0.1");*/
    curl_easy_setopt(curl, CURLOPT_URL, url_tts);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    ao_close(dev);
    ao_shutdown();

    return 0;
}



