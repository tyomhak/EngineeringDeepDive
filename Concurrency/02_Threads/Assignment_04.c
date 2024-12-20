// Calculating Square of Numbers in Parallel
// Objective: Demonstrate simple tasks that can run in parallel.

// Instructions:
// Create an array of integers (e.g., [1, 2, 3, 4, 5]).
// For each number in the array, create a thread that calculates its square and prints the result (e.g., "Square of 2 is 4").
// Wait for all threads to finish before the main program exits.
// Expected Output: Each thread prints the square of its assigned number.


#include <stdio.h>
#include <pthread.h>
#include <errno.h>

const int ARRAY_SIZE = 10;

void print_square(int i)
{
    printf("%d\n", i * i);
}

void *thread_task(void* args)
{
    print_square(*(int*)(args));
}

int main()
{
    int ret;
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i)
        array[i] = i + 1;

    pthread_t thread_array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        ret = pthread_create(&thread_array[i], NULL, thread_task, &array[i]);
        if (ret)
        {
            errno = ret;
            perror("pthread_create failed\n");
            return -1;
        }
    }

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        ret = pthread_join(thread_array[i], NULL);
        if (ret)
        {
            errno = ret;
            perror("pthread_join failed\n");
            return -1;
        }
    }
    
    return 0;
}