#ifndef TRUCK_H
#define TRUCK_H 


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

struct Truck{
    bool hasPassedToll;
    bool isOnFerry;
    int size;
    int busyTime;
    bool isStartingSide;
    int start_side;         
    bool has_crossed_once;  
    bool isCompleted;  
    int timesWaited;
    int randomId;
};

typedef struct Truck Truck;

void Truck_init(Truck* t);
    
#endif 