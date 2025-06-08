
#ifndef FERRY_H
#define FERRY_H

struct Square;
struct Behind_Square;

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
#include "square.h"


const int lengthOfCars=20;
const int lengthOfMinibuses=10;
const int lengthOfTrucks=6;

struct Ferry {
    int capacity;
    bool isWentToAcross;
    bool inFirstRound;
    int usedCapacity;
    int inWhichSquare;
    Car* cars[40];
    Minibus* minibusses[20];
    Truck* trucks[12];
};

typedef struct Ferry Ferry;

void Ferry_init(Ferry* fe);

void Take_vehicles(Ferry* fe,struct  Square* square0);

void Pass_vehicles(Ferry* fe,struct Square* square1,struct Square* square2,struct Behind_Square* bs1,struct Behind_Square* bs2);

#endif