
#ifndef FERRY_H
#define FERRY_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

// #include "toll.h"

#include "minibus.h"
#include "car.h"
#include "truck.h"


struct Ferry {
    int capacity;
    bool isWentToAcross;
    bool inFirstRound;
    int usedCapacity;
    int inWhichSquare;
    Car* cars[20];
    Truck* trucks[6];
    Minibus* minibusses[10]; 
};

typedef struct Ferry Ferry;

void Ferry_init(Ferry* fe);

void Take_vehicles(Ferry* fe,Square square);

void Pass_vehicles(Ferry* fe,Car* cars[20], Minibus* minibusses[10], Truck* trucks[6]);

#endif