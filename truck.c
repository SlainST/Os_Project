#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "truck.h"

void Truck_init(Truck* t){
    
    t->hasPassedToll = false;
    t->size=3;
    t->isCompleted=false;
    t->isOnFerry=false;
    t->isStartingSide=true;
    t->busyTime=(rand() % 100) + 201;
    t->timesWaited=0;
}