#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int X, N, M;

// Shared buffer implemented as a circular queue.
int *buffer;
int in_index = 0;      // Index where next produced item will be inserted.
int out_index = 0;     // Index where next item will be consumed.
int count = 0;         // Number of filled packets in the buffer.

// Enforces production order for user threads.
int next_turn = 1;

// Counts the total number of user threads served so far.
int served = 0;

// Mutex and condition variables for synchronizing producers and consumers.
pthread_mutex_t lock;
pthread_cond_t cond_producer;
pthread_cond_t cond_consumer;

void* user_thread(void* arg) {
    int my_id = *(int*)arg;
    free(arg); // Free the id.

    // Delay based on thread id.
    int delay = 10000 + 10000 * (my_id % 5);

    pthread_mutex_lock(&lock);

    // Wait until it is this thread’s turn AND there is at least one available packet.
    while (my_id != next_turn || count == X) {
         printf("No packet available or not my turn to produce, user level thread %d going to sleep\n", my_id);
         pthread_cond_wait(&cond_producer, &lock);
    }

    usleep(delay); // Simulate some delay.
    printf("User level thread %d is going to put data in a packet\n", my_id);

    // Write data (its id) into the buffer.
    buffer[in_index] = my_id;
    in_index = (in_index + 1) % X;
    count++;

    // Allow the next thread in order to proceed.
    next_turn++;

    // Wake up kernel threads waiting for data as well as any producers waiting for an empty packet.
    pthread_cond_broadcast(&cond_consumer);
    pthread_cond_broadcast(&cond_producer);
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

void* kernel_thread(void* arg) {
    int my_id = *(int*)arg;
    free(arg);
    
    while (1) {
         pthread_mutex_lock(&lock);

         // Wait until there is data in the buffer OR all user threads have been served.
         while (count == 0 && served < N) {
              printf("No data available, Going to sleep kernel thread %d\n", my_id);
              pthread_cond_wait(&cond_consumer, &lock);
         }

         // If all user threads are served, exit the loop.
         if (served >= N) {
              pthread_mutex_unlock(&lock);
              break;
         }

         // Consume one item from the buffer.
         int servedId = buffer[out_index];
         out_index = (out_index + 1) % X;
         count--;
         served++;
         printf("user thread %d getting served\n", servedId);

         // Wake up any producer that may be waiting because a packet was full.
         pthread_cond_broadcast(&cond_producer);
         pthread_mutex_unlock(&lock);
         
         // Consumption delay.
         usleep(5000);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
         fprintf(stderr, "Usage: %s <X> <N> <M>\n", argv[0]);
         exit(EXIT_FAILURE);
    }
    // Read command-line arguments.
    X = atoi(argv[1]); // Number of packets (buffer size).
    N = atoi(argv[2]); // Number of user threads (producers).
    M = atoi(argv[3]); // Number of kernel threads (consumers).
    
    // Allocate the buffer.
    buffer = (int*) malloc(X * sizeof(int));
    if (!buffer) {
         perror("malloc");
         exit(EXIT_FAILURE);
    }
    
    // Initialize the mutex and condition variables.
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond_producer, NULL);
    pthread_cond_init(&cond_consumer, NULL);
    
    // Allocate arrays to hold thread handles.
    pthread_t *user_threads = malloc(N * sizeof(pthread_t));
    pthread_t *kernel_threads = malloc(M * sizeof(pthread_t));
    
    // Create user (producer) threads.
    for (int i = 0; i < N; i++) {
         int *arg = malloc(sizeof(*arg));
         *arg = i + 1; // User thread id.
         pthread_create(&user_threads[i], NULL, user_thread, arg);
    }

    usleep(50000); // Delay so user threads print first.
    
    // Create kernel (consumer) threads.
    for (int i = 0; i < M; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i + 1; // Kernel thread id.
        pthread_create(&kernel_threads[i], NULL, kernel_thread, arg);
   }
    
    // Wait for all user threads to finish.
    for (int i = 0; i < N; i++) {
         pthread_join(user_threads[i], NULL);
    }
    // After all producers have finished, wake up any kernel threads that may be waiting.
    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&cond_consumer);
    pthread_mutex_unlock(&lock);
    
    // Wait for all kernel threads to finish.
    for (int i = 0; i < M; i++) {
         pthread_join(kernel_threads[i], NULL);
    }
    
    // Clean up resources.
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_producer);
    pthread_cond_destroy(&cond_consumer);
    free(buffer);
    free(user_threads);
    free(kernel_threads);
    
    return 0;
}
