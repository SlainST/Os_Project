#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>


#include "square.h"
#include <toll.h>

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

Car* Square_car_Left(Square* self, Ferry* ferry){ //tolldaki hatalı kodlama olurdu çünkü her left loaddan sonra değil

}

Minibus* Square_minibus_Left(Square* self, Ferry* ferry){

}

Truck* Square_truck_Left(Square* self, Ferry* ferry){

}