#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DATA_SIZE 5
const int data_size = 5;

int *data[DATA_SIZE];
int data_count = 0;
pthread_mutex_t data_mutex;
pthread_cond_t data_cond_var;

void *producer(void*)
{
    while (1)
    {
        pthread_mutex_lock(&data_mutex);
        while (data_count == DATA_SIZE)
        {
            printf("PRODUCER STOPPED -- DATACOUNT = %d\n", data_count);
            pthread_cond_wait(&data_cond_var, &data_mutex);
        }

        for (int i = 0; i < data_size; ++i)
        {
            if (data[i] == NULL)
            {
                data[i] = malloc(sizeof(*data[i]));
                *data[i] = rand() % 10 + 1;
                data_count++;

                printf("Produced %d, data_count = %d\n", *data[i], data_count);

                break;
            }
        }

        pthread_mutex_unlock(&data_mutex);
        pthread_cond_signal(&data_cond_var);
    }
}

void *consumer(void*)
{
    while (1)
    {
        pthread_mutex_lock(&data_mutex);
        while (data_count == 0)
        {
            printf("CONSUMER STOPPED -- DATACOUNT = %d\n", data_count);
            pthread_cond_wait(&data_cond_var, &data_mutex);
        }

        for (int i = 0; i < data_size; ++i)
        {
            if (data[i] != NULL)
            {
                int value = *data[i];
                free(data[i]);
                data[i] = NULL;
                data_count--;

                printf("Consumed %d, data_count = %d\n", value, data_count);
                break;
            }
        }

        pthread_mutex_unlock(&data_mutex);
        pthread_cond_signal(&data_cond_var);
    }
}



int main()
{
    pthread_cond_init(&data_cond_var, NULL);
    pthread_mutex_init(&data_mutex, NULL);
    
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, consumer, NULL);
    pthread_create(&consumer_thread, NULL, producer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_cond_destroy(&data_cond_var);
    pthread_mutex_destroy(&data_mutex);

    return 0;
}