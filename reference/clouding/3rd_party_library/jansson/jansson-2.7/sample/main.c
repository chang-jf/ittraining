#include <string.h>
#include <jansson.h>

#define URL_FORMAT   "https://api.github.com/repos/%s/%s/commits"
#define URL_SIZE     256

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

int main(int argc, char *argv[])
{
    size_t i;
    char *text;
    char url[URL_SIZE];

    json_t *root;
    json_error_t error;

    if(argc != 3)
    {
        fprintf(stderr, "usage: %s USER REPOSITORY\n\n", argv[0]);
        fprintf(stderr, "List commits at USER's REPOSITORY.\n\n");
        return 2;
    }
    snprintf(url, URL_SIZE, URL_FORMAT, argv[1], argv[2]);
    
    text = request(url);
    if(!text)
        return 1;

    root = json_loads(text, 0, &error);
    free(text);

    if(!root)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }
    if(!json_is_array(root))
    {
        fprintf(stderr, "error: root is not an array\n");
        json_decref(root);
        return 1;
    }
    for(i = 0; i < json_array_size(root); i++)
    {
        json_t *data, *sha, *commit, *message;
        const char *message_text;

        data = json_array_get(root, i);
        if(!json_is_object(data))
        {
            fprintf(stderr, "error: commit data %d is not an object\n", i + 1);
            json_decref(root);
            return 1;
        }
        sha = json_object_get(data, "sha");
        if(!json_is_string(sha))
        {
            fprintf(stderr, "error: commit %d: sha is not a string\n", i + 1);
            json_decref(root);
            return 1;
        }

        commit = json_object_get(data, "commit");
        if(!json_is_object(commit))
        {
            fprintf(stderr, "error: commit %d: commit is not an object\n", i + 1);
            json_decref(root);
            return 1;
        }

        message = json_object_get(commit, "message");
        if(!json_is_string(message))
        {
            fprintf(stderr, "error: commit %d: message is not a string\n", i + 1);
            json_decref(root);
            return 1;
        }
        
        message_text = json_string_value(message);
        printf("%.8s %.*s\n", json_string_value(sha), newline_offset(message_text), message_text);
    }
    json_decref(root);
    return 0;
}
