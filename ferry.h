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

#include "minibus.h"
#include "car.h"
#include "truck.h"
#include "square.h"

#define MAX_CARS 20
#define MAX_MINIBUSES 10
#define MAX_TRUCKS 6

extern const int lengthOfCars;
extern const int lengthOfMinibuses;
extern const int lengthOfTrucks;

struct Ferry {
    int capacity;
    int usedCapacity;
    int inWhichSquare; // side
    Car* cars[20];
    Minibus* minibusses[10];
    Truck* trucks[6];

    int car_count;
    int minibus_count;
    int truck_count;
};

typedef struct Ferry Ferry;

void Ferry_init(Ferry* fe);
void Take_vehicles(Ferry* fe, struct Square* square0);
void Pass_vehicles(Ferry* fe, struct Behind_Square* bs2);

#endif