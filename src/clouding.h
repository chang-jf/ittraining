#ifndef _CLOUDING_H
#define _CLOUDING_H
#include <parse.h>

#define RATE_LIMIT          17      //parse limit of an update per channel every 15 seconds
#define BUFFER_SIZE         1024    //buffer for sending command to cloud, as well as receive from cloud

void myPushCallback(ParseClient client, int error, const char *buffer);
#endif // for #ifndef _CLOUDING_H
