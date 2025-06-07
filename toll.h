#ifndef TOLL_H
#define TOLL_H

#include <behind_square.h>


#include <truck.h>
#include <car.h>
#include <minibus.h>
#include <square.h>


const int carsLength=1;
const int minibusesLength=1;
const int trucksLength=1;
struct Toll {
    Car* cars[40];
    Minibus* minibuses[20];
    Truck* trucks[12];

   
};
// Forward declaration (opaque pointer) - internal structure is hidden
typedef struct Toll Toll;


Toll* Toll_create_vehicle_arrays(); 
void Toll_destroy_vehicle_arrays(Toll* toll); //examples


void Toll_random_choose(Toll* toll_instance, Behind_Square* bs_instance, Square* square);
Car* Toll_car_return(Toll* toll);
Minibus* Toll_minibus_return(Toll* toll);
Truck* Toll_truck_return(Toll* toll);
#endif // Toll_H