#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "behind_across_square.h" 
#include <truck.h>
#include <car.h>
#include <minibus.h>


bool isAcrossAllEmpty = false;

void Behind_Across_Square_load(Car* cars[acrossCarsLength], Minibus* minibusses[acrossMinibusesLength], Truck* trucks[acrossTrucksLength]){
    
}

Car* Behind_Across_Square_Car_Left(Behind_Across_Square* self){
    if (!self) {
        return NULL;
    }
    for(int i=0; i < acrossCarsLength; i++){ 
        if(self->cars[i]!=NULL){
            isAcrossAllEmpty = false; 
            break;
        }
        else{
            isAcrossAllEmpty = true;
        }
    }
    
    int vehicle_choice = rand() % acrossCarsLength; 

    while(self->cars[vehicle_choice]==NULL && !isAcrossAllEmpty) { 
        vehicle_choice = rand() % acrossCarsLength;
    }
    return self->cars[vehicle_choice]; 
}

Minibus* Behind_Across_Square_Minibus_Left(Behind_Across_Square* self){
    if (!self) {
        return NULL;
    }
    for(int i=0; i < acrossMinibusesLength; i++){ 
        if(self->minibuses[i]!=NULL){
            isAcrossAllEmpty = false; 
            break;
        }
        else{
            isAcrossAllEmpty = true;
        }
    }
    
    int vehicle_choice = rand() % acrossMinibusesLength; 

    while(self->minibuses[vehicle_choice]==NULL && !isAcrossAllEmpty) { 
        vehicle_choice = rand() % acrossMinibusesLength;
    }
    return self->minibuses[vehicle_choice];
}

Truck* Behind_Across_Square_Truck_Left(Behind_Across_Square* self){
    if (!self) {
        return NULL;
    }
    for(int i=0; i < acrossTrucksLength; i++){ 
        if(self->trucks[i]!=NULL){
            isAcrossAllEmpty = false; 
            break;
        }
        else{
            isAcrossAllEmpty = true;
        }
    }

    int vehicle_choice = rand() % acrossTrucksLength; 

    while(self->trucks[vehicle_choice]==NULL && !isAcrossAllEmpty) { 
        vehicle_choice = rand() % acrossTrucksLength;
    }
    return self->trucks[vehicle_choice];
}