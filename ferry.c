#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include <car.h>
#include <minibus.h>
#include <truck.h>

#include <ferry.h>
#include <square.h>

void Ferry_init(Ferry* fe){

    fe -> capacity=20;
    fe ->usedCapacity=0;
    fe-> isWentToAcross=false;
    fe->inWhichSquare=rand()%2;
}

void Take_vehicles(Ferry* fe, Square* square){
    int which=rand()%3;
    int count_car=0;
    int count_minibus=0;
    int count_truck=0;
    while (fe->usedCapacity<=17){

        if(which==0){
            int slots_to_check = 40;
            int count_local=0;
            int filled_indices[slots_to_check];
            for (int i = 0; i < slots_to_check; i++) {

                if (square->cars[i] != NULL) { 
                    filled_indices[count_local] = i; //what it does is checking for filled array spaces
                }
            }

            if (count_local > 0) {
                int random_choice = rand() % count_local;
                fe->cars[count_truck] = square->cars[filled_indices[random_choice]];
                count_car++;
            }

            
            
        }
        if (which == 1) {
            int slots_to_check_minibus = 20;
            int count_local = 0;
            int filled_indices[slots_to_check_minibus];
            for (int i = 0; i < slots_to_check_minibus; i++) {
                if (square->minibuses[i] != NULL) {
                    filled_indices[count_local] = i;
                }
            }

            if (count_local > 0) {
                int random_choice = rand() % count_local;
                if (count_minibus < slots_to_check_minibus) {
                    fe->minibusses[count_truck] = square->minibuses[filled_indices[random_choice]];
                    count_minibus++;
                }
            }
        }
        if (which == 2) {
            int slots_to_check_truck = 12;
            int count_local = 0;
            int filled_indices[slots_to_check_truck];
            for (int i = 0; i < slots_to_check_truck; i++) {
                if (square->trucks[i] != NULL) {
                    filled_indices[count_local] = i;
                }
            }

            if (count_local > 0) {
                int random_choice = rand() % count_local;
                if (count_truck < slots_to_check_truck) {
                    fe->trucks[count_truck] = square->trucks[filled_indices[random_choice]];
                    count_truck++;
                }
            }
        }
    }
    
        
    

}

void Pass_vehicles(Ferry* fe,Car* cars[20], Minibus* minibusses[10], Truck* trucks[6]){
    
    if(fe->inWhichSquare==0){

        fe->inWhichSquare=1;

        int slots_to_check = 20;
            int count_local=0;
            int filled_cars[slots_to_check];
            for (int i = 0; i < slots_to_check; i++) {

                if (fe->cars[i] != NULL) { 
                    filled_cars[count_local++] = i; //what it does is checking for filled array spaces
                }
            }

        for(int i=0; i<count_local;i++){

            //empty to other square

        }



        int slots_to_check = 10;
            int count_local=0;
            int filled_minibuses[slots_to_check];
            for (int i = 0; i < slots_to_check; i++) {

                if (fe->minibusses[i] != NULL) { 
                    filled_minibuses[count_local++] = i; //what it does is checking for filled array spaces
                }
            }
        for(int i=0; i<count_local;i++){


        }



        int slots_to_check = 6;
            int count_local=0;
            int filled_trucks[slots_to_check];
            for (int i = 0; i < slots_to_check; i++) {

                if (fe->trucks[i] != NULL) { 
                    filled_trucks[count_local++] = i; //what it does is checking for filled array spaces
                }
            }
        for(int i=0; i<count_local;i++){


        }



        if(fe->inFirstRound){

            //empty come back



            //
            fe->inFirstRound=false;

        }
    }

    if(fe->inWhichSquare==1){

        //same stuff maybe

        fe->inWhichSquare=0;
        if(fe->inFirstRound){

            //empty come back

            
            
            //belki sadec inwhichsquare eski haline getir?
            fe->inFirstRound=false;

        }
    }
    
}

