#ifndef CAR_H
#define CAR_H 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

struct Car {
    bool hasPassedToll;
    int timesWaited;
    bool isOnFerry;
    int size ;
    int busyTime;
    bool isStartingSide;
    int start_side;         
    bool has_crossed_once;  
    bool isCompleted; 

    int randomId;     
    
};

typedef struct Car Car;
    
void Car_init(Car* c);

#endif 