//prologue, description of purpose of the objects in the file, (optional) author, (optional) revision control. (optional) reference.
//header file includes, system header files firse
//defines and typedefs in this order: constant macros->function macros->typedefs->enums
//global(external) data declarations in this order: externs->non-static globals->static globals
//function definition, groups by similar levels of abstraction, large numbers of essentially-independant utility functions->consider order by alphabetical order.
#ifndef _CLOUDING_H
#define _CLOUDING_H

#include <jansson.h>
#define APPLICATION_ID      "pXOUZN6OVN5aAuLCMm0WvX3yRLJBInn0cmBWA6kj"

#define CLIENT_KEY          "9JKl30rKIHt83jlAtcXUGH2UiQj6CFzoIvw4W3Bf"
#define PARSE_PATH          "/1/classes/TestObject"
#define RATE_LIMIT          1      //parse limit: 30 req/s, respect to rate limit
#define BUFFER_SIZE         1024    //buffer for sending command to cloud, as well as receive from cloud
//structure parse_payload initiator: //usage: INIT_PARSE_PAYLOAD(upload); 
//#define INIT_PARSE_PAYLOAD(X) parse_payload X = {.objectId = "", .Temperature = "", .Humidity = "", .createdAt = "", .updatedAt = ""}

//payload structure for upload/download single record to parse
typedef struct
{ 
    char *objectId;         /**/    
    char *Temperature;      /**/
    char *Humidity;         /**/
    char *createdAt;        /**/
    char *updatedAt;        /**/
} parse_payload;

//FIXME data sample from parse.com, separate this to other document.
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

    //parseSendRequest(client, "POST", "/1/classes/TestObject", "{\"temperature\":\"30\", \"humidity\":\"70\"}", NULL);
    //sleep(1);
    //parseSendRequest(client, "GET", "/1/classes/TestObject", NULL, mySendRequestCallback);
int parseSend(parse_payload *);
int parseRecv(parse_payload *);

//callBack function to handle send result
void SendCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody);
//callBack function to handle send result
void RecvCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody);


//payload initiator -- allocate memory for payload
parse_payload *payload_initiator();
//payload destroyer -- release payload memory
int payload_destroyer(parse_payload *payload_t);
//print out payload content for debug purpose
void payload_printer(parse_payload *payload_t);

//convert a int number to string
char *int2str(int);
//convert a string to int
int str2int(char *);

//FIXME: consider separate JSON manipulator to other module
//convert payload structure to json object
json_t          *payloadToJsonObj(parse_payload *);
//convert json object to payload structure
parse_payload   *jsonObjToPayload(json_t *);
//convert json object to json string
char *          jsonObjToJsonStr(json_t *);
//convert json string to json object
json_t          *jsonStrToJsonObj(char *);
//convert payload to json str
char            *payloadToJsonStr(parse_payload *);
//convert json str payload
parse_payload   *JsonStrToPayload(char *);

//convert string to int
//convert int to string

//sample code for demonstrate jansson API usage, remove before 1.st release
int handleJson(const char *);

//reference code - delete this if we don't need push service
void myPushCallback(ParseClient client, int error, const char *buffer);



#endif // for #ifndef _CLOUDING_H
