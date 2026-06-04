#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t chopstick[N];
sem_t room;

// Philosopher Function
void *philosopher(void *num)
{
    int i = *(int *)num;

    printf("Philosopher %d is Thinking\n", i);

    sem_wait(&room);

    sem_wait(&chopstick[i]);
    sem_wait(&chopstick[(i + 1) % N]);

    printf("Philosopher %d is Eating\n", i);

    sem_post(&chopstick[i]);
    sem_post(&chopstick[(i + 1) % N]);

    sem_post(&room);

    printf("Philosopher %d Finished Eating\n", i);

    pthread_exit(NULL);
}

int main()
{
    pthread_t p[N];
    int id[N];

    sem_init(&room, 0, 4);

    for(int i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for(int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }

    return 0;
}