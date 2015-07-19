//prologue, description of purpose of the objects in the file, (optional) author, (optional) revision control. (optional) reference.
//sample code for demonstrate the use of clouding module API
//header file includes, system header files firse
//defines and typedefs in this order: constant macros->function macros->typedefs->enums
//global(external) data declarations in this order: externs->non-static globals->static globals
//function definition, groups by similar levels of abstraction, large numbers of essentially-independant utility functions->consider order by alphabetical order.
//0.    This program simulate an in-house which continually log environment data such as temperature and humidity onto IOT service, as well as display on 16X2 LED panel.
//0-1.  besides of push-talk temperature/humidity reporting, system also support automatic speakout while temperature reach configurable threshold value. 
//1.    fetch temperature/humidity from sensor
//          .pulling from sensor(V)
//          .interrupt trigger function accept value
//2-1.  send value to IOT clouding and retrive my last insert time #ensure we are respecting IOT'srate limit.
//2-2.  send value to LCD module.
//2-3.  send value to TTS, pipe sound binary to mpg123 library
//
#include "main.h"

int main()
{
    //initial payload and assign
    /*json_t *obj, *t_obj;*/
    /*char *t_string;*/
    //initial payload
    parse_payload *payload = payload_initiator();
    parse_payload *t_payload = payload_initiator();

    //set layload dummy FIXME: replace with code that fetch value from sensor
    strcpy(payload->Temperature, int2str(getTemperature())); 
    strcpy(payload->Humidity,    int2str(getHumidity())); 

    printf("==Getting Temperature&Humidity======================\n");
    payload_printer(payload);

    //test payload to obj
    /*if (json_is_object(obj = payloadToJsonObj(payload))) {*/
	/*printf("payload to obj ok\n");*/
    /*} else {*/
	/*printf("payload to obj fail\n");*/
    /*}*/
    /*printf("====================================================\n");*/

    //test obj to payload
    /*t_payload = jsonObjToPayload(obj);*/
    /*payload_printer(t_payload);*/
    /*printf("==object to payload ok==============================\n");*/

    //test obj to jString
    /*printf("jstring:\n");*/
    /*t_string = jsonObjToJsonStr(obj);*/
    /*printf("%s\n", t_string);*/
    printf("==Converting to JSON================================\n");
    printf("%s\n",payloadToJsonStr(payload));

    //test jString to obj
    /*t_obj = jsonStrToJsonObj(t_string);*/
    /*if (json_is_object(t_obj)) {*/
	/*printf("jstring to obj ok\n");*/
    /*} else {*/
	/*printf("jstring to obj fail\n");*/
    /*}*/
    /*printf("====================================================\n");*/
    /*printf("passed all test\n");*/
    parseSend(payload);

    /*ParseClient client = parseInitialize(APPLICATION_ID, CLIENT_KEY);*/
    /*printf("Initialized\n");*/
    /*parseSendRequest(client, "POST", PARSE_PATH,*/
		     /*"{\"temperature\":\"10\", \"humidity\":\"20\"}",*/
		     /*NULL);*/
    /*sleep(RATE_LIMIT);*/
    /*parseSendRequest(client, "GET", PARSE_PATH, NULL,*/
		     /*mySendRequestCallback);*/
    /*printf("sent get request\n");*/
    payload_destroyer(payload);
    payload_destroyer(t_payload);
    return 0;
}
