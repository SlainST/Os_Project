
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


const int lengthOfCars=20;
const int lengthOfMinibuses=10;
const int lengthOfTrucks=6;

struct Ferry {
    int capacity;
    bool isWentToAcross;
    bool inFirstRound;
    int usedCapacity;
    int inWhichSquare;
    Car* cars[lengthOfCars];
    Truck* trucks[lengthOfTrucks];
    Minibus* minibusses[lengthOfMinibuses]; 
};

typedef struct Ferry Ferry;

void Ferry_init(Ferry* fe);

void Take_vehicles(Ferry* fe,Square square);

void Pass_vehicles(Ferry* fe, Square square1, Square square2, Behind_Square bs1, Behind_Square bs2);

#endif