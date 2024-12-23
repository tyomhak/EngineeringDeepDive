#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int b_counter = 0;

const int setter_delay_ms = 1000;
const int handler_delay_ms = 5000;

void* state_setter(void*)
{
    while (1)
    {
        if (rand() % 100 + 1 < 15) // 15% of having B state
        {
            b_counter++;
            printf("Total B states: %d\n", b_counter);
        }

        // simulate other activities
        usleep(setter_delay_ms);
    }
}

void* B_state_handler(void*)
{
    int handled_b_counter = 0;

    while(1)
    {
        int curr_b_counter = b_counter;
        while (handled_b_counter < curr_b_counter)
        {
            // handle B state
            handled_b_counter++;
            printf("Handled %d B states\n", handled_b_counter);
        }

        // simulate other activities
        usleep(handler_delay_ms);
    }
}



int main()
{
    pthread_t setter_thread;
    pthread_t handler_thread;

    int status = 0;
	status = pthread_create(&setter_thread, NULL, state_setter, NULL);
    if (status)
    {
        fprintf(stderr, "Failed to create state_setter thread\n");
		return -1;
    }

    status = pthread_create(&handler_thread, NULL, B_state_handler, NULL);
    if (status)
    {
        fprintf(stderr, "Failed to create B_state_handler thread\n");
		return -1;
    }

    status = pthread_join(setter_thread, NULL);
    if (status)
    {
        fprintf(stderr, "Failed to join the setter thread\n");
        return -1;
    }

    status = pthread_join(handler_thread, NULL);
    if (status)
    {
        fprintf(stderr, "Failed to join the handler thread\n");
        return -1;
    }

    return 0;
}