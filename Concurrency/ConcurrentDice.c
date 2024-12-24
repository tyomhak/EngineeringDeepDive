#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_barrier_t dice_throwing_barrier;
pthread_barrier_t winner_calculation_barrier;

int thrown_dice[6];

void* throw_dice(void* arg)
{
    int index = *((int*)arg);
    free(arg);

    while (1)
    {
        thrown_dice[index] = rand() % 6 + 1;
        pthread_barrier_wait(&dice_throwing_barrier);
        pthread_barrier_wait(&winner_calculation_barrier);
    }
}

void *calculate_winner(void* arg)
{
    while(1)
    {
        pthread_barrier_wait(&dice_throwing_barrier);
        int winner = 0;
        for (int i = 0; i < 6; ++i)
        {
            printf("%d, ", thrown_dice[i]);
            if (thrown_dice[i] > thrown_dice[winner])
                winner = i;
        }
        printf("   : Winner is %d\n", winner + 1);
        pthread_barrier_wait(&winner_calculation_barrier);
    }
}


int main()
{
    pthread_barrier_init(&dice_throwing_barrier, NULL, 7);
    pthread_barrier_init(&winner_calculation_barrier, NULL, 7);
    int status;

    pthread_t player_threads[6];
    for (int i = 0; i < 6; ++i)
    {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        status = pthread_create(&player_threads[i], NULL, throw_dice, (void*)arg);
        if (status)
        {
            printf("Failed to create Player thread\n");
        }
    }

    pthread_t calculation_thread;
    status = pthread_create(&calculation_thread, NULL, calculate_winner, NULL);
    if (status)
    {
        printf("Failed to create calculating thread\n");
    }

    for (int i = 0; i < 6; ++i)
    {
        status = pthread_join(player_threads[i], NULL);
        if (status)
            printf("Failed to join Player thread\n");
    }
    status = pthread_join(calculation_thread, NULL);
    if (status)
        printf("Failed to join calculating thread\n");

    pthread_barrier_destroy(&dice_throwing_barrier);
    pthread_barrier_destroy(&winner_calculation_barrier);
}