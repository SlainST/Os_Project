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
    bool isCompleted;
    int timesWaited;
};

typedef struct Truck Truck;

void Truck_init(Truck* t);
    
#endif 