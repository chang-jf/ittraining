#ifndef _CLOUDING_C
#define _CLOUDING_C
#include "clouding.h"
#include <stdio.h>

void myPushCallback(ParseClient client, int error, const char *buffer) {
  if (error == 0 && buffer != NULL) {
    printf("received push: '%s'\n", buffer);
  }
}
#endif // for #ifndef _CLOUDING_C
