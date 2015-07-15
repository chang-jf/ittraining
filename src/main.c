#include <stdio.h>
#include <time.h>
#include <parse.h>
#include "clouding.h"

/*void myPushCallback(ParseClient client, int error, const char *buffer) {
  if (error == 0 && buffer != NULL) {
    printf("received push: '%s'\n", buffer);
  }
}*/
int main(int argc, char *argv[]) {
    ParseClient client = parseInitialize("pXOUZN6OVN5aAuLCMm0WvX3yRLJBInn0cmBWA6kj", "9JKl30rKIHt83jlAtcXUGH2UiQj6CFzoIvw4W3Bf");
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"aaa\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"bbb\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"ccc\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"ddd\"}", NULL);
    sleep(6);
    parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"foo\":\"eee\"}", NULL);
    sleep(6);
    
parseSetPushCallback(client, myPushCallback);
parseStartPushService(client);
 
parseRunPushLoop(client);
    return 0;
}

