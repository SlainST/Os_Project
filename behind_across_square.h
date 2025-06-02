#ifndef BEHIND_ACROSS_SQUARE_H
#define BEHIND_ACROSS_SQUARE_H 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include <truck.h>
#include <car.h>
#include <minibus.h>

const int acrossCarsLength = 40;       
const int acrossMinibusesLength = 20;  
const int acrossTrucksLength = 12;     

struct Behind_Across_Square {
    Car* cars[acrossCarsLength]; 
    Minibus* minibuses[acrossMinibusesLength]; 
    Truck* trucks[acrossTrucksLength]; 
};

typedef struct Behind_Across_Square Behind_Across_Square;
    

void Behind_Across_Square_load(Car* cars[acrossCarsLength], Minibus* minibusses[acrossMinibusesLength], Truck* trucks[acrossTrucksLength]);

Car* Behind_Across_Square_Car_Left(Behind_Across_Square* self);

Minibus* Behind_Across_Square_Minibus_Left(Behind_Across_Square* self);

Truck* Behind_Across_Square_Truck_Left(Behind_Across_Square* self);

#endif