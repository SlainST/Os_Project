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


bool isAllEmpty=true;

void Ferry_init(Ferry* fe) {
    fe->capacity = 20;
    fe->usedCapacity = 0;
    fe->isWentToAcross = false; // Feribotun yönünü belirtir
    fe->inWhichSquare = 0;

    fe->car_count = 0;
    fe->minibus_count = 0;
    fe->truck_count = 0;
    
    for(int i = 0; i < 40; i++) fe->cars[i] = NULL;
    for(int i = 0; i < 20; i++) fe->minibusses[i] = NULL;
    for(int i = 0; i < 12; i++) fe->trucks[i] = NULL;
}

void wait_mses(long milisaniye) {
    clock_t baslangic_zamani = clock();

    // İstenen milisaniye süresine karşılık gelen clock tick sayısını hesapla
    // ve o zamana ulaşana kadar döngüde kal.
    while (clock() < baslangic_zamani + (milisaniye * CLOCKS_PER_SEC / 1000));
}



// void Take_vehicles(Ferry* fe, Square* square){
//     if (!fe || !square ) return;
//     printf("Ferry loading from current square...\n");
    
//     wait_mses(300); //almaya başlamadan önce 300 ms kalmasını istiyorum.

//     while (fe->usedCapacity<=fe->capacity){
//         int choice=rand()%3;  //rastgelelik şart projede!
//         bool vehicle_loaded = false;
//         if(choice==0 && fe->usedCapacity + 1 <= fe->capacity){
//             //skip if 
//             isAllEmpty=true;
//             for(int i=0; i<CARS_LENGTH;i++){
//                 if(square->cars[i]!=NULL){
//                     isAllEmpty=false;
//                     break;
//                 }
//                 else{
                    
//                 }
                
//                 //wait 300ms for after
//             }
//             if(isAllEmpty==true){
//                 if(fe->isWentToAcross==true){
//                     fe->isWentToAcross=false;
//                 }

//                 if(fe->isWentToAcross==false){
//                     fe->isWentToAcross=true;
//                 }
//             }
//             else{
                
//                 if(fe->capacity<fe->usedCapacity+1){
//                     break;
//                 }
                
                
//                 Car* car = Square_car_Left(square);
//                 //count car ekleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//                 if (car) {
//                     fe->cars[fe->usedCapacity] = car; // DİKKAT: index olarak usedCapacity kullanılıyor
//                     fe->usedCapacity += 1;
//                     vehicle_loaded = true;
//                 }

//                 fe->usedCapacity=fe->usedCapacity+1;
                
//                 if(fe->capacity<fe->usedCapacity+1){
//                     break;
//                 }
                
//             }
            
            
//         }
//         if (choice == 1) {
//             isAllEmpty=true;
//             for(int i=0; i<MINIBUSES_LENGTH;i++){
//                 if(square->minibuses[i]!=NULL){
//                     isAllEmpty=false;
//                     break;
//                 }
//                 else{
                    
//                 }
                
//                 //wait 300ms for after
//             }
//             if(isAllEmpty==true){
//                 return;
//             }
//             else{
                
//                 if(fe->capacity<fe->usedCapacity+2){
//                     break;
//                 }
                
                
//                 Minibus* minibus = Square_minibus_Left(square);
//                 //count car ekleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//                 if (minibus) {
//                     fe->minibusses[fe->usedCapacity] = minibus; // DİKKAT: index olarak usedCapacity kullanılıyor
//                     fe->usedCapacity += 2;
//                     vehicle_loaded = true;
//                 }
//                     fe->usedCapacity=fe->usedCapacity+2;
//                     if(fe->capacity<fe->usedCapacity+2){
//                         break;
//                     }
//                 }
            
//         }
//         if (choice == 2) {
//             isAllEmpty=true;
//             for(int i=0; i<TRUCKS_LENGTH;i++){
//                 if(square->trucks[i]!=NULL){
//                     isAllEmpty=false;
//                     break;
//                 }
//                 else{
                    
//                 }
                
//                 //wait 300ms for after
//             }
//             if(isAllEmpty==true){
//                 return;
//             }
//             else{
                
//                 if(fe->capacity<fe->usedCapacity+3){
//                     break;
//                 }
                
                
//                 Truck* truck = Square_truck_Left(square);
//                 //count car ekleeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
//                 if (truck) {
//                     fe->trucks[fe->usedCapacity] = truck; // DİKKAT: index olarak usedCapacity kullanılıyor
//                     fe->usedCapacity += 3;
//                     vehicle_loaded = true;
//                 }

//                     fe->usedCapacity=fe->usedCapacity+3;
//                     if(fe->capacity<fe->usedCapacity+3){
//                         break;
//                     }
//                 }
//             }
            
//         if(vehicle_loaded){
//             printf("loaded");
//         }
//     }
// }


void Take_vehicles(Ferry* fe, Square* square) {
    if (!fe || !square) return;
    
    wait_mses(300);

    int attempts_without_load = 0;
    while (fe->usedCapacity < fe->capacity) {
        wait_mses(300);
        if (attempts_without_load > 1) {
             break;
        }

        int choice = rand() % 3;
        bool loaded_this_try = false;

        if (choice == 0 && fe->usedCapacity + 1 <= fe->capacity) {
            Car* car = Square_car_Left(square);
            if (car) {
                fe->cars[fe->car_count] = car;
                fe->car_count++;
                fe->usedCapacity += 1;
                loaded_this_try = true;
            }
        } else if (choice == 1 && fe->usedCapacity + 2 <= fe->capacity) {
            Minibus* minibus = Square_minibus_Left(square);
            if (minibus) {
                fe->minibusses[fe->minibus_count] = minibus;
                fe->minibus_count++;
                fe->usedCapacity += 2;
                loaded_this_try = true;
            }
        } else if (choice == 2 && fe->usedCapacity + 3 <= fe->capacity) {
            Truck* truck = Square_truck_Left(square);
            if (truck) {
                fe->trucks[fe->truck_count] = truck;
                fe->truck_count++;
                fe->usedCapacity += 3;
                loaded_this_try = true;
            }
        }

        if (loaded_this_try) {
            printf("Loaded a vehicle. Capacity: %d/%d\n", fe->usedCapacity, fe->capacity);
            attempts_without_load = 0;
        } else {
            attempts_without_load++;
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
        } else if (car->has_crossed_once) {
            car->isCompleted = true;
            printf("Car %d completed round trip!\n", car->randomId);
        }
        for (int j = 0; j < carsLength; j++) {
            if (bs->cars[j] == NULL) {
                bs->cars[j] = car;
                break;
            }
        }
    }

    for (int i = 0; i < fe->minibus_count; i++) {
        Minibus* minibus = fe->minibusses[i];
        if (minibus->start_side != current_side) {
            minibus->has_crossed_once = true;
        } else if (minibus->has_crossed_once) {
            minibus->isCompleted = true;
             printf("Minibus %d completed round trip!\n", minibus->randomId);
        }
        for (int j = 0; j < minibusesLength; j++) {
            if (bs->minibuses[j] == NULL) {
                bs->minibuses[j] = minibus;
                break;
            }
        }
    }
    
    for (int i = 0; i < fe->truck_count; i++) {
        Truck* truck = fe->trucks[i];
        if (truck->start_side != current_side) {
            truck->has_crossed_once = true;
        } else if (truck->has_crossed_once) {
            truck->isCompleted = true;
            printf("Truck %d completed round trip!\n", truck->randomId);
        }
        for (int j = 0; j < trucksLength; j++) {
            if (bs->trucks[j] == NULL) {
                bs->trucks[j] = truck;
                break;
            }
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
// void Pass_vehicles(Ferry* fe,Behind_Square* bs2){
//     if(!fe->isWentToAcross){
//         for(int i=0;i<MAX_CARS;i++){
//             if(fe->cars[i]==NULL){
//             }
//             else{
//                 for(int j=0;j<CARS_LENGTH;j++){
//                     if(bs2->cars[j]==NULL){
//                         bs2->cars[j]=fe->cars[i];
//                         printf("%d has passed\n", fe->cars[i]->randomId);
//                         fe->cars[i]=NULL;
//                     }
                    
            
//                 }                
//             }

//         }
//         for(int i=0;i<MAX_MINIBUSES;i++){
//             if(fe->minibusses[i]==NULL){
//             }
//             else{
//                 for(int j=0;j<MINIBUSES_LENGTH;j++){
//                     if(bs2->minibuses[j]==NULL){
//                         bs2->minibuses[j]=fe->minibusses[i];
//                         printf("%d has passed\n", fe->minibusses[i]->randomId);
//                         fe->minibusses[i]=NULL;
//                     }
                    
            
//                 }                
//             }

//         }
//         for(int i=0;i<MAX_TRUCKS;i++){
//             if(fe->trucks[i]==NULL){
//             }
//             else{
//                 for(int j=0;j<TRUCKS_LENGTH;j++){
//                     if(bs2->trucks[j]==NULL){
//                         bs2->trucks[j]=fe->trucks[i];
//                         printf("%d has passed\n", fe->trucks[i]->randomId);
//                         fe->trucks[i]=NULL;
                        
//                     }
                    
            
//                 }                
//             }

//         }
//         fe->isWentToAcross=true;
//     }
    

//     if(fe->isWentToAcross){
//         for(int i=0;i<MAX_CARS;i++){
//             if(fe->cars[i]==NULL){
//             }
//             else{
//                 for(int j=0;j<CARS_LENGTH;j++){
                    
//                     printf("%d completed",fe->cars[i]->randomId);
//                     fe->cars[i]->isCompleted=true;
//                     fe->cars[i]=NULL;
                    
                    
            
//                 }                
//             }

//         }
//         for(int i=0;i<MAX_MINIBUSES;i++){
//             if(fe->minibusses[i]==NULL){
//             }
//             else{
//                 for(int j=0;j<MINIBUSES_LENGTH;j++){
//                     printf("%d completed",fe->minibusses[i]->randomId);
//                     fe->minibusses[i]->isCompleted=true;
//                     fe->minibusses[i]=NULL;
                    
            
//                 }                
//             }

//         }
//         for(int i=0;i<MAX_TRUCKS;i++){
//             if(fe->trucks[i]==NULL){
//             }
//             else{
//                 for(int j=0;j<TRUCKS_LENGTH;j++){
//                     printf("%d completed",fe->trucks[i]->randomId);
//                     fe->trucks[i]->isCompleted=true;
//                     fe->trucks[i]=NULL;
                    
            
//                 }                
//             }

//         }
//         fe->isWentToAcross=false;
//     }
    
    




//     fe->usedCapacity=0;


// }
