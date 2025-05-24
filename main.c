#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include <toll.h>

int main(int argc, char const *argv[])
{
    Toll* p1 = Toll_create(10, 20);
    Toll* p2 = Toll_create(5, 15);

    if (p1) {
        Toll_print(p1); // Output: Toll(10, 20)
        Toll_move(p1, 2, 3);
        //printf("Moved p1: (%d, %d)\n", Toll_getX(p1), Toll_getY(p1)); // Output: Moved p1: (12, 23)
    }

    if (p2) {
        Toll_print(p2); // Output: Toll(5, 15)
    }

    Toll_destroy(p1);
    Toll_destroy(p2);




    

    
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


