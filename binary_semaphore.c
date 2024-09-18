#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} BinarySemaphore;

// Function to initialize the binary semaphore
void sem_init(BinarySemaphore *sem, int value) {
    sem->value = value;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

// Function to wait (P operation) on the binary semaphore
void sem_wait(BinarySemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->value == 0) {
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value = 0; // Lock the semaphore
    pthread_mutex_unlock(&sem->mutex);
}

// Function to signal (V operation) on the binary semaphore
void sem_signal(BinarySemaphore *sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value = 1; // Unlock the semaphore
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->mutex);
}

// Function to destroy the binary semaphore
void sem_destroy(BinarySemaphore *sem) {
    pthread_mutex_destroy(&sem->mutex);
    pthread_cond_destroy(&sem->cond);
}

// Example usage of the binary semaphore
void *worker(void *arg) {
    BinarySemaphore *sem = (BinarySemaphore *)arg;

    printf("Thread %ld is waiting to enter critical section.\n", pthread_self());
    sem_wait(sem);
    
    printf("Thread %ld has entered the critical section.\n", pthread_self());
    sleep(2); // Simulate work in critical section
    printf("Thread %ld is leaving the critical section.\n", pthread_self());
    
    sem_signal(sem);
    return NULL;
}

int main() {
    const int NUM_THREADS = 3;
    pthread_t threads[NUM_THREADS];
    BinarySemaphore sem;

    sem_init(&sem, 1); // Initialize the binary semaphore with value 1 (unlocked)

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

