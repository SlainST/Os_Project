#ifndef SQUARE_H
#define SQUARE_H 

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
#include <toll.h>
#include <ferry.h>
struct Square {
    Car* cars[40];
    Minibus* minibuses[20];
    Truck* trucks[12];

};

typedef struct Square Square;
    
void Square_load(Square* self, Toll* toll);

Car* Square_car_Left(Square* self, Ferry* ferry);


Minibus* Square_minibus_Left(Square* self, Ferry* ferry);


Truck* Square_truck_Left(Square* self, Ferry* ferry);

#endif 