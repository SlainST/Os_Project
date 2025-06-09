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

// Helper function to check if any vehicle is on a given side
bool is_any_vehicle_waiting(int side_index) {
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

        printf("Vehicles moving through tolls...\n");
        for (int i = 0; i < TOTAL_TOLLS; i++) {
            int side = i / NUM_TOLLS_PER_SIDE;
            Toll_random_choose(&tolls[i], &behind_squares[side]);
            Square_load(&squares[side], &tolls[i]);
        }

        int current_side = ferry.inWhichSquare;
        int other_side = 1 - current_side;
        printf("Ferry at SIDE %d is working.\n", current_side);

        if (ferry.usedCapacity > 0) {
            printf("Unloading ferry at SIDE %d...\n", current_side);
            Pass_vehicles(&ferry, &behind_squares[current_side]);
        }
        
        printf("Loading ferry from SIDE %d...\n", current_side);
        Take_vehicles(&ferry, &squares[current_side]);
        
        // --- UPDATED FERRY MOVEMENT LOGIC ---
        // Move if: 
        // 1. The ferry has passengers.
        // OR
        // 2. The ferry is empty, the current side has no waiting vehicles, BUT the other side does.
        if (ferry.usedCapacity > 0 || (!is_any_vehicle_waiting(current_side) && is_any_vehicle_waiting(other_side))) {
            printf("Ferry is moving to SIDE %d.\n", other_side);
            ferry.inWhichSquare = other_side;
        } else {
            printf("Ferry is waiting at SIDE %d.\n", current_side);
        }

        print_simulation_state();
        sleep(1);
    }

    printf("\n======================================================\n");
    if (rounds >= 100) {
        printf("SIMULATION STOPPED: Reached 100 rounds limit.\n");
    } else {
        printf("SIMULATION COMPLETE: All vehicles returned home.\n");
    }
    printf("======================================================\n");

    return 0;
}