#ifndef TOLL_ACROSS_H
#define TOLL_ACROSS_H

// Forward declaration (opaque pointer) - internal structure is hidden
typedef struct Toll Toll;

// Constructor and Destructor Toll* Toll_create(int x, int y);
Toll* Toll_create(int x, int y);
void Toll_destroy( Toll* p);

// Accessor methods (Getters)
int Toll_getX(const Toll* p);
int Toll_getY(const Toll* p);

// Other methods
void Toll_move( Toll* p, int dx, int dy);
void Toll_print(const Toll* p);

void Toll_random_choose(){

}

#endif // Toll_H