// Basic Thread Creation
// Objective: Familiarize yourself with creating threads.

// Instructions:
// Write a C program that creates three threads.
// Each thread should print a message, including its thread ID, to indicate it is running (e.g., "Thread X is running").
// Ensure the main thread waits for each of the threads to complete using pthread_join.
// Expected Output: Each thread prints a message, and the program exits only after all threads are complete.

#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

int THREAD_COUNT = 3;

void *print_thread_id(void*)
{
    pthread_t thread_id = pthread_self();
    printf("Thread %lu is running\n", (unsigned long)thread_id);
}

int main()
{
    pthread_t threads[THREAD_COUNT];
    int res;
    for (int i = 0; i < THREAD_COUNT; ++i)
    {
        res = pthread_create(&threads[i], NULL, print_thread_id, NULL);
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

    return 0;
}