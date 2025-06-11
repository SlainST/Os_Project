#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include "car.h"
#include "minibus.h"
#include "truck.h"
#include "toll.h"
#include "square.h"
#include "behind_square.h"
#include "ferry.h"


const int lengthOfCars = 40;
const int lengthOfMinibuses = 20;
const int lengthOfTrucks = 12;

#define NUM_CARS 12
#define NUM_MINIBUSES 10
#define NUM_TRUCKS 8

#define NUM_TOLLS_PER_SIDE 2
#define TOTAL_TOLLS 4

Car* all_cars[NUM_CARS];
Minibus* all_minibuses[NUM_MINIBUSES];
Truck* all_trucks[NUM_TRUCKS];

Behind_Square behind_squares[2];
Square squares[2];
Toll tolls[TOTAL_TOLLS];
Ferry ferry;

// Bir yakada (hem gişe arkası hem meydan) araç olup olmadığını kontrol eder
bool is_any_vehicle_on_side(int side_index) {
    for (int i = 0; i < CARS_LENGTH; i++) if (squares[side_index].cars[i]) return true;
    for (int i = 0; i < MINIBUSES_LENGTH; i++) if (squares[side_index].minibuses[i]) return true;
    for (int i = 0; i < TRUCKS_LENGTH; i++) if (squares[side_index].trucks[i]) return true;
    
    for (int i = 0; i < carsLength; i++) if (behind_squares[side_index].cars[i]) return true;
    for (int i = 0; i < minibusesLength; i++) if (behind_squares[side_index].minibuses[i]) return true;
    for (int i = 0; i < trucksLength; i++) if (behind_squares[side_index].trucks[i]) return true;

    return false;
}


void print_simulation_state() {
    printf("\n------------------------------------------------------\n");
    printf("--- SIMULATION STATE ---\n");
    
    printf("Ferry is at SIDE %d | Capacity Used: %d/%d\n", 
           ferry.inWhichSquare, ferry.usedCapacity, ferry.capacity);

    int side0_behind_cars = 0, side0_behind_minibuses = 0, side0_behind_trucks = 0;
    for(int i=0; i<carsLength; i++) if(behind_squares[0].cars[i]) side0_behind_cars++;
    for(int i=0; i<minibusesLength; i++) if(behind_squares[0].minibuses[i]) side0_behind_minibuses++;
    for(int i=0; i<trucksLength; i++) if(behind_squares[0].trucks[i]) side0_behind_trucks++;

    int side0_square_cars = 0, side0_square_minibuses = 0, side0_square_trucks = 0;
    for(int i=0; i<CARS_LENGTH; i++) if(squares[0].cars[i]) side0_square_cars++;
    for(int i=0; i<MINIBUSES_LENGTH; i++) if(squares[0].minibuses[i]) side0_square_minibuses++;
    for(int i=0; i<TRUCKS_LENGTH; i++) if(squares[0].trucks[i]) side0_square_trucks++;

    printf("\n--- SIDE 0 ---\n");
    printf("Behind Square : %d Cars, %d Minibuses, %d Trucks\n", side0_behind_cars, side0_behind_minibuses, side0_behind_trucks);
    printf("Waiting Square: %d Cars, %d Minibuses, %d Trucks\n", side0_square_cars, side0_square_minibuses, side0_square_trucks);

    int side1_behind_cars = 0, side1_behind_minibuses = 0, side1_behind_trucks = 0;
    for(int i=0; i<carsLength; i++) if(behind_squares[1].cars[i]) side1_behind_cars++;
    for(int i=0; i<minibusesLength; i++) if(behind_squares[1].minibuses[i]) side1_behind_minibuses++;
    for(int i=0; i<trucksLength; i++) if(behind_squares[1].trucks[i]) side1_behind_trucks++;

    int side1_square_cars = 0, side1_square_minibuses = 0, side1_square_trucks = 0;
    for(int i=0; i<CARS_LENGTH; i++) if(squares[1].cars[i]) side1_square_cars++;
    for(int i=0; i<MINIBUSES_LENGTH; i++) if(squares[1].minibuses[i]) side1_square_minibuses++;
    for(int i=0; i<TRUCKS_LENGTH; i++) if(squares[1].trucks[i]) side1_square_trucks++;

    printf("\n--- SIDE 1 ---\n");
    printf("Behind Square : %d Cars, %d Minibuses, %d Trucks\n", side1_behind_cars, side1_behind_minibuses, side1_behind_trucks);
    printf("Waiting Square: %d Cars, %d Minibuses, %d Trucks\n", side1_square_cars, side1_square_minibuses, side1_square_trucks);
    printf("------------------------------------------------------\n\n");
}

bool is_simulation_complete() {
    int completed_vehicles = 0;
    for (int i = 0; i < NUM_CARS; i++) {
        if (all_cars[i]->isCompleted) completed_vehicles++;
    }
    for (int i = 0; i < NUM_MINIBUSES; i++) {
        if (all_minibuses[i]->isCompleted) completed_vehicles++;
    }
    for (int i = 0; i < NUM_TRUCKS; i++) {
        if (all_trucks[i]->isCompleted) completed_vehicles++;
    }
    return completed_vehicles == (NUM_CARS + NUM_MINIBUSES + NUM_TRUCKS);
}

