#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#include "Bakery.h"

const int THREAD_COUNT = 40;
int value = 0;

BakeryLock lock;

void *increment_value(void* p_thread_ndx)
{
    int thread_ndx = (int)p_thread_ndx;
    for (int i = 0; i < 100; ++i)
    {
        bakery_lock(&lock, thread_ndx);
        value++;
        bakery_unlock(&lock, thread_ndx);
    }
}

int main()
{
    bakery_init(&lock, THREAD_COUNT);
    pthread_t threads[THREAD_COUNT];
    int res;
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        res = pthread_create(&threads[i], NULL, increment_value, (void*)i);
        if (res)
        {
            errno = res;
            perror("pthread_create");
            return -1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        res = pthread_join(threads[i], NULL);
        if (res)
        {
            errno = res;
            perror("pthread_join");
            return -1;
        }
    }
    printf("%d\n", value);

    bakery_destroy(&lock);
    return 0;
}