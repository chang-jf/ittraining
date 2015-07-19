#include <stdio.h>
#include <string.h>
#include <parse.h>
#include <jansson.h>
#include <unistd.h>
#include "clouding.h"
#include "clouding_test.c"


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  upload ipayload content upto IOT service
 *
 * @Param payload   IOT data container
 *
 * @Returns   0: success FIXME:add a callback function for error handle
 */
/* ----------------------------------------------------------------------------*/
int parseSend(parse_payload *payload)
{
    /*payload_printer(payload);*/
    ParseClient client = parseInitialize(APPLICATION_ID, CLIENT_KEY);
    //parseSendRequest(client, "POST", PARSE_PATH, payloadToJsonStr(*payload), NULL);
    printf("Sending to server:\n%s\n", payloadToJsonStr(payload));
    parseSendRequest(client, "POST", PARSE_PATH, payloadToJsonStr(payload), SendCallback);
    sleep(RATE_LIMIT);
    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  download 1 record from IOT services, and fill into payload, 
 *
 * @Param payload   IOT datacontainer
 *
 * @Returns   0: success FIXME: place requested data into payload
 */
/* ----------------------------------------------------------------------------*/
int parseRecv(parse_payload *payload)
{
    ParseClient client = parseInitialize(APPLICATION_ID, CLIENT_KEY);
    parseSendRequest(client, "GET", PARSE_PATH, NULL, RecvCallback);
    sleep(RATE_LIMIT);
    return 0;
}

void SendCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody){
    (void) client;		                        //avoid "unused parameter client" warning
    if (error == 0 && httpResponseBody != NULL) {       //request success       

    } else {                                            //request fail
    }
}
void RecvCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody)
{
    (void) client;		//avoid "unused parameter client" warning

    if (error == 0 && httpResponseBody != NULL) {
	printf("Parse server : Request successed!\n");
	printf("error=%d\n", error);
	printf("httpStatus=%d\n", httpStatus);
	printf("httpResponseBody:\n%s\n", httpResponseBody);
	printf("======================================\n");
	//handleJson(httpResponseBody);

    } else {
	printf("Parse server : Request failure!\n");
	printf("error_no=%d\n", error);
	printf("httpStatus=%d\n", httpStatus);
	printf("httpResponseBody:\n%s\n", httpResponseBody);
    }
}

//payload initiator -- allocate memory for payload
parse_payload *payload_initiator()
{
    parse_payload *payload_t = (parse_payload *)malloc(sizeof(parse_payload));
    if((payload_t) == NULL){ perror("malloc"); exit(-1); }

    payload_t->objectId = (char *)malloc(sizeof(char));
    if((payload_t->objectId) == NULL){ perror("malloc"); exit(-1); }
    payload_t->Temperature = (char *)malloc(sizeof(char));
    if((payload_t->Temperature) == NULL){ perror("malloc"); exit(-1); }
    payload_t->Humidity = (char *)malloc(sizeof(char));
    if((payload_t->Humidity) == NULL){ perror("malloc"); exit(-1); }
    payload_t->createdAt = (char *)malloc(sizeof(char));
    if((payload_t->createdAt) == NULL){ perror("malloc"); exit(-1); }
    payload_t->updatedAt = (char *)malloc(sizeof(char));
    if((payload_t->updatedAt) == NULL){ perror("malloc"); exit(-1); }

    strcpy(payload_t->objectId, "");
    strcpy(payload_t->Temperature, "");
    strcpy(payload_t->Humidity, "");
    strcpy(payload_t->createdAt, "");
    strcpy(payload_t->updatedAt, "");
    return payload_t;
}
/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  payload destroyer -- release payload memory
 *
 * @Param payload_t 
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int payload_destroyer(parse_payload *payload_t)
{
    free(payload_t->objectId);
    free(payload_t->Temperature);
    free(payload_t->Humidity);
    free(payload_t->createdAt);
    free(payload_t->updatedAt);
    free(payload_t);
    return 0;   
}

//print out payload content for debug purpose
void payload_printer(parse_payload *payload){
    if(strlen(payload->objectId)    !=  strlen("")){
        printf("payload->objectId:\t%s\n", payload->objectId);
    }
    if(strlen(payload->Temperature) !=  strlen("")){
        printf("payload->Temperature:\t%s\n", payload->Temperature);
    }
    if(strlen(payload->Humidity)    !=  strlen("")){
        printf("payload->Humidity:\t%s\n", payload->Humidity);
    }
    if(strlen(payload->createdAt)   !=  strlen("")){
        printf("payload->createdAt:\t%s\n", payload->createdAt);
    }
    if(strlen(payload->updatedAt)   !=  strlen("")){
        printf("payload->updatedAt:\t%s\n", payload->updatedAt);
    }
}

//convert a int number to string
char *int2str(int i){
    char *str=(char *)malloc(sizeof(char));
    if(sprintf(str, "%d", i)<0){
        perror("should not be there, sprintf fail");
    }
    return str;
}
//convert a string to int
int str2int(char *s){
    return atoi(s);
}

//convert payload structure to json object, only elementals with value convert into json object
json_t *payloadToJsonObj(parse_payload *payload)
{
    json_t *obj = json_object();
    if(strlen(payload->objectId)    !=  strlen("")){
       // printf("there is objectId\n");
        json_object_set_new(obj, "objectId", json_string(payload->objectId));
    }
    if(strlen(payload->Temperature) !=  strlen("")){
     //   printf("there is Temperature\n");
        json_object_set_new(obj, "Temperature", json_string(payload->Temperature));
    }
    if(strlen(payload->Humidity)    !=  strlen("")){
     //   printf("there is Humidity\n");
        json_object_set_new(obj, "Humidity", json_string(payload->Humidity));
    }
    if(strlen(payload->createdAt)   !=  strlen("")){
     //   printf("there is createdAt\n");
        json_object_set_new(obj, "createdAt", json_string(payload->createdAt));
    }
    if(strlen(payload->updatedAt)   !=  strlen("")){
     //   printf("there is updatedAt\n");
        json_object_set_new(obj, "updatedAt", json_string(payload->updatedAt));
    }
    return obj;
}

//convert json object to payload structure
parse_payload *jsonObjToPayload(json_t * obj)
{
    parse_payload *payload=payload_initiator();

    if(json_object_get(obj, "objectId")!=NULL){
        payload->objectId = (char *) malloc(strlen(json_string_value(json_object_get(obj, "objectId"))) * sizeof(char));
        strcpy(payload->objectId, json_string_value(json_object_get(obj, "objectId")));
    }
    if(json_object_get(obj, "Temperature")!=NULL){
        payload->Temperature = (char *) malloc(strlen (json_string_value(json_object_get(obj, "Temperature"))) * sizeof(char));
        strcpy(payload->Temperature, json_string_value(json_object_get(obj, "Temperature")));
    }
    if(json_object_get(obj, "Humidity")!=NULL){
        payload->Humidity = (char *) malloc(strlen(json_string_value(json_object_get(obj, "Humidity"))) * sizeof(char));
        strcpy(payload->Humidity, json_string_value(json_object_get(obj, "Humidity")));
    }
    if(json_object_get(obj, "createdAt")!=NULL){
        payload->createdAt = (char *) malloc(strlen(json_string_value(json_object_get(obj, "createdAt"))) * sizeof(char));
        strcpy(payload->createdAt, json_string_value(json_object_get(obj, "createdAt")));
    }
    if(json_object_get(obj, "updatedAt")!=NULL){
        payload->updatedAt = (char *) malloc(strlen(json_string_value(json_object_get(obj, "updatedAt"))) * sizeof(char));
        strcpy(payload->updatedAt, json_string_value(json_object_get(obj, "updatedAt")));
    }


    return payload;
}

//convert json object to json string
char *jsonObjToJsonStr(json_t * obj)
{
    char *str;
    str = json_dumps(obj, 0);
    json_decref(obj);
    return str;
}

//convert json string to json object
json_t *jsonStrToJsonObj(char *str)
{
    json_t *obj = json_object();
    json_error_t err = { 0 };
    obj = json_loads(str, 0, &err);
    free(str);
    return obj;
}

//convert payload to json str(payload->jObj->jStr
char *payloadToJsonStr(parse_payload *payload)
{
    return jsonObjToJsonStr(payloadToJsonObj(payload));
}

//convert json str to payload
parse_payload *JsonStrToPayload(char *str)
{
    return jsonObjToPayload(jsonStrToJsonObj(str));
}

int handleJson(const char *Json)
{
    size_t i;
    json_t *root;
    json_error_t err;
    char *localJson = (char *) malloc(strlen(Json) * sizeof(char));

    printf("JsonFromSrv_length:%ld\nstring:%s\n\n", strlen(Json), Json);
    strncpy(localJson, Json, strlen(Json) - 2);	//tear off last two char '}\0'
    localJson += 11;		//unpack Json which responsed from Parse, remove first 11 chars and last two chars

    printf("handleJson_length:%ld\nstring:%s\n\n", strlen(localJson),
	   localJson);
    root = json_loads(localJson, 0, &err);
    if (!root) {
	fprintf(stderr, "error: on line %d: %s\n", err.line, err.text);
	return -1;
    }
    if (!json_is_array(root)) {
	fprintf(stderr, "error: root is not an array\n");
	json_decref(root);
	return -1;
    }
    for (i = 0; i < json_array_size(root); ++i) {
	json_t *data, *objectId, *temperature, *humidity, *createdAt,
	    *updatedAt;

	data = json_array_get(root, i);
	if (!json_is_object(data)) {
	    fprintf(stderr, "error: commit data %ld is not an object\n",
		    i + 1);
	    json_decref(root);
	    return -1;
	}
	objectId = json_object_get(data, "objectId");
	if (!json_is_string(objectId)) {
	    fprintf(stderr, "error: record %ld objectId is not a string\n",
		    i + 1);
	    json_decref(root);
	    return -1;
	}
	temperature = json_object_get(data, "temperature");
	if (!json_is_string(temperature)) {
	    fprintf(stderr,
		    "error: record %ld temperature is not a string\n",
		    i + 1);
	    json_decref(root);
	    return -1;
	}
	humidity = json_object_get(data, "humidity");
	if (!json_is_string(humidity)) {
	    fprintf(stderr, "error: record %ld humidity is not a string\n",
		    i + 1);
	    json_decref(root);
	    return -1;
	}
	createdAt = json_object_get(data, "createdAt");
	if (!json_is_string(createdAt)) {
	    fprintf(stderr,
		    "error: record %ld createdAt is not a string\n",
		    i + 1);
	    json_decref(root);
	    return -1;
	}
	updatedAt = json_object_get(data, "updatedAt");
	if (!json_is_string(updatedAt)) {
	    fprintf(stderr,
		    "error: record %ld updatedAt is not a string\n",
		    i + 1);
	    json_decref(root);
	    return -1;
	}
	printf
	    ("objectId:%s\tTemperature:%s\tHumidity:%s\tcreatedAt:%s\tupdatedAt%s\n",
	     json_string_value(objectId), json_string_value(temperature),
	     json_string_value(humidity), json_string_value(createdAt),
	     json_string_value(updatedAt));
    }
    json_decref(root);
    return 0;
}


//reference code - delete this if we don't need push service
void myPushCallback(ParseClient client, int error, const char *buffer)
{
    (void) client;
    if (error == 0 && buffer != NULL) {
	printf("received push: ':%s'\n", buffer);
    }
}
