#ifndef BEHIND_SQUARE_H
#define BEHIND_SQUARE_H 

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


int carsLength=40;
int minibusesLength=20;
int trucksLength=12;


struct Behind_Square {
    Car* cars[40];
    Minibus* minibuses[20];
    Truck* trucks[12];

};

typedef struct Behind_Square Behind_Square;
    
void Behind_Square_load(Car* cars[40], Minibus* minibusses[20], Truck* trucks[12]);

Car* Behind_Square_Car_Left(Behind_Square* self);

Minibus* Behind_Square_Minibus_Left( Behind_Square* self);

Truck* Behind_Square_Truck_Left(Behind_Square* self);

#endif 