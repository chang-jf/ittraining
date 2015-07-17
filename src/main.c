#include "main.h"
#include <string.h>

int main() {
    json_t *obj, *t_obj;
    char * t_string;
    //initial payload
    /*INIT_PARSE_PAYLOAD(payload);*/
    //INIT_PARSE_PAYLOAD(t_payload);
    parse_payload payload;
    parse_payload t_payload;
    /*parse_payload payload={*/
        /*.objectId=0,*/
        /*.Temperature=0,*/
        /*.Humidity=0,*/
        /*.createdAt=0,*/
        /*.updatedAt=0*/
    /*};*/
    /*parse_payload t_payload={*/
        /*.objectId=0,*/
        /*.Temperature=0,*/
        /*.Humidity=0,*/
        /*.createdAt=0,*/
        /*.updatedAt=0*/
    /*};*/

    //set layload
    printf("1s\n");
    //strcpy(payload.objectId,    "12345"     );
    payload.objectId="12345";
    printf("11s\n");
    /*strcpy(payload.Temperature, "10"        );*/
    payload.Temperature="10";
    printf("12s\n");
    /*strcpy(payload.Humidity,    "20"        );*/
    payload.Humidity="20";
    printf("13s\n");
    /*strcpy(payload.createdAt,   "2015-05-05");*/
    payload.createdAt="2015-05-05";
    printf("14s\n");
    /*strcpy(payload.updatedAt,   "2015-06-06");*/
    payload.updatedAt="2015-06-06";
    printf("15s\n");
    //test payload to obj
    printf("2s\n");
    if( json_is_object( obj = payloadToJsonObj( payload ) ) ){
        printf("payload to obj ok\n");
    }else{
        printf("payload to obj fail\n");
    }
    //test obj to payload
    printf("3s\n");
    t_payload   =   jsonObjToPayload( obj );
    printf("objectId:%s\n",     t_payload.objectId);
    printf("31s\n");//exit(-1);
    printf("Temperature:%s\n",  t_payload.Temperature);
    printf("Humidity:%s\n", t_payload.Humidity);
    printf("createdAt:%s\n", t_payload.createdAt);
    printf("updatedAt:%s\n", t_payload.updatedAt);
    //test obj to jString
    printf("4s\n");
    printf("jstring:\n");
    t_string=jsonObjToJsonStr(obj);
    printf("%s\n", t_string);
    //test jString to obj
    //t_obj=jsonStrToJsonObj(t_string);
    printf("5s\n");
    //if( json_is_object(t_obj=jsonStrToJsonObj(t_string)) ){
    t_obj=jsonStrToJsonObj(t_string);
    if( json_is_object(t_obj)){
        printf("jstring to obj ok\n");
    }else{
        printf("jstring to obj fail\n");
    }
    printf("passed all test\n");
    //printf("payloadtoJsonStr:%s\n",payloadToJsonStr(payload));
    //parseSend(payload);
    //parseRecv(payload);
    return 0;
    ParseClient client = parseInitialize(APPLICATION_ID, CLIENT_KEY);
    printf("Initialized\n");
    parseSendRequest(client, "POST", PARSE_PATH, "{\"temperature\":\"10\", \"humidity\":\"20\"}", NULL);
    sleep(RATE_LIMIT);
    parseSendRequest(client, "GET", PARSE_PATH, NULL, mySendRequestCallback);
    printf("sent get request\n");
    return 0;
}

