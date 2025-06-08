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
    free(toll); //free aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
}




void wait_ms(long milisaniye) {
    clock_t baslangic_zamani = clock();

    // İstenen milisaniye süresine karşılık gelen clock tick sayısını hesapla
    // ve o zamana ulaşana kadar döngüde kal.
    while (clock() < baslangic_zamani + (milisaniye * CLOCKS_PER_SEC / 1000));
}











//void Toll_random_choose(Toll* self_toll, Behind_Square* bs, Square square) {
void Toll_random_choose(Toll* self_toll, Behind_Square* bs) {    
    if (!self_toll || !bs) {
        return;
    }

    int vehicle_type_choice = rand() % 3;

    if (vehicle_type_choice == 0) {
        Car* new_car = Behind_Square_Car_Left(bs);
        if (new_car != NULL) {
            int placed = 0;
            for (i = 0; i < carsLength; ++i) {
                if (self_toll->cars[i] == NULL) {
                    self_toll->cars[i] = new_car;
                    placed = 1;

                    wait_ms(self_toll->cars[i]->busyTime);
                   //hemen de kurtulmalı hemen olmazsa bile ardından

                    
                    Toll_car_return(self_toll);
                    break;


                }
            }
            if (!placed) {
            }
        }
    } else if (vehicle_type_choice == 1) {
        Minibus* new_minibus = Behind_Square_Minibus_Left(bs);
        if (new_minibus != NULL) {
            int placed = 0;
            for (i = 0; i < minibusesLength; ++i) {
                if (self_toll->minibuses[i] == NULL) {
                    self_toll->minibuses[i] = new_minibus;
                    placed = 1;
                    
                    wait_ms(self_toll->minibuses[i]->busyTime);
                    Toll_minibus_return(self_toll);
                    break;

                    
                }
            }
            if (!placed) {
            }
        }
    } else {
        Truck* new_truck = Behind_Square_Truck_Left(bs);
        if (new_truck != NULL) {
            int placed = 0;
            for (i = 0; i < trucksLength; ++i) {
                if (self_toll->trucks[i] == NULL) {
                    self_toll->trucks[i] = new_truck;
                    placed = 1;
                    
                    
                    wait_ms(self_toll->trucks[i]->busyTime);
                    Toll_truck_return(self_toll);
                    break;


                }
            }
            if (!placed) {
            }
        }
    }
}


Car* Toll_car_return(Toll* self_toll){
    carWillBeSended= self_toll->cars[i]; //hatalı kodlama değil çükü her return tolldan sonra çalışcak
                    
                    self_toll->cars[i]=NULL;
                    return carWillBeSended;


}

Minibus* Toll_minibus_return(Toll* self_toll){
    minibusWillBeSended= self_toll->minibuses[i];
                    
                    self_toll->minibuses[i]=NULL;
                    return minibusWillBeSended;

}

Truck* Toll_truck_return(Toll* self_toll){

    truckWillBeSended= self_toll->trucks[i];
                    
    self_toll->trucks[i]=NULL;
    return truckWillBeSended;
}