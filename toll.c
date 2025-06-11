#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>


#include "toll.h"
#include "car.h"
#include "minibus.h"
#include "truck.h"

#include "behind_square.h"

Car* carWillBeSended;
Minibus* minibusWillBeSended;
Truck* truckWillBeSended;
int i;

void Toll_destroy_vehicle_arrays(Toll* toll) {
    free(toll);
}

void wait_ms(long milisaniye) {
    if (milisaniye <= 0) return;
    clock_t baslangic_zamani = clock();
    while (clock() < baslangic_zamani + (milisaniye * CLOCKS_PER_SEC / 1000));
}

void Toll_random_choose(Toll* self_toll, Behind_Square* bs) {    
    if (!self_toll || !bs) {
        return;
    }

    for(int attempts = 0; attempts < 5; attempts++) {
        int vehicle_type_choice = rand() % 3;

        if (vehicle_type_choice == 0) {
            Car* new_car = Behind_Square_Car_Left(bs);
            if (new_car != NULL) {
                for (i = 0; i < carsLength; ++i) {
                    if (self_toll->cars[i] == NULL) {
                        self_toll->cars[i] = new_car;
                        printf("Car %d entering toll, processing for %d ms.\n", new_car->randomId, new_car->busyTime);
                        wait_ms(new_car->busyTime);
                        return;
                    }
                }
            }
        } else if (vehicle_type_choice == 1) {
            Minibus* new_minibus = Behind_Square_Minibus_Left(bs);
            if (new_minibus != NULL) {
                for (i = 0; i < minibusesLength; ++i) {
                    if (self_toll->minibuses[i] == NULL) {
                        self_toll->minibuses[i] = new_minibus;
                        printf("Minibus %d entering toll, processing for %d ms.\n", new_minibus->randomId, new_minibus->busyTime);
                        wait_ms(new_minibus->busyTime);
                        return;
                    }
                }
            }
        } else {
            Truck* new_truck = Behind_Square_Truck_Left(bs);
            if (new_truck != NULL) {
                for (i = 0; i < trucksLength; ++i) {
                    if (self_toll->trucks[i] == NULL) {
                        self_toll->trucks[i] = new_truck;
                        printf("Truck %d entering toll, processing for %d ms.\n", new_truck->randomId, new_truck->busyTime);
                        wait_ms(new_truck->busyTime);
                        return;
                    }
                }
            }
        }
    }
}


Car* Toll_car_return(Toll* self_toll){
    if (!self_toll) return NULL;

    for (int i = 0; i < carsLength; ++i) { 
        if (self_toll->cars[i] != NULL) {
            carWillBeSended = self_toll->cars[i]; 
            self_toll->cars[i] = NULL; 
            printf("Car: %d passed from toll.\n",carWillBeSended->randomId);
            return carWillBeSended;
        }
    }
    return NULL; 
}

Truck* Toll_truck_return(Toll* self_toll){
    if (!self_toll) return NULL;

    for (int i = 0; i < trucksLength; ++i) { 
        if (self_toll->trucks[i] != NULL) {
            truckWillBeSended = self_toll->trucks[i]; 
            self_toll->trucks[i] = NULL; 
            printf("Truck: %d passed from toll.\n",truckWillBeSended->randomId);
            return truckWillBeSended;
        }
    }
    return NULL; 
}


Minibus* Toll_minibus_return(Toll* self_toll){
    if (!self_toll) return NULL;

    for (int i = 0; i < minibusesLength; ++i) { 
        if (self_toll->minibuses[i] != NULL) {
            minibusWillBeSended = self_toll->minibuses[i]; 
            self_toll->minibuses[i] = NULL;
            printf("Minibus: %d passed from toll.\n",minibusWillBeSended->randomId); 
            return minibusWillBeSended;
        }
    }
    return NULL; 
}