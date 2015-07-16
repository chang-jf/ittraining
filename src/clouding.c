#ifndef _CLOUDING_C
#define _CLOUDING_C
#include "clouding.h"
#include <stdio.h>
#include <jansson.h>
#include <string.h>

char * extract_string(char *str){
    int len=0;
    char *newstr=str;
    if ((len=strlen(str))<2) {
        return -1;
    }else{
        newstr+=11;         //remove {"results": from responsebody
        newstr[strlen(newstr)-2]=0;
    }
    printf("length:%d\nstring:%s\n", strlen(str),str);
    printf("length:%d\nnewstr:%s\n", strlen(newstr),newstr);
   return newstr; 
}
void myPushCallback(ParseClient client, int error, const char *buffer) {
    if (error == 0 && buffer != NULL) {
        printf("received push: ':%s'\n", buffer);
    }
}

/* Return the offset of the first newline in text or the length of
   text if there's no newline */
static int newline_offset(const char *text)
{
    const char *newline = strchr(text, '\n');
    if(!newline)
        return strlen(text);
    else
        return (int)(newline - text);
}
int handleJson(char *Json)
{
    size_t i;
    char *tmp;
    json_t *root;
    json_error_t err;
    if((tmp = extract_string(Json))==-1){
        perror(extract_string);
        return -1;
    }
    root=json_loads(tmp, 0, &err);
    if(!root){
        fprintf(stderr, "error: on line %d: %s\n", err.line, err.text);
        return -1;
    }
    if(!json_is_array(root))
    {
        fprintf(stderr, "error: root is not an array\n");
        json_decref(root);
        return -1;
    }
    for (i = 0; i < json_array_size(root); ++i) {
        json_t *data, *objectId, *temperature, *humidity, *createdAt, *updatedAt;
        
        //data = json_array_get(Json, i);
        data = json_array_get(root, i);
        if (!json_is_object(data)) {
            fprintf(stderr, "error: commit data %d is not an object\n", i + 1);
            json_decref(root);
            return -1;
        }
        objectId = json_object_get(data, "objectId");
        if (!json_is_string(objectId)) {
            fprintf(stderr, "error: record %d objectId is not a string\n", i+1);
            json_decref(root);
            return -1;
        }
        temperature = json_object_get(data, "temperature");
        if (!json_is_string(temperature)) {
            fprintf(stderr, "error: record %d temperature is not a string\n", i+1);
            json_decref(root);
            return -1;
        }
        humidity = json_object_get(data, "humidity");
        if (!json_is_string(humidity)) {
            fprintf(stderr, "error: record %d humidity is not a string\n", i+1);
            json_decref(root);
            return -1;
        }
        createdAt = json_object_get(data, "createdAt");
        if (!json_is_string(createdAt)) {
            fprintf(stderr, "error: record %d createdAt is not a string\n", i+1);
            json_decref(root);
            return -1;
        }
        updatedAt = json_object_get(data, "updatedAt");
        if (!json_is_string(updatedAt)) {
            fprintf(stderr,"error: record %d updatedAt is not a string\n", i+1);
            json_decref(root);
            return -1;
        }
        printf("objectId:%s\tTemperature:%s\tHumidity:%s\tcreatedAt:%s\tupdatedAt%s\n", json_string_value(objectId), json_string_value(temperature), json_string_value(humidity), json_string_value(createdAt), json_string_value(updatedAt));
    }
    json_decref(root);
    return 0;
}

void mySendRequestCallback(ParseClient client, int error, int httpStatus, const char *httpResponseBody){

    printf("I get call backed\n");
    if (error == 0 && httpResponseBody != NULL) {
        printf("Sending request success\n");
        printf("error=%d\n", error);
        printf("httpStatus=%d\n", httpStatus);
        printf("httpResponseBody:\n%s\n", httpResponseBody);
        printf("======================================\n");
        handleJson(httpResponseBody);

    }else{
        printf("Sending request error\n");
        printf("error=%d\n", error);
        printf("httpStatus=%d\n", httpStatus);
        printf("httpResponseBody:\n%s\n", httpResponseBody);
    }
}

#endif // for #ifndef _CLOUDING_C
