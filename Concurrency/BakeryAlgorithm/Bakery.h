#include <stdlib.h>

typedef struct
{
    int *entering;
    int *number;
    int size;
    
} BakeryLock;

void bakery_init(BakeryLock* bakery, int size);

void bakery_destroy(BakeryLock *bakery);

void bakery_lock(BakeryLock* bakery, int ndx);

void bakery_unlock(BakeryLock* bakery, int ndx);