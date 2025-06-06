#ifndef TOLL_H
#define TOLL_H


struct Behind_Square;
struct Square;

#include "behind_square.h"


#include "truck.h"
#include "car.h"
#include "minibus.h"
#include "square.h"


const int carsLengthh=1;
const int minibusesLengthh=1;
const int trucksLengthh=1;
struct Toll {
    Car* cars[40];
    Minibus* minibuses[20];
    Truck* trucks[12];

   
};
// Forward declaration (opaque pointer) - internal structure is hidden
typedef struct Toll Toll;


Toll* Toll_create_vehicle_arrays(); 
void Toll_destroy_vehicle_arrays(Toll* toll); //examples


void Toll_random_choose(Toll* toll_instance,struct Behind_Square* bs_instance, struct Square* square);
Car* Toll_car_return(Toll* toll);
Minibus* Toll_minibus_return(Toll* toll);
Truck* Toll_truck_return(Toll* toll);
#endif // Toll_H