#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 8   // Buffer size
int buffer[N];
int in = 0;
int out = 0;
// Semaphores
sem_t empty;   // Counts empty slots
sem_t full;    // Counts filled slots
// Mutex lock
pthread_mutex_t S;
// Function to produce item
int produce_item() {
    static int item = 1;
    return item++;
}
// Function to consume item
void consume_item(int item) {
    printf("Item processed: %d\n", item);
}
// Producer thread
void* producer(void* arg) {
    int itemP;
    for(int i=0;i<=5;i++){
        // Produce item
        itemP = produce_item();
        // Wait for empty slot
        sem_wait(&empty);
        // Enter critical section
        pthread_mutex_lock(&S);
        // Insert item into buffer
        buffer[in] = itemP;
        printf("Produced: %d at position %d\n",
               itemP, in);
        // Circular queue update
        in = (in + 1) % N;
        // Exit critical section
        pthread_mutex_unlock(&S);
        // Signal filled slot
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}
// Consumer thread
void* consumer(void* arg) {
    int itemC;
    for(int i=0;i<=5;i++){
        // Wait for filled slot
        sem_wait(&full);
        // Enter critical section
        pthread_mutex_lock(&S);
        // Remove item from buffer
        itemC = buffer[out];
        printf("Consumed: %d from position %d\n",
               itemC, out);
        // Circular queue update
        out = (out + 1) % N;
        // Exit critical section
        pthread_mutex_unlock(&S);
        // Signal empty slot
        sem_post(&empty);
        // Consume item
        consume_item(itemC);
        sleep(2);
    }
    return NULL;
}
int main() {
    pthread_t prod, cons;
    // Initialize semaphores
    // Initially all slots are empty
    sem_init(&empty, 0, N);
    // Initially no filled slots
    sem_init(&full, 0, 0);
    // Initialize mutex
    pthread_mutex_init(&S, NULL);
    // Create producer thread
    pthread_create(&prod, NULL,
                   producer, NULL);
    // Create consumer thread
    pthread_create(&cons, NULL,
                   consumer, NULL);
    // Wait for threads
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&S);
    return 0;
}
