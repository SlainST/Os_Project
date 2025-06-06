#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>


#include "truck.h"
#include "car.h"
#include "minibus.h"

#include "behind_square.h"


bool isAllEmpty=true;
Car* carWillBeSend;
Minibus* minibusWillBeSend;
Truck* truckWillBeSend;

Car* Behind_Square_Car_Left(Behind_Square* self){
    
    
    if (!self ) {
        return;
    }
    isAllEmpty=true;
    for(int i=0;i<carsLength;i++){
        if(self->cars[i]!=NULL){
            isAllEmpty=false;
            break;
        }
        else{    
        }
        if(i== carsLength-1  && isAllEmpty){
            return;
        }
    }
    int vehicle_type_choice = rand() % carsLength;

    while(self->cars[vehicle_type_choice]==NULL&& !isAllEmpty) {
        vehicle_type_choice = rand() % carsLength;
    }
    carWillBeSend=self->cars[vehicle_type_choice];
    self->cars[vehicle_type_choice]=NULL;
    return carWillBeSend; //mantık hatası var ayrılırken boşaltmam lazım orayı
    
}

Minibus* Behind_Square_Minibus_Left(Behind_Square* self){
    
    if (!self ) {
        return;
    }
    for(int i=0;i<minibusesLength;i++){
        if(self->minibuses[i]!=NULL){
            isAllEmpty=false;
            break;
        }
        else{
            
            
        }
        if(i== minibusesLength-1 && isAllEmpty){
            return;
        }
    }
    int vehicle_type_choice = rand() % minibusesLength;

    while(self->minibuses[vehicle_type_choice]==NULL&& !isAllEmpty) {
        vehicle_type_choice = rand() % minibusesLength;
    }
    minibusWillBeSend=self->minibuses[vehicle_type_choice];
    self->minibuses[vehicle_type_choice]=NULL;
    return minibusWillBeSend; //mantık hatası var ayrılırken boşaltmam lazım orayı
}

Truck* Behind_Square_Truck_Left(Behind_Square* self){

    if (!self ) {
        return;
    }
    for(int i=0;i<trucksLength;i++){
        if(self->trucks[i]!=NULL){
            isAllEmpty=false;
            break;
        }
        else{
            
            
        }
        if(i== trucksLength-1 && isAllEmpty){
            return;
        }
    }
    int vehicle_type_choice = rand() % trucksLength;

    while(self->trucks[vehicle_type_choice]==NULL&& !isAllEmpty) {
        vehicle_type_choice = rand() % trucksLength;
    }
    truckWillBeSend=self->trucks[vehicle_type_choice];
    self->trucks[vehicle_type_choice]=NULL;
    return truckWillBeSend; //mantık hatası var ayrılırken boşaltmam lazım orayı
}