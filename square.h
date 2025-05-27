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
struct Square {
    Car* cars[40];
    Minibus* minibuses[20];
    Truck* trucks[12];

};

typedef struct Square Square;
    
void Square_load(Car* cars[40], Minibus* minibusses[20], Truck* trucks[12]);

void Square_Left(Car* cars[20], Minibus* minibusses[10], Truck* trucks[6]);

#endif 