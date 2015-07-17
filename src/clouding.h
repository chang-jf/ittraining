#ifndef _CLOUDING_H
#define _CLOUDING_H

#include <jansson.h>
#define APPLICATION_ID      "pXOUZN6OVN5aAuLCMm0WvX3yRLJBInn0cmBWA6kj"
#define CLIENT_KEY          "9JKl30rKIHt83jlAtcXUGH2UiQj6CFzoIvw4W3Bf"
#define PARSE_PATH          "/1/classes/TestObject"
#define RATE_LIMIT          1      //parse limit: 30 req/s
#define BUFFER_SIZE         1024    //buffer for sending command to cloud, as well as receive from cloud

//parse payload structure for upload/download single record
typedef struct
{ 
    char *objectId;
    char *Temperature;
    char *Humidity;
    char *createdAt;
    char *updatedAt;
} parse_payload;

//structure parse_payload initiator: 
//usage: INIT_PARSE_PAYLOAD(upload); 
#define INIT_PARSE_PAYLOAD(X) parse_payload X = {.objectId = '\0', .Temperature = '\0', .Humidity = '\0', .createdAt = '\0', .updatedAt = '\0'}

/*#define PARSE_RESPONSE_STRUCTURE    
 *{
 *    "results":[
 *    {   "createdAt":"2015-07-16T03:23:42.393Z",
 *        "foo":"today",
 *        "objectId":"yqmPYNWez9",
 *        "updatedAt":"2015-07-16T03:23:42.393Z"},
 *    {
 *        "createdAt":"2015-07-16T03:23:49.555Z",
 *        "foo":"tomorrow",
 *        "objectId":"kt3WvbHjmN",
 *        "updatedAt":"2015-07-16T03:23:49.555Z"}
 *    ]
 *}
 */

int handleJson(const char *);
//convert payload structure to json object
json_t          *payloadToJsonObj(parse_payload);
//convert json object to payload structure
parse_payload   jsonObjToPayload(json_t *);
//convert json object to json string
char *          jsonObjToJsonStr(json_t *);
//convert json string to json object
json_t          *jsonStrToJsonObj(char *);
//convert payload to json str
char            *payloadToJsonStr(parse_payload);
//convert json str payload
parse_payload   JsonStrToPayload(char *);


void mySendRequestCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody);

void myPushCallback(ParseClient client, int error, const char *buffer);
    //parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"temperature\":\"30\", \"humidity\":\"70\"}", NULL);
    //sleep(1);
    //parseSendRequest(client, "GET", "/1/classes/TestObject", NULL, mySendRequestCallback);
int parseSend(parse_payload);
int parseRecv(parse_payload);



#endif // for #ifndef _CLOUDING_H
