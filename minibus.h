#ifndef MINIBUS_H
#define MINIBUS_H 



#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>



struct Minibus{
    bool hasPassedToll;
    bool isOnFerry;
    int size;
    int timesWaited;
    int busyTime;
    bool isStartingSide;
    int start_side;         
    bool has_crossed_once;  
    bool isCompleted;  
    int randomId;


};

typedef struct Minibus Minibus;

void Minibus_init(Minibus* m);
    
#endif 