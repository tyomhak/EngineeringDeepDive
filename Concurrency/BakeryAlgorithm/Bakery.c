#include <Bakery.h>

void bakery_init(BakeryLock* bakery, int size)
{
    bakery->size = size;
    bakery->entering = (int*)malloc(sizeof(int) * size);
    bakery->number = (int*)malloc(sizeof(int) * size);
}

void bakery_destroy(BakeryLock *bakery)
{
    free(bakery->entering);
    free(bakery->number);
}

int bakery_get_next_number(BakeryLock* bakery)
{
    int number = 0;
    for (int i = 0; i < bakery->size; ++i)
    {
        if (bakery->number[i] > number)
            number = bakery->number[i];
    }
    return number + 1;
}

void bakery_lock(BakeryLock* bakery, int ndx)
{
    bakery->entering[ndx] = 1;
    bakery->number[ndx] = bakery_get_next_number(bakery);
    bakery->entering[ndx] = 0;

    for (int i = 0; i < bakery->size; ++i)
    {
        while (bakery->entering[i]){}
        while (bakery->number[i] != 0 && 
            (bakery->number[i] < bakery->number[ndx] || 
            (bakery->number[i] == bakery->number[ndx] && i < ndx))) 
        {}
    }
}

void bakery_unlock(BakeryLock* bakery, int ndx)
{
    bakery->number[ndx] = 0;
}