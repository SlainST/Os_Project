#ifndef TOLL_H
#define TOLL_H


struct Behind_Square;
struct Square;

#include "behind_square.h"


#include "truck.h"
#include "car.h"
#include "minibus.h"
#include "square.h"


struct Toll {
    Car* cars[40];
    Minibus* minibuses[20];
    Truck* trucks[12];

   
};

typedef struct Toll Toll;


Toll* Toll_create_vehicle_arrays(); 
void Toll_destroy_vehicle_arrays(Toll* toll); 
void wait_ms(long milisaniye);

void Toll_random_choose(Toll* toll_instance,struct Behind_Square* bs_instance);

Car* Toll_car_return(Toll* toll);
Minibus* Toll_minibus_return(Toll* toll);
Truck* Toll_truck_return(Toll* toll);
#endif 