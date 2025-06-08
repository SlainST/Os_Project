#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "minibus.h"

void Minibus_init(Minibus* m){
    
    m->hasPassedToll = false;
    m->size=2;
    m->isCompleted=false;
    m->isOnFerry=false;
    m->isStartingSide=true;
    m->busyTime=(rand() % 100) + 101;
    m->timesWaited=0;
    m->randomId=(rand() % 10000);
    m->start_side = 0;
    m->has_crossed_once = false;
  

    printf("minibus created: %d \n ",m->randomId);

}