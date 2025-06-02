#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

// #include "toll.h"

#include "minibus.h"
#include "car.h"
#include "truck.h"


int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv; 
    srand(time(NULL));

    // Toll* p1 = Toll_create(10, 20);
    // Toll* p2 = Toll_create(5, 15);

    // if (p1) {
    //     Toll_print(p1); // Output: Toll(10, 20)
    //     Toll_move(p1, 2, 3);
    //     //printf("Moved p1: (%d, %d)\n", Toll_getX(p1), Toll_getY(p1)); // Output: Moved p1: (12, 23)
    // }

    // if (p2) {
    //     Toll_print(p2); // Output: Toll(5, 15)
    // }

    // Toll_destroy(p1);
    // Toll_destroy(p2);

    int sizeOfCar = 12;
    int sizeOfMinibus = 10;
    int sizeOfTruck = 8;

    Car* cars[sizeOfCar];
    Minibus* minibuses[sizeOfMinibus];
    Truck* trucks[sizeOfTruck];

    Car c1;
    Car_init(&c1);

    Car c2;
    Car_init(&c2);

    Car c3;
    Car_init(&c3);

    Minibus m1;
    Minibus_init(&m1);

    Minibus m2;
    Minibus_init(&m2);

    Minibus m3;
    Minibus_init(&m3);

    Truck t1;
    Truck_init(&t1);

    Truck t2;
    Truck_init(&t2);

    Truck t3;
    Truck_init(&t3);

    cars[0] = &c1;
    cars[1] = &c2;
    cars[2] = &c3;

    minibuses[0] = &m1;
    minibuses[1] = &m2;
    minibuses[2] = &m3;

    trucks[0] = &t1;
    trucks[1] = &t2;
    trucks[2] = &t3;

    for(int i = 0; i < 3; i++){
        printf("%d. car: busyTime = %d\n", i, cars[i]->busyTime);
    }

    for(int i = 0; i < 3; i++){
        printf("%d. minibus: busyTime = %d\n", i, minibuses[i]->busyTime);
    }

    for(int i = 0; i < 3; i++){
        printf("%d. truck: busyTime = %d\n", i, trucks[i]->busyTime);
    }

    return 0;


}

