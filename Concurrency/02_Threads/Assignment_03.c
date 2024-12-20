// Printing Numbers with Threads
// Objective: Practice thread creation and task division without synchronization.

// Instructions:
// Write a program that creates three threads.
// Each thread should print numbers from 1 to 5, along with its thread ID.
// Observe that the order of printing may vary between runs, showing the concurrent execution.
// Expected Output: Each thread prints numbers from 1 to 5, but in potentially varying orders.


#include <stdio.h>
#include <pthread.h>
#include <errno.h>

const int THREAD_COUNT = 3;
const int MAX_PRINT_NUM = 5;

void *thread_task(void*)
{
    for (int i = 1; i < MAX_PRINT_NUM + 1; ++i)
        printf("%d, ", i);
    printf("%lu\n", pthread_self());
}

int main()
{
    int ret;

    pthread_t thread_array[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        ret = pthread_create(&thread_array[i], NULL, thread_task, NULL);
        if (ret)
        {
            errno = ret;
            perror("pthread_create failed\n");
            return -1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; ++i)
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