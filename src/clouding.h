#ifndef _CLOUDING_H
#define _CLOUDING_H
#include <parse.h>

#define APPLICATION_ID      "pXOUZN6OVN5aAuLCMm0WvX3yRLJBInn0cmBWA6kj"
#define CLIENT_KEY          "9JKl30rKIHt83jlAtcXUGH2UiQj6CFzoIvw4W3Bf"
#define RATE_LIMIT          17      //parse limit of an update per channel every 15 seconds
#define BUFFER_SIZE         1024    //buffer for sending command to cloud, as well as receive from cloud
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

//void parseSetPushCallback (ParseClient client, parsePushCallback callback)
//typedef void(*  parsePushCallback) (ParseClient client, int error, const char *data)
void myPushCallback(ParseClient client, int error, const char *buffer);

//void parseSendRequest (ParseClient client, const char *httpVerb, const char *httpPath, const char *httpRequestBody, parseRequestCallback callback)
//typedef void(*  parseRequestCallback) (ParseClient client, int error, int httpStatus, const char *httpResponseBody)
void mySendRequestCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody);
#endif // for #ifndef _CLOUDING_H
