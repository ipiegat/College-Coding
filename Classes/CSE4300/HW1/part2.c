#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PRODUCE_LIMIT 1000

// Shared buffer (implemented as a circular queue)
int queue_size;      // Set by the command line.
int *buffer;         // Array to hold items.
int in_index = 0;    // Next insertion index.
int out_index = 0;   // Next removal index.
int count = 0;       // Number of items currently in the queue.

// Counters for overall production/consumption.
int produced_count = 0;
int consumed_count = 0;

// Sleep counters for each thread
int producer_sleep_count[3] = {0, 0, 0};  // For 3 producers.
int consumer_sleep_count[2] = {0, 0};       // For 2 consumers.

// Synchronization primitives
pthread_mutex_t lock;
pthread_cond_t not_full;
pthread_cond_t not_empty;

// Producer thread function
void* producer(void* arg) {
    int thread_id = *(int*)arg;
    free(arg); // Clean up allocated id.
    int local_sleep = 0;

    while (1) {
        pthread_mutex_lock(&lock);
        // Check if we've already produced enough items.
        if (produced_count >= PRODUCE_LIMIT) {
            pthread_mutex_unlock(&lock);
            break;
        }
        // Wait until the queue is not full.
        while (count == queue_size && produced_count < PRODUCE_LIMIT) {
            local_sleep++;
            //printf("Producer thread %d sleeping due to full queue\n", thread_id);
            pthread_cond_wait(&not_full, &lock);
        }
        // After waking up, re-check production limit.
        if (produced_count >= PRODUCE_LIMIT) {
            pthread_mutex_unlock(&lock);
            break;
        }
        // Produce an item (using produced_count + 1 as a unique item).
        int item = produced_count + 1;
        buffer[in_index] = item;
        in_index = (in_index + 1) % queue_size;
        count++;
        produced_count++;
        pthread_mutex_unlock(&lock);

        // Signal consumers that an item is available.
        pthread_cond_signal(&not_empty);
        // Simulate production delay.
        usleep(10000 + 10000 * (thread_id % 5));
    }
    // Store the sleep count.
    pthread_mutex_lock(&lock);
    producer_sleep_count[thread_id - 1] = local_sleep;
    pthread_mutex_unlock(&lock);
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    int thread_id = *(int*)arg;
    free(arg);
    int local_sleep = 0;

    while (1) {
        pthread_mutex_lock(&lock);
        // If the queue is empty and production is not yet finished, wait.
        while (count == 0 && produced_count < PRODUCE_LIMIT) {
            local_sleep++;
            //printf("Consumer thread %d sleeping due to empty queue\n", thread_id);
            pthread_cond_wait(&not_empty, &lock);
        }
        // If the queue is empty and no more items will be produced, exit.
        if (count == 0 && produced_count >= PRODUCE_LIMIT) {
            pthread_mutex_unlock(&lock);
            break;
        }
        // Consume an item.
        int item = buffer[out_index];
        out_index = (out_index + 1) % queue_size;
        count--;
        consumed_count++;
        pthread_mutex_unlock(&lock);

        // Signal producers that there is space available.
        pthread_cond_signal(&not_full);
        // Simulate consumption delay.
        usleep(5000 + 10000 * (thread_id % 5));

        // If we have consumed enough items and the buffer is empty, exit.
        pthread_mutex_lock(&lock);
        if (consumed_count >= PRODUCE_LIMIT && count == 0) {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
    }
    // Save the local sleep count.
    pthread_mutex_lock(&lock);
    consumer_sleep_count[thread_id - 1] = local_sleep;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <queue_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // Set the queue size from the command line.
    queue_size = atoi(argv[1]);
    if (queue_size <= 0) {
        fprintf(stderr, "Queue size must be a positive integer.\n");
        exit(EXIT_FAILURE);
    }
    // Allocate the buffer.
    buffer = (int *)malloc(queue_size * sizeof(int));
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    // Initialize mutex and condition variables.
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
    
    pthread_t producers[3], consumers[2];
    
    // Create 3 producer threads.
    for (int i = 0; i < 3; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        if (pthread_create(&producers[i], NULL, producer, id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    // Create 2 consumer threads.
    for (int i = 0; i < 2; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        if (pthread_create(&consumers[i], NULL, consumer, id) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    // Wait for all producers to finish.
    for (int i = 0; i < 3; i++) {
        pthread_join(producers[i], NULL);
    }
    // Wake up any consumers still waiting, so they can exit if production is done.
    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&not_empty);
    pthread_mutex_unlock(&lock);
    
    // Wait for all consumers to finish.
    for (int i = 0; i < 2; i++) {
        pthread_join(consumers[i], NULL);
    }
    
    // Print out the sleep counts for each producer and consumer.
    printf("\nSleep counts:\n");
    for (int i = 0; i < 3; i++) {
        printf("Producer thread %d slept %d times\n", i + 1, producer_sleep_count[i]);
    }
    for (int i = 0; i < 2; i++) {
        printf("Consumer thread %d slept %d times\n", i + 1, consumer_sleep_count[i]);
    }
    
    // Clean up.
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    free(buffer);
    
    return 0;
}
