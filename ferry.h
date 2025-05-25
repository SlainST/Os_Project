
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
    int usedCapacity;
    Car* cars[20];
    Truck* trucks[6];
    Minibus* minibusses[10]; 
};

typedef struct Ferry Ferry;

void Ferry_init(Ferry* fe);

void Take_vehicles(Car* cars[20], Minibus* minibusses[], Truck* trucks[]);

void Pass_vehicles(Car* cars[20], Minibus* minibusses[], Truck* trucks[]);

#endif