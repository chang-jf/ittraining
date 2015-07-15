#include <stdio.h>
#include <parse.h>
#include <unistd.h>
#include "clouding.h"

/*void myPushCallback(ParseClient client, int error, const char *buffer) {
  if (error == 0 && buffer != NULL) {
    printf("received push: '%s'\n", buffer);
  }
}*/
int main() {
    ParseClient client = parseInitialize(APPLICATION_ID, CLIENT_KEY);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"fff\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"ggg\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"hhh\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"iii\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"jjj\"}", NULL);
    sleep(6);
    
parseSetPushCallback(client, myPushCallback);
parseStartPushService(client);
 
parseRunPushLoop(client);
    return 0;
}

