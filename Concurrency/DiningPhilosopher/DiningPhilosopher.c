#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <semaphore.h>

const int PHIL_COUNT = 5;

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
	return (phil_id + PHIL_COUNT - 1) % PHIL_COUNT;
}
int right_phil_id(int phil_id)
{
	return (phil_id + 1) % PHIL_COUNT;
}

void think()
{
	sleep(1);
}

void eat()
{
	sleep(1);
}

void take_forks(int phil_id)
{
	pthread_mutex_lock(&mutex);
	states[phil_id] = HUNGRY;
	test(phil_id);
	pthread_mutex_unlock(&mutex);
	sem_wait(&sems[phil_id]);
}

void put_forks(int phil_id)
{
	pthread_mutex_lock(&mutex);
	states[phil_id] = THINKING;
	
	test(left_phil_id(phil_id));
	test(right_phil_id(phil_id));

	pthread_mutex_unlock(&mutex);
	sem_post(&sems[phil_id]);
}

void test(int phil_id)
{
	if (states[phil_id] == HUNGRY && states[left_phil_id(phil_id)] != EATING && states[right_phil_id(phil_id)] != EATING)
	{
		states[phil_id] = EATING;
		sem_post(&sems[phil_id]);
	}
}


void *philosopher(void *i)
{
	int phil_id = *((int*)i);
	free(i);

	think();
	take_forks(i);
	eat();
	put_forks(i);
}

int main()
{
	pthread_t threads[PHIL_COUNT];

	for (int i = 0; i < PHIL_COUNT; ++i)
	{
		sem_init(&sems[i], 0, 1);
		states[i] = THINKING;
	}


	for (int i = 0; i < PHIL_COUNT; ++i)
	{
		int *phil_id = malloc(sizeof(*phil_id));
		if (phil_id == NULL)
		{
			fprintf(stderr, "Failed to allocate memory for thread arg\n");
			return -1;
		} 

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
