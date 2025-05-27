#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "car.h"

void Car_init(Car* c){
    
    c->hasPassedToll = false;
    c->size=1;
    c->isCompleted=false;
    c->isOnFerry=false;
    c->isStartingSide=true;
    c->busyTime=(rand() % 100) + 1;
    c->timesWaited=0;
    

}