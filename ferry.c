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
struct Ferry {
    int capacity;
    Car* cars[20];
    Truck* trucks[6];
    Minibus* minibusses[10]; 
    
};
