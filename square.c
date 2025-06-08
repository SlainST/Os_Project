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

#include "square.h"
#include "toll.h"

Car* carWillBeSend;
Minibus* minibusWillBeSend;
Truck* truckWillBeSend;

bool isAllEmpty=false;
// void Square_load_ferry(Square* self, Toll* toll){
    
// }



void Square_load(Square* self, Toll* toll){
    if ( self || !toll) {
        return;
    }

    int vehicle_type_choice = rand() % 3;

    if (vehicle_type_choice == 0) {
        Car* new_car = Toll_car_return(toll);
        if (new_car != NULL) {
            int placed = 0;
            for (int i = 0; i < carsLength; ++i) {
                if  (self->cars[i] == NULL) {
                 self->cars[i] = new_car;
                    placed = 1;


                   break;




                }
            }
            if (!placed) {
            }
        }
    } else if (vehicle_type_choice == 1) {
        Minibus* new_minibus = Toll_minibus_return(toll);
        if (new_minibus != NULL) {
            int placed = 0;
            for (int i = 0; i < minibusesLength; ++i) {
                if  (self->minibuses[i] == NULL) {
                 self->minibuses[i] = new_minibus;
                    placed = 1;
                    
                    


                    break;
                }
            }
            if (!placed) {
            }
        }
    } else {
        Truck* new_truck = Toll_truck_return(toll);
        if (new_truck != NULL) {
            int placed = 0;
            for (int i = 0; i < trucksLength; ++i) {
                if  (self->trucks[i] == NULL) {
                 self->trucks[i] = new_truck;
                    placed = 1;
                    
                    



                    break;
                }
            }
            if (!placed) {
            }
        }
    }


}






Car* Square_car_Left(Square* self){ //tolldaki hatalı kodlama olurdu çünkü her left loaddan sonra değil
//ferry gerekli mi burda

    if (!self ) {
        return NULL;
    }
    for(int i=0;i<carsLength;i++){
        if(self->cars[i]!=NULL){
            isAllEmpty=false;
            break;
        }
        else{
            isAllEmpty=true;
            
        }
        if(i == carsLength-1){ return NULL; }
    }

    int vehicle_type_choice = rand() % carsLength;//hataaaaaaaaaaaaaaaaaaaaaaaa

    while(self->cars[vehicle_type_choice]==NULL&& !isAllEmpty) {
        vehicle_type_choice = rand() % carsLength;
    }
    carWillBeSend=self->cars[vehicle_type_choice];
    self->cars[vehicle_type_choice]=NULL;
    return carWillBeSend;


}

Minibus* Square_minibus_Left(Square* self){
    if (!self ) {
        return NULL;
    }
    for(int i=0;i<minibusesLength;i++){
        if(self->minibuses[i]!=NULL){
            isAllEmpty=false;
            break;
        }
        else{
            isAllEmpty=true;
            
        }
        if(i== minibusesLength-1){
            return NULL;
        }
    }

    int vehicle_type_choice = rand() % minibusesLength;

    while(self->minibuses[vehicle_type_choice]==NULL&& !isAllEmpty) {
        vehicle_type_choice = rand() % minibusesLength;
    }
    minibusWillBeSend=self->minibuses[vehicle_type_choice];
    self->minibuses[vehicle_type_choice]=NULL;
    return minibusWillBeSend;


}
Truck* Square_truck_Left(Square* self){
    if (!self ) {
        return NULL;
    }
    for(int i=0;i<trucksLength;i++){
        if(self->trucks[i]!=NULL){
            isAllEmpty=false;
            break;
        }
        else{
            isAllEmpty=true;
            
        }
        if(i== trucksLength-1){
            return NULL;
        }
    }

    int vehicle_type_choice = rand() % trucksLength;

    while(self->trucks[vehicle_type_choice]==NULL&& !isAllEmpty) {
        vehicle_type_choice = rand() % trucksLength;
    }
    truckWillBeSend=self->trucks[vehicle_type_choice];
    self->trucks[vehicle_type_choice]=NULL;
    return truckWillBeSend;


}