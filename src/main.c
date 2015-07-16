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
    printf("Initialized\n");
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"temperature\":\"30\", \"humidity\":\"70\"}", NULL);
    sleep(6);
    parseSendRequest(client, "GET", "/1/classes/TestObject", NULL, mySendRequestCallback);
    printf("sent get request\n");

//    curl -X GET -H "X-Parse-Application-Id: pXOUZN6OVN5aAuLCMm0WvX3yRLJBInn0cmBWA6kj" -H "X-Parse-REST-API-Key: aMzETnz9UKWIJRoBX8sytC2wxdItM7Rt6YrnlAuH" -G --data-urlencode 'include=game' https://api.parse.com/1/classes/TestObject
/*    
parseSetPushCallback(client, myPushCallback);
    printf("setted pushcallt\n");
parseStartPushService(client);
 
parseRunPushLoop(client);
*/
    return 0;
}

