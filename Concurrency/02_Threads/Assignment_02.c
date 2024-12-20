// Array Processing with Threads
// Objective: Practice dividing an array processing task among multiple threads.

// Instructions:
// Create an array of integers with a few values.
// Write a function that calculates the sum of part of this array.
// Use two threads: assign each half of the array to a different thread.
// Each thread should calculate the sum of its half and print it.
// Expected Output: Two separate partial sums printed by each thread.

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

int N = 10;

long long array_sum(int* array, int size)
{
    long long sum = 0ll;
    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }
    return sum;
}

typedef struct Array {
    int* data;
    int size;
} Array;

void *array_sum_th(void* args)
{
    Array *array = (Array*)args;
    long long *sum = malloc(sizeof(long long));
    *sum = array_sum(array->data, array->size);
    return sum;
}


int main()
{
    pthread_t thread_0, thread_1;
    int ret;

    int array[N];
    for (int i = 0; i < N; ++i)
        array[i] = i + 1;

    int halfSize = N / 2;
    Array firstSubarray = {
        array,
        halfSize
    };
    Array secondSubarray = {
        array + halfSize,
        N - halfSize
    };
    
    ret = pthread_create(&thread_0, NULL, array_sum_th, (void*)(&firstSubarray));
    if (ret)
    {   
        errno = ret;
        printf("pthread_create failed\n");
        return -1;
    }
    ret = pthread_create(&thread_1, NULL, array_sum_th, (void*)(&secondSubarray));
    if (ret)
    {   
        errno = ret;
        printf("pthread_create failed\n");
        return -1;
    }

    long long *res_0;
    long long *res_1;

    ret = pthread_join(thread_0, (void*)&res_0);
    if (ret)
    {
        errno = ret;
        perror("pthread_join failed\n");
        return -1;
    }
    ret = pthread_join(thread_1, (void*)&res_1);
    if (ret)
    {
        errno = ret;
        perror("pthread_join failed\n");
        return -1;
    }

    printf("%lld, %lld\n", *res_0, *res_1);
    free(res_0);
    free(res_1);
    return 0;
}