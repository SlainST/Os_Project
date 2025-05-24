#include <stdio.h>
#include <stdlib.h>
#include "toll.h"
#include <thread.h>

// Actual struct definition (private)
struct Toll {
    int x;
    int y;
};

Toll* Toll_create(int x, int y) {
    Toll* p = (Toll*)malloc(sizeof(Toll));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

void Toll_destroy(Toll* p) {
    free(p);
}

int Toll_getX(const Toll* p) {
    if (p == NULL) return 0; // Or handle error
    return p->x;
}

int Toll_getY(const Toll* p) {
    if (p == NULL) return 0; // Or handle error
    return p->y;
}

void Toll_move(Toll* p, int dx, int dy) {
    if (p == NULL) return;
    p->x += dx;
    p->y += dy;
}

void Toll_print(const Toll* p) {
    if (p == NULL) {
        printf("Toll is NULL\n");
        return;
    }
    printf("Toll(%d, %d)\n", p->x, p->y);
}