void initialize_vehicles() {
    int starting_side = 0;
    for (int i = 0; i < NUM_CARS; i++) {
        all_cars[i] = malloc(sizeof(Car));
        Car_init(all_cars[i]);
        all_cars[i]->start_side = starting_side;
        for (int j = 0; j < carsLength; j++) {
            if (behind_squares[starting_side].cars[j] == NULL) {
                behind_squares[starting_side].cars[j] = all_cars[i];
                break;
            }
        }
    }
    for (int i = 0; i < NUM_MINIBUSES; i++) {
        all_minibuses[i] = malloc(sizeof(Minibus));
        Minibus_init(all_minibuses[i]);
        all_minibuses[i]->start_side = starting_side;
        for (int j = 0; j < minibusesLength; j++) {
            if (behind_squares[starting_side].minibuses[j] == NULL) {
                behind_squares[starting_side].minibuses[j] = all_minibuses[i];
                break;
            }
        }
    }
    for (int i = 0; i < NUM_TRUCKS; i++) {
        all_trucks[i] = malloc(sizeof(Truck));
        Truck_init(all_trucks[i]);
        all_trucks[i]->start_side = starting_side;
        for (int j = 0; j < trucksLength; j++) {
            if (behind_squares[starting_side].trucks[j] == NULL) {
                behind_squares[starting_side].trucks[j] = all_trucks[i];
                break;
            }
        }
    }
}
void process_all_vehicles_through_tolls(int side_index) {
    Behind_Square* bs = &behind_squares[side_index];
    Square* sq = &squares[side_index];
    Toll* toll_a = &tolls[side_index * 2];
    Toll* toll_b = &tolls[side_index * 2 + 1];

    // Otomobilleri işle
    for (int i = 0; i < carsLength; i++) {
        if (bs->cars[i] != NULL) {
            // Basitlik adına, rastgele bir gişe seçelim.
            // Gerçekte HGS/OGS bakiyesi kontrolü de burada yapılabilir.
            wait_ms(bs->cars[i]->busyTime); 
            
            // Aracı Square'e taşı
            for (int j = 0; j < CARS_LENGTH; j++) {
                if (sq->cars[j] == NULL) {
                    sq->cars[j] = bs->cars[i];
                    bs->cars[i] = NULL; // Eski yerini boşalt
                    break;
                }
            }
        }
    }

    // Minibüsleri işle
    for (int i = 0; i < minibusesLength; i++) {
        if (bs->minibuses[i] != NULL) {
            wait_ms(bs->minibuses[i]->busyTime);
            for (int j = 0; j < MINIBUSES_LENGTH; j++) {
                if (sq->minibuses[j] == NULL) {
                    sq->minibuses[j] = bs->minibuses[i];
                    bs->minibuses[i] = NULL;
                    break;
                }
            }
        }
    }

    // Kamyonları işle
    for (int i = 0; i < trucksLength; i++) {
        if (bs->trucks[i] != NULL) {
            wait_ms(bs->trucks[i]->busyTime);
            for (int j = 0; j < TRUCKS_LENGTH; j++) {
                if (sq->trucks[j] == NULL) {
                    sq->trucks[j] = bs->trucks[i];
                    bs->trucks[i] = NULL;
                    break;
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));

    printf("Starting simulation...\n");
    memset(behind_squares, 0, sizeof(behind_squares));
    memset(squares, 0, sizeof(squares));
    memset(tolls, 0, sizeof(tolls));
    Ferry_init(&ferry);
    initialize_vehicles();

    printf("Setup done. Ferry starts at SIDE %d.\n", ferry.inWhichSquare);
    print_simulation_state();
    sleep(1);

    int rounds = 0;
    while (!is_simulation_complete() && rounds < 100) {
        printf("\n>>> ROUND %d <<<\n", ++rounds);

        int current_side = ferry.inWhichSquare;
        int other_side = 1 - current_side;
        printf("Ferry is at SIDE %d.\n", current_side);

        // 1. Adım: If ferry filled move vehicles
        if (ferry.usedCapacity > 0) {
            printf("Unloading ferry at SIDE %d...\n", current_side);
            Pass_vehicles(&ferry, &behind_squares[current_side]);
            print_simulation_state(); // Durumu gör
        }
        
        // 2. Toll moves
        printf("Vehicles at SIDE %d moving through tolls to the waiting square...\n", current_side);
        process_all_vehicles_through_tolls(current_side);
        print_simulation_state(); // Durumu gör

        // 3. Ferrybot carry
        printf("Loading ferry from SIDE %d...\n", current_side);
        Take_vehicles(&ferry, &squares[current_side]);
        
        // 4. FERRYBOT MOVES.
        if (ferry.usedCapacity > 0 || (!is_any_vehicle_on_side(current_side) && is_any_vehicle_on_side(other_side))) {
            printf("Ferry is moving to SIDE %d.\n", other_side);
            ferry.inWhichSquare = other_side;
        } else {
            printf("Ferry is waiting at SIDE %d.\n", current_side);
        }

        print_simulation_state();
        
    }

    printf("\n======================================================\n");
    if (rounds >= 100) {
        printf("SIMULATION STOPPED: Reached 100 rounds limit.\n");
    } else {
        printf("SIMULATION COMPLETE: All vehicles returned home in %d rounds.\n", rounds);
    }
    printf("======================================================\n");

    return 0;
}