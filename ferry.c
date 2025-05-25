#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include <car.h>
#include <minibus.h>
#include <truck.h>

#include <ferry.h>


void Ferry_init(Ferry* fe){

    fe -> capacity=20;
    fe ->usedCapacity=0;
    fe-> isWentToAcross=false;
}

void Take_vehicles(Car* cars[20], Minibus* minibusses[], Truck* trucks[]){


}

void Pass_vehicles(Car* cars[20], Minibus* minibusses[], Truck* trucks[]){

    
}

