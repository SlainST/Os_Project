#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

#include "car.h"
#include "minibus.h"
#include "truck.h"

#include "ferry.h"
#include "square.h"
#include "behind_square.h"

void Ferry_init(Ferry* fe) {
    fe->capacity = 20;
    fe->usedCapacity = 0;
    fe->inWhichSquare = 0; // Feribot başlangıçta 0. yakada

    fe->car_count = 0;
    fe->minibus_count = 0;
    fe->truck_count = 0;
    
    for(int i = 0; i < 20; i++) fe->cars[i] = NULL;
    for(int i = 0; i < 10; i++) fe->minibusses[i] = NULL;
    for(int i = 0; i < 6; i++) fe->trucks[i] = NULL;
}

void wait_mses(long milisaniye) {
    clock_t baslangic_zamani = clock();
    while (clock() < baslangic_zamani + (milisaniye * CLOCKS_PER_SEC / 1000));
}

void Take_vehicles(Ferry* fe, Square* square) {
    if (!fe || !square) return;
    
    wait_mses(300); // Fonksiyon başında 300ms bekleme

    int attempts_without_load = 0;
    while (fe->usedCapacity < fe->capacity) {
        // Döngüden çıkma koşulunu daha toleranslı hale getirdik.
        if (attempts_without_load > 10) { 
             break;
        }

        int choice = rand() % 3;
        bool loaded_this_try = false;

        if (choice == 0 && fe->usedCapacity + 1 <= fe->capacity) {
            Car* car = Square_car_Left(square);
            if (car) {
                fe->cars[fe->car_count++] = car;
                fe->usedCapacity += 1;
                loaded_this_try = true;
            }
        } else if (choice == 1 && fe->usedCapacity + 2 <= fe->capacity) {
            Minibus* minibus = Square_minibus_Left(square);
            if (minibus) {
                fe->minibusses[fe->minibus_count++] = minibus;
                fe->usedCapacity += 2;
                loaded_this_try = true;
            }
        } else if (choice == 2 && fe->usedCapacity + 3 <= fe->capacity) {
            Truck* truck = Square_truck_Left(square);
            if (truck) {
                fe->trucks[fe->truck_count++] = truck;
                fe->usedCapacity += 3;
                loaded_this_try = true;
            }
        }

        if (loaded_this_try) {
            printf("Loaded a vehicle. Ferry capacity: %d/%d\n", fe->usedCapacity, fe->capacity);
            attempts_without_load = 0; // Başarılı yüklemede sayacı sıfırla
            wait_mses(100); // Yükleme sonrası kısa bir bekleme
        } else {
            attempts_without_load++; // Başarısız denemeyi artır
        }
    }
}

void Pass_vehicles(Ferry* fe, Behind_Square* bs) {
    if (!fe || !bs) return;

    int current_side = fe->inWhichSquare;

    for (int i = 0; i < fe->car_count; i++) {
        Car* car = fe->cars[i];
        if (car->start_side != current_side) {
            car->has_crossed_once = true;
            for (int j = 0; j < carsLength; j++) {
                if (bs->cars[j] == NULL) {
                    bs->cars[j] = car;
                    break;
                }
            }
        } else if (car->has_crossed_once) {
            car->isCompleted = true;
            printf("Car %d completed round trip and is removed!\n", car->randomId);
            free(car);
        }
    }

    for (int i = 0; i < fe->minibus_count; i++) {
        Minibus* minibus = fe->minibusses[i];
        if (minibus->start_side != current_side) {
            minibus->has_crossed_once = true;
            for (int j = 0; j < minibusesLength; j++) {
                if (bs->minibuses[j] == NULL) {
                    bs->minibuses[j] = minibus;
                    break;
                }
            }
        } else if (minibus->has_crossed_once) {
            minibus->isCompleted = true;
             printf("Minibus %d completed round trip and is removed!\n", minibus->randomId);
             free(minibus);
        }
    }
    
    for (int i = 0; i < fe->truck_count; i++) {
        Truck* truck = fe->trucks[i];
        if (truck->start_side != current_side) {
            truck->has_crossed_once = true;
            for (int j = 0; j < trucksLength; j++) {
                if (bs->trucks[j] == NULL) {
                    bs->trucks[j] = truck;
                    break;
                }
            }
        } else if (truck->has_crossed_once) {
            truck->isCompleted = true;
            printf("Truck %d completed round trip and is removed!\n", truck->randomId);
            free(truck);
        }
    }

    fe->usedCapacity = 0;
    fe->car_count = 0;
    fe->minibus_count = 0;
    fe->truck_count = 0;
    memset(fe->cars, 0, sizeof(fe->cars));
    memset(fe->minibusses, 0, sizeof(fe->minibusses));
    memset(fe->trucks, 0, sizeof(fe->trucks));
}