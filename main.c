#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("a");
    return 0;


}

typedef struct{
    bool hasPassedToll;
    bool isOnFerry;
    int capacity;
    int busyTime;
    bool isStartingSide;
    bool isCompleted;
}Car;


