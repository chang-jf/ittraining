#include <jansson.h>
#include <stdio.h>

int main()
{
    typedef struct
    { 
        int id;
        const char *message;
        double prices[3];
    } example_t;
    
    unsigned long int i;
    json_t *obj = json_object(), *arr = json_array();
    example_t ex = {143296, "boo", {12.47, 34.95, 192.02}};
    
    json_object_set_new(obj, "id", json_integer(ex.id));
    json_object_set_new(obj, "message", json_string(ex.message));
    
    for(i=0; i < sizeof(ex.prices)/sizeof(ex.prices[0]); i++)
    //json_array_set_new(arr, i, json_real(ex.prices[i]));
    //json_array_insert_new(arr, i, json_real(ex.prices[i]));
    json_array_append_new(arr, json_real(ex.prices[i]));
    
    json_object_set_new(obj, "prices", arr);
    
    // convert to a json string
    char *str = json_dumps(obj, 0);  
    printf("string:\n%s", str);
    json_decref(obj); 
    
    // convert str back into a json_t object
    json_error_t err = {0}; 
    obj = json_loads(str, 0, &err);
    printf("obj:\n%s", obj);
    free(str); 
    
    return 0;
}
