#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

// #include "toll.h"

typedef struct{
    bool hasPassedToll;
    bool isOnFerry;
    int size;
    int busyTime;
    bool isStartingSide;
    bool isCompleted;
}Car;

typedef struct{
    bool hasPassedToll;
    bool isOnFerry;
    int size;
    int busyTime;
    bool isStartingSide;
    bool isCompleted;
}Minibus;

typedef struct{
    bool hasPassedToll;
    bool isOnFerry;
    int size;
    int busyTime;
    bool isStartingSide;
    bool isCompleted;
}Truck;

int main(int argc, char const *argv[])
{
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

    Car cars[sizeOfCar];
    Minibus minibuses[sizeOfMinibus];
    Truck trucks[sizeOfTruck];

    Car c1;
    c1.hasPassedToll = false;
    c1.isOnFerry = false;
    c1.size = 1;
    c1.busyTime = (rand() % 100) + 1;
    c1.isStartingSide = true;
    c1.isCompleted = false;

    Car c2;
    c2.hasPassedToll = false;
    c2.isOnFerry = false;
    c2.size = 1;
    c2.busyTime = (rand() % 100) + 1;
    c2.isStartingSide = true;
    c2.isCompleted = false;

    Car c3;
    c3.hasPassedToll = false;
    c3.isOnFerry = false;
    c3.size = 1;
    c3.busyTime = (rand() % 100) + 1;
    c3.isStartingSide = true;
    c3.isCompleted = false;

    Minibus m1;
    m1.hasPassedToll = false;
    m1.isOnFerry = false;
    m1.size = 2;
    m1.busyTime = (rand() % 100) + 1;
    m1.isStartingSide = true;
    m1.isCompleted = false;

    Minibus m2;
    m2.hasPassedToll = false;
    m2.isOnFerry = false;
    m2.size = 2;
    m2.busyTime = (rand() % 100) + 1;
    m2.isStartingSide = true;
    m2.isCompleted = false;

    Minibus m3;
    m3.hasPassedToll = false;
    m3.isOnFerry = false;
    m3.size = 2;
    m3.busyTime = (rand() % 100) + 1;
    m3.isStartingSide = true;
    m3.isCompleted = false;

    Truck t1;
    t1.hasPassedToll = false;
    t1.isOnFerry = false;
    t1.size = 3;
    t1.busyTime = (rand() % 100) + 1;
    t1.isStartingSide = true;
    t1.isCompleted = false;

    Truck t2;
    t2.hasPassedToll = false;
    t2.isOnFerry = false;
    t2.size = 3;
    t2.busyTime = (rand() % 100) + 1;
    t2.isStartingSide = true;
    t2.isCompleted = false;

    Truck t3;
    t3.hasPassedToll = false;
    t3.isOnFerry = false;
    t3.size = 3;
    t3.busyTime = (rand() % 100) + 1;
    t3.isStartingSide = true;
    t3.isCompleted = false;

    cars[0] = c1;
    cars[1] = c2;
    cars[2] = c3;

    minibuses[0] = m1;
    minibuses[1] = m2;
    minibuses[2] = m3;

    trucks[0] = t1;
    trucks[1] = t2;
    trucks[2] = t3;

    for(int i = 0; i < 3; i++){
        printf("%d. car: busyTime = %d\n", i, cars[i].busyTime);
    }

    return 0;


}

