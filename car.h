#ifndef CAR_H
#define CAR_H // Corrected: Consistent naming

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

struct Car {
    bool hasPassedToll;
    bool isOnFerry;
    int size;
    int busyTime;
    bool isStartingSide;
    bool isCompleted;
};

typedef struct Car Car;
    
#endif 