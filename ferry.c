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

#include "ferry.h"
#include <square.h>
#include <behind_square.h>


bool isAllEmpty=false;

Car* carWillBeSend;
Minibus* minibusWillBeSend;
Truck* truckWillBeSend;

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
    while (fe->usedCapacity<20){
        
        if(which==0){
            //skip if 
            isAllEmpty=true;
            for(int i=0; i<CARS_LENGTH;i++){
                if(square->cars[i]!=NULL){
                    isAllEmpty=false;
                    break;
                }
                else{
                    
                }
                
                //wait 300ms for after
            }
            if(isAllEmpty=true){
                if(fe->isWentToAcross=true){
                    fe->isWentToAcross=false;
                }

                if(fe->isWentToAcross=false){
                    fe->isWentToAcross=true;
                }
            }
            else{
                for(int i=fe->usedCapacity;i< fe->capacity;){
                    if(fe->capacity<fe->usedCapacity+1){
                        break;
                    }
                    
                    fe->minibusses[fe->usedCapacity]=Behind_Square_Truck_Left(sqrt);



                    fe->usedCapacity=fe->usedCapacity+1;
                    if(fe->capacity<fe->usedCapacity+1){
                        break;
                    }
                }
            }
            
            
        }
        if (which == 1) {
            isAllEmpty=true;
            for(int i=0; i<MINIBUSES_LENGTH;i++){
                if(square->minibuses[i]!=NULL){
                    isAllEmpty=false;
                    break;
                }
                else{
                    
                }
                
                //wait 300ms for after
            }
            if(isAllEmpty=true){
                return;
            }
            else{
                for(int i=fe->usedCapacity;i<fe->capacity;){
                    if(fe->capacity<fe->usedCapacity+2){
                        break;
                    }
                    fe->minibusses[fe->usedCapacity]=Behind_Square_Minibus_Left(sqrt);



                    fe->usedCapacity=fe->usedCapacity+2;
                    if(fe->capacity<fe->usedCapacity+2){
                        break;
                    }
                }
            }
        }
        if (which == 2) {
            isAllEmpty=true;
            for(int i=0; i<TRUCKS_LENGTH;i++){
                if(square->trucks[i]!=NULL){
                    isAllEmpty=false;
                    break;
                }
                else{
                    
                }
                
                //wait 300ms for after
            }
            if(isAllEmpty=true){
                return;
            }
            else{
                for(int i=fe->usedCapacity;i<fe->capacity;){
                    if(fe->capacity<fe->usedCapacity+3){
                        break;
                    }
                    fe->trucks[fe->usedCapacity]=Behind_Square_Truck_Left(sqrt);



                    fe->usedCapacity=fe->usedCapacity+3;
                    if(fe->capacity<fe->usedCapacity+3){
                        break;
                    }
                }
            }
            
        }
    }
    
        
    

}

void Pass_vehicles(Ferry* fe,Square* square0, Square* square1, Behind_Square* bs1, Behind_Square* bs2){
    if(!fe->isWentToAcross){
        for(int i=0;i<lengthOfCars;i++){
            if(fe->cars[i]==NULL){
            }
            else{
                for(int j=0;j<CARS_LENGTH;j++){
                    if(bs2->cars[j]==NULL){
                        bs2->cars[j]=fe->cars[i];
                        printf(fe->cars[i]->randomId+ "has passed");
                        fe->cars[i]=NULL;
                    }
                    
            
                }                
            }

        }
        for(int i=0;i<lengthOfMinibuses;i++){
            if(fe->minibusses[i]==NULL){
            }
            else{
                for(int j=0;j<MINIBUSES_LENGTH;j++){
                    if(bs2->minibuses[j]==NULL){
                        bs2->minibuses[j]=fe->minibusses[i];
                        printf(fe->minibusses[i]->randomId+ "has passed");
                        fe->minibusses[i]=NULL;
                    }
                    
            
                }                
            }

        }
        for(int i=0;i<lengthOfTrucks;i++){
            if(fe->trucks[i]==NULL){
            }
            else{
                for(int j=0;j<TRUCKS_LENGTH;j++){
                    if(bs2->trucks[j]==NULL){
                        bs2->trucks[j]=fe->trucks[i];
                        printf(fe->trucks[i]->randomId+ "has passed");
                        fe->trucks[i]=NULL;
                        
                    }
                    
            
                }                
            }

        }
        fe->isWentToAcross=true;
    }
    

    if(fe->isWentToAcross){
        for(int i=0;i<lengthOfCars;i++){
            if(fe->cars[i]==NULL){
            }
            else{
                for(int j=0;j<CARS_LENGTH;j++){
                    
                    printf(fe->cars[i]->randomId+"completed");
                    printf(fe->cars[i]->isCompleted);
                    fe->cars[i]=NULL;
                    
                    
            
                }                
            }

        }
        for(int i=0;i<lengthOfMinibuses;i++){
            if(fe->minibusses[i]==NULL){
            }
            else{
                for(int j=0;j<MINIBUSES_LENGTH;j++){
                    printf(fe->minibusses[i]->randomId+"completed");
                    printf(fe->minibusses[i]->isCompleted);
                    fe->minibusses[i]=NULL;
                    
            
                }                
            }

        }
        for(int i=0;i<lengthOfTrucks;i++){
            if(fe->trucks[i]==NULL){
            }
            else{
                for(int j=0;j<TRUCKS_LENGTH;j++){
                    printf(fe->trucks[i]->randomId+"completed");
                    printf(fe->trucks[i]->isCompleted);
                    fe->trucks[i]=NULL;
                    
            
                }                
            }

        }
        fe->isWentToAcross=false;
    }
    
    




    fe->usedCapacity=0;


}

