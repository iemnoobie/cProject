#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} CountingSemaphore;

// Function to initialize the counting semaphore
void sem_init(CountingSemaphore *sem, int value) {
    sem->value = value;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

// Function to wait (P operation) on the counting semaphore
void sem_wait(CountingSemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->value <= 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value--; // Decrement the semaphore value
    pthread_mutex_unlock(&sem->mutex);
}

// Function to signal (V operation) on the counting semaphore
void sem_signal(CountingSemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value++; // Increment the semaphore value
    pthread_cond_signal(&sem->cond); // Wake up a waiting thread if any
    pthread_mutex_unlock(&sem->mutex);
}

// Function to destroy the counting semaphore
void sem_destroy(CountingSemaphore *sem) {
    pthread_mutex_destroy(&sem->mutex);
    pthread_cond_destroy(&sem->cond);
}

// Example usage of the counting semaphore
#define NUM_THREADS 5
#define MAX_RESOURCES 3

void *worker(void *arg) {
    CountingSemaphore *sem = (CountingSemaphore *)arg;

    printf("Thread %ld is waiting to acquire a resource.\n", pthread_self());
    sem_wait(sem);
    
    printf("Thread %ld has acquired a resource.\n", pthread_self());
    sleep(1); // Simulate work with the resource
    printf("Thread %ld is releasing the resource.\n", pthread_self());
    
    sem_signal(sem);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    CountingSemaphore sem;

    sem_init(&sem, MAX_RESOURCES); // Initialize the counting semaphore with available resources

    // Create worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, (void *)&sem);
    }

    // Join the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem); // Clean up semaphore resources
    return 0;
    }

