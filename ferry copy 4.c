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
    fe->inWhichSquare = 0;

    fe->car_count = 0;
    fe->minibus_count = 0;
    fe->truck_count = 0;
    
    memset(fe->cars, 0, sizeof(fe->cars));
    memset(fe->minibusses, 0, sizeof(fe->minibusses));
    memset(fe->trucks, 0, sizeof(fe->trucks));
}

void wait_mses(long milisaniye) {
    clock_t baslangic_zamani = clock();
    while (clock() < baslangic_zamani + (milisaniye * CLOCKS_PER_SEC / 1000));
}

void Take_vehicles(Ferry* fe, Square* square) {
    if (!fe || !square) return;

    wait_mses(300); // İsteğin üzerine yükleme başlangıcında bekleme

    while (fe->usedCapacity < fe->capacity) {
        bool loaded_in_this_pass = false;

        // Rastgeleliği korumak için araç türlerini her seferinde karıştır
        int vehicle_types[] = {0, 1, 2}; // 0: Araba, 1: Minibüs, 2: Kamyon
        for (int i = 0; i < 3; ++i) {
            int j = i + rand() / (RAND_MAX / (3 - i) + 1);
            int temp = vehicle_types[j];
            vehicle_types[j] = vehicle_types[i];
            vehicle_types[i] = temp;
        }

        // Karıştırılmış sırayla TÜM araç türlerini deniyoruz
        for (int i = 0; i < 3; ++i) {
            int choice = vehicle_types[i];

            if (choice == 0 && fe->usedCapacity + 1 <= fe->capacity) {
                Car* car = Square_car_Left(square);
                if (car) {
                    fe->cars[fe->car_count++] = car;
                    fe->usedCapacity += 1;
                    loaded_in_this_pass = true;
                    printf("Loaded a vehicle. Ferry capacity: %d/%d\n", fe->usedCapacity, fe->capacity);
                }
            } else if (choice == 1 && fe->usedCapacity + 2 <= fe->capacity) {
                Minibus* minibus = Square_minibus_Left(square);
                if (minibus) {
                    fe->minibusses[fe->minibus_count++] = minibus;
                    fe->usedCapacity += 2;
                    loaded_in_this_pass = true;
                    printf("Loaded a vehicle. Ferry capacity: %d/%d\n", fe->usedCapacity, fe->capacity);
                }
            } else if (choice == 2 && fe->usedCapacity + 3 <= fe->capacity) {
                Truck* truck = Square_truck_Left(square);
                if (truck) {
                    fe->trucks[fe->truck_count++] = truck;
                    fe->usedCapacity += 3;
                    loaded_in_this_pass = true;
                    printf("Loaded a vehicle. Ferry capacity: %d/%d\n", fe->usedCapacity, fe->capacity);
                }
            }
        }

        // Eğer tam bir deneme turunda (3 araç türü de denendiğinde)
        // hiç araç yüklenemediyse, demek ki ya meydan boş ya da kalanlar sığmıyor.
        // Bu durumda yüklemeyi bitir.
        if (!loaded_in_this_pass) {
            break;
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

    // Feribotu sıfırla
    fe->usedCapacity = 0;
    fe->car_count = 0;
    fe->minibus_count = 0;
    fe->truck_count = 0;
    memset(fe->cars, 0, sizeof(fe->cars));
    memset(fe->minibusses, 0, sizeof(fe->minibusses));
    memset(fe->trucks, 0, sizeof(fe->trucks));
}