#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <semaphore.h>

#define PHIL_COUNT 5

typedef enum 
{
	THINKING,
	HUNGRY,
	EATING
} PHILOSOPHER_STATE;

pthread_mutex_t mutex;
sem_t sems[PHIL_COUNT];
PHILOSOPHER_STATE states[PHIL_COUNT];

int left_phil_id(int phil_id)
{
	// if (phil_id == 0) return PHIL_COUNT - 1;
	// return phil_id - 1;

	return (phil_id + PHIL_COUNT - 1) % PHIL_COUNT;
}
int right_phil_id(int phil_id)
{
	return (phil_id + 1) % PHIL_COUNT;
}

void print_divider()
{
	printf("_____________________\n");
}

void print_state(const char* title, int phil_id)
{
	if (title != NULL)
	{
		print_divider();
		printf("%d : %s\n", phil_id + 1, title);
	}

	char header[] = "_____________________\n";
	header[(phil_id + 1) * 4 - 2] = 'V';
	printf("%s", header);

	// print_divider();
	printf("| ");
	for (int i = 0; i < PHIL_COUNT; ++i)
	{
		PHILOSOPHER_STATE state = states[i];
		if (state == THINKING)
			printf("T");
		else if (state == HUNGRY)
			printf("H");
		else if (state == EATING)
			printf("E");
		printf(" | ");
	}
	printf("\n");
	
	print_divider();
	printf("| ");
	for (int i = 0; i < PHIL_COUNT; ++i) 
	{
		int sem_value;
		sem_getvalue(&sems[i], &sem_value);
		printf("%d | ", sem_value);
	}
	printf("\n");
	print_divider();
	printf("\n\n");
}

void think()
{
	sleep(1);
}

void eat()
{
	sleep(1);
}

void test(int phil_id)
{
	if (states[phil_id] == HUNGRY && states[left_phil_id(phil_id)] != EATING && states[right_phil_id(phil_id)] != EATING)
	{
		states[phil_id] = EATING;
		sem_post(&sems[phil_id]);

		print_state("Test -- EATING + sem_post", phil_id);
	}
}

void take_forks(int phil_id)
{
	pthread_mutex_lock(&mutex);

	states[phil_id] = HUNGRY;
	print_state("HUNGRY", phil_id);

	test(phil_id);

	pthread_mutex_unlock(&mutex);
	sem_wait(&sems[phil_id]);

	pthread_mutex_lock(&mutex);
	print_state("Took forks, start eating -- Sem wait finished", phil_id);
	pthread_mutex_unlock(&mutex);
}

void put_forks(int phil_id)
{
	pthread_mutex_lock(&mutex);
	states[phil_id] = THINKING;
	print_state("THINKING", phil_id);

	test(left_phil_id(phil_id));
	test(right_phil_id(phil_id));

	pthread_mutex_unlock(&mutex);
}




void *philosopher(void *i)
{
	int phil_id = *((int*)i);
	free(i);
	
	while(1)
	{
		think();
		take_forks(phil_id);
		eat();
		put_forks(phil_id);
	}
}

int main()
{
	pthread_t threads[PHIL_COUNT];

	for (int i = 0; i < PHIL_COUNT; ++i)
	{
		sem_init(&sems[i], 0, 0);
		states[i] = THINKING;
	}

	print_state("Starting State", 0);

	for (int i = 0; i < PHIL_COUNT; ++i)
	{
		int *phil_id = malloc(sizeof(*phil_id));
		if (phil_id == NULL)
		{
			fprintf(stderr, "Failed to allocate memory for thread arg\n");
			return -1;
		}
		*phil_id = i;

		int status = pthread_create(&threads[i], NULL, philosopher, (void*)phil_id);
		if (status)
		{
			fprintf(stderr, "Failed to create a philosopher thread\n");
			return -1;
		}
	}

	for (int i = 0; i < PHIL_COUNT; ++i)
	{
		int status = pthread_join(threads[i], NULL);
		if (status)
		{
			fprintf(stderr, "Failed to join a philosopher thread\n");
			return -1;
		}
	}
	return 0;
}
