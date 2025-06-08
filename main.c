#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()

// --- Project Headers ---
#include "car.h"
#include "minibus.h"
#include "truck.h"
#include "toll.h"
#include "square.h"
#include "behind_square.h"
#include "ferry.h"

// --- Simulation Constants ---
#define NUM_CARS 12
#define NUM_MINIBUSES 10
#define NUM_TRUCKS 8

#define NUM_TOLLS_PER_SIDE 2
#define TOTAL_TOLLS 4

// --- Data Structures for Tracking ---
// We need to track the original location of each vehicle to know when the simulation is done.
typedef struct {
    int initial_side;
    int current_side; // 0 or 1
    bool has_completed_trip; // True when it has gone to the other side and come back
} VehicleTracker;

// --- Global Arrays for Simulation Objects ---
// All vehicles
Car all_cars[NUM_CARS];
Minibus all_minibuses[NUM_MINIBUSES];
Truck all_trucks[NUM_TRUCKS];

// Trackers for each vehicle
VehicleTracker car_trackers[NUM_CARS];
VehicleTracker minibus_trackers[NUM_MINIBUSES];
VehicleTracker truck_trackers[NUM_TRUCKS];

// Simulation environment
Behind_Square behind_squares[2];
Square squares[2];
Toll tolls[TOTAL_TOLLS];
Ferry ferry;

// --- Helper Functions ---

/**
 * @brief Prints the current state of the entire simulation.
 */
void print_simulation_state() {
    printf("\n------------------------------------------------------\n");
    printf("--- SIMULATION STATE ---\n");
    
    // Ferry status
    printf("Ferry is at SIDE %d | Capacity Used: %d/%d | Is returning: %s\n", 
           ferry.inWhichSquare, ferry.usedCapacity, ferry.capacity, ferry.isWentToAcross ? "Yes" : "No");

    // Side 0 status
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


    // Side 1 status
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


/**
 * @brief Checks if all vehicles have returned to their starting side.
 * @return True if the simulation is complete, false otherwise.
 */
bool is_simulation_complete() {
    int completed_vehicles = 0;
    // Check cars
    for (int i = 0; i < NUM_CARS; i++) {
        if (car_trackers[i].has_completed_trip) {
            completed_vehicles++;
        }
    }
    // Add checks for minibuses and trucks if they have trackers
    return completed_vehicles == NUM_CARS; // Simplified for now
}

/**
 * @brief Initializes all vehicles and places them randomly on one of the two sides.
 */
void initialize_vehicles() {
    // Initialize Cars
    for (int i = 0; i < NUM_CARS; i++) {
        Car_init(&all_cars[i]);
        int starting_side = rand() % 2;
        car_trackers[i].initial_side = starting_side;
        car_trackers[i].current_side = starting_side;
        car_trackers[i].has_completed_trip = false;

        // Add to the Behind_Square of the starting side
        for (int j = 0; j < carsLength; j++) {
            if (behind_squares[starting_side].cars[j] == NULL) {
                behind_squares[starting_side].cars[j] = &all_cars[i];
                break;
            }
        }
    }
    // NOTE: The same logic should be applied for Minibuses and Trucks
}


int main() {
    srand(time(NULL)); // Seed the random number generator

    // --- 1. INITIALIZATION ---
    printf("Initializing simulation...\n");

    // Initialize all structures to be empty (pointers are NULL)
    memset(behind_squares, 0, sizeof(behind_squares));
    memset(squares, 0, sizeof(squares));
    memset(tolls, 0, sizeof(tolls));

    // Initialize the ferry
    Ferry_init(&ferry);
    
    // Initialize and place all vehicles
    initialize_vehicles();

    printf("Initialization complete. Ferry starts at SIDE %d.\n", ferry.inWhichSquare);
    print_simulation_state();
    sleep(1); // Pause to see initial state

    // --- 2. MAIN SIMULATION LOOP ---
    int rounds = 0;
    while (!is_simulation_complete() && rounds < 100) { // Safety break after 100 rounds
        printf("\n>>> ROUND %d <<<\n", ++rounds);

        // --- STEP A: Vehicles move from Behind_Square -> Toll -> Square ---
        // This simulates vehicles passing the tolls to get in line for the ferry.
        printf("Vehicles are passing through tolls...\n");
        for (int i = 0; i < TOTAL_TOLLS; i++) {
            int side = i / NUM_TOLLS_PER_SIDE; // Tolls 0,1 are for side 0; 2,3 for side 1
            // Your Toll_random_choose should handle moving a vehicle from behind_squares[side] to squares[side]
            // For now, we'll manually simulate this logic.
            Toll_random_choose(&tolls[i], &behind_squares[side], &squares[side]);
        }
        
        // --- STEP B: Ferry Operations ---
        int current_side = ferry.inWhichSquare;
        printf("Ferry is at SIDE %d. Starting operations.\n", current_side);
        
        // 1. Unload vehicles that just arrived
        if (ferry.usedCapacity > 0) {
            printf("Unloading vehicles from ferry at SIDE %d...\n", current_side);
            // This function should move vehicles from the ferry to behind_squares[current_side]
            // It should also update the tracking status of each vehicle.
            Pass_vehicles(&ferry, &squares[0], &squares[1], &behind_squares[0], &behind_squares[1]);
        }

        // 2. Load new vehicles from the waiting square
        printf("Loading vehicles onto ferry from SIDE %d...\n", current_side);
        Take_vehicles(&ferry, &squares[current_side]);
        
        // 3. Ferry travels to the other side
        if (ferry.usedCapacity > 0) {
             printf("Ferry is departing from SIDE %d to SIDE %d.\n", current_side, 1 - current_side);
             ferry.inWhichSquare = 1 - current_side; // Travel
             ferry.isWentToAcross = !ferry.isWentToAcross; // Toggle direction flag
        } else {
            printf("Ferry at SIDE %d is empty and waiting. No one to take.\n", current_side);
        }

        // --- STEP C: Print state and wait ---
        print_simulation_state();
        sleep(1); // Pause for 1 second to make the simulation readable
    }

    // --- 3. END OF SIMULATION ---
    printf("\n======================================================\n");
    if (rounds >= 100) {
        printf("Simulation stopped after 100 rounds.\n");
    } else {
        printf("Simulation complete! All vehicles returned home.\n");
    }
    printf("======================================================\n");

    return 0;
}
