/*#include <stdio.h>      [>printf()<]*/
/*#include <stdlib.h>     [>rand(), srand(), RAND_MAX<]*/
/*#include <time.h>       [>time(), clock()<]*/

/*int getTemperature();*/
/*int getHumidity();*/
#include "clouding_test.h"

int getTemperature(){
    srand(time(NULL));
    return rand()%20+20;    /*number generated from (0~19)+20=20~29*/
}
int getHumidity(){
    srand(time(NULL));
    return rand()%100;    /*number generated from 0~100*/
}
