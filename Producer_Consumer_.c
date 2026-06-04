#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty;
sem_t full;
sem_t mutex;

// Producer Function
void *producer(void *arg)
{
    int item;

    printf("Enter item to produce: ");
    scanf("%d", &item);

    sem_wait(&empty);   // wait(empty)
    sem_wait(&mutex);   // wait(mutex)

    buffer[in] = item;
    printf("Produced: %d\n", item);

    in = (in + 1) % SIZE;

    sem_post(&mutex);   // signal(mutex)
    sem_post(&full);    // signal(full)

    pthread_exit(NULL);
}

// Consumer Function
void *consumer(void *arg)
{
    sem_wait(&full);    // wait(full)
    sem_wait(&mutex);   // wait(mutex)

    int item = buffer[out];
    printf("Consumed: %d\n", item);

    out = (out + 1) % SIZE;

    sem_post(&mutex);   // signal(mutex)
    sem_post(&empty);   // signal(empty)

    pthread_exit(NULL);
}

int main()
{
    pthread_t p, c;

    // Initialize semaphores
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_join(p, NULL);

    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}







8. pthread_t
pthread_t p,c;

Think:

p = producer thread
c = consumer thread
9. Creating Thread
pthread_create(&p,NULL,producer,NULL);

Syntax:

pthread_create(
    thread_id,
    attributes,
    function_name,
    argument
);

Example

pthread_create(&p,NULL,producer,NULL);

means:

Create thread p
Run producer()
10. Joining Thread
pthread_join(p,NULL);

Meaning:

Wait until thread p finishes

Without join:

Main may terminate before producer finishes