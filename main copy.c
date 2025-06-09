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


// Number of each vehicle type
#define NUM_CARS 12
#define NUM_MINIBUSES 10
#define NUM_TRUCKS 8

// Number of tolls on each side
#define NUM_TOLLS_PER_SIDE 2
#define TOTAL_TOLLS 4

// Track vehicle positions and trips
typedef struct {
    int start_side;
    int current_side;
    bool trip_done;
} VehicleTracker;

// All vehicles in simulation
Car* all_cars[NUM_CARS];

Minibus* all_minibuses[NUM_MINIBUSES];
Truck* all_trucks[NUM_TRUCKS];

// Track vehicles' locations
VehicleTracker car_trackers[NUM_CARS];
VehicleTracker minibus_trackers[NUM_MINIBUSES];
VehicleTracker truck_trackers[NUM_TRUCKS];

// Simulation areas
Behind_Square behind_squares[2];
Square squares[2];
Toll tolls[TOTAL_TOLLS];
Ferry ferry;

// Show current simulation status
void print_simulation_state() {
    printf("\n------------------------------------------------------\n");
    printf("--- SIMULATION STATE ---\n");
    
    printf("Ferry is at SIDE %d | Capacity Used: %d/%d | Is returning: %s\n", 
           ferry.inWhichSquare, ferry.usedCapacity, ferry.capacity, ferry.isWentToAcross ? "Yes" : "No");

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

// Check if all vehicles finished trips
bool is_simulation_complete() {
    int completed_cars = 0;
    for (int i = 0; i < NUM_CARS; i++) {
        if (all_cars[i]->isCompleted) { 
            completed_cars++;
        }
    }

    int completed_minibuses = 0;
    for (int i = 0; i < NUM_MINIBUSES; i++) {
        if (all_minibuses[i]->isCompleted) {
            completed_minibuses++;
        }
    }

    int completed_trucks = 0;
    for (int i = 0; i < NUM_TRUCKS; i++) {
        if (all_trucks[i]->isCompleted) {
            completed_trucks++;
        }
    }

    return (completed_cars == NUM_CARS) && 
           (completed_minibuses == NUM_MINIBUSES) && 
           (completed_trucks == NUM_TRUCKS);
}
// Set starting positions for vehicles
void initialize_vehicles() {
    
    int starting_side = 0;
    for (int i = 0; i < NUM_CARS; i++) {
        all_cars[i] = malloc(sizeof(Car));
        Car_init(all_cars[i]);
        int starting_side = 0;
        car_trackers[i].start_side = starting_side;
        car_trackers[i].current_side = starting_side;
        all_cars[i]->start_side = starting_side;
        all_cars[i]->has_crossed_once = false;
        all_cars[i]->isCompleted = false;

        car_trackers[i].trip_done = false;

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
        int starting_side = 0;
        minibus_trackers[i].start_side = starting_side;
        minibus_trackers[i].current_side = starting_side;
        minibus_trackers[i].trip_done = false;

        all_minibuses[i]->start_side = starting_side;
        all_minibuses[i]->has_crossed_once = false;
        all_minibuses[i]->isCompleted = false;


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
        
        truck_trackers[i].start_side = starting_side;
        truck_trackers[i].current_side = starting_side;
        truck_trackers[i].trip_done = false;

        all_trucks[i]->start_side = starting_side;
        all_trucks[i]->has_crossed_once = false;
        all_trucks[i]->isCompleted = false;



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
        printf("Ferry at SIDE %d working\n", current_side);
        
        if (ferry.usedCapacity > 0) {
            printf("Unloading ferry at SIDE %d...\n", current_side);
            Pass_vehicles(&ferry, &behind_squares[current_side]); 
        }

        printf("Loading ferry from SIDE %d...\n", current_side);
        Take_vehicles(&ferry, &squares[current_side]);
        
        if (ferry.usedCapacity > 0) {
             printf("Ferry moving to SIDE %d.\n", 1 - current_side);
             ferry.inWhichSquare = 1 - current_side;
             ferry.isWentToAcross = !ferry.isWentToAcross;
        } else {
            printf("Ferry waiting at SIDE %d\n", current_side);
        }

        print_simulation_state();
        sleep(1);
    }

    printf("\n======================================================\n");
    if (rounds >= 100) {
        printf("Stopped after 100 rounds.\n");
    } else {
        printf("All vehicles returned home.\n");
    }
    printf("======================================================\n");

    return 0;
}