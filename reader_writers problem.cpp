#include <pthread.h> // Include the pthread library for threading
#include <semaphore.h> // Include the semaphore library for semaphores
#include <stdio.h> // Include the standard I/O library
#include <sys/wait.h> // Include the wait system call header file

/*
This program provides a possible solution for the first readers-writers problem using mutex and semaphore.
I have used 10 readers and 5 writers to demonstrate the solution. You can adjust these values as needed.
*/

sem_t wrt; // Semaphore for controlling writer access
pthread_mutex_t mutex; // Mutex for controlling access to shared variables
int cnt = 1; // Shared variable that readers and writers access
int numreader = 0; // Shared variable to track the number of active readers

// Function for writer thread
void *writer(void *wno)
{  
    sem_wait(&wrt); // Wait for the writer semaphore
    cnt = cnt*2; // Modify the shared variable
    printf("Writer %d modified cnt to %d\n",(*((int *)wno)),cnt); // Print writer activity
    sem_post(&wrt); // Release the writer semaphore
}

// Function for reader thread
void *reader(void *rno)
{  
    pthread_mutex_lock(&mutex); // Acquire the mutex lock
    numreader++; // Increment the number of active readers
    if(numreader == 1) {
        sem_wait(&wrt); // If this is the first reader, block the writer
    }
    pthread_mutex_unlock(&mutex); // Release the mutex lock
    
    // Reading Section
    printf("Reader %d: read cnt as %d\n",*((int *)rno),cnt); // Print reader activity

    pthread_mutex_lock(&mutex); // Acquire the mutex lock
    numreader--; // Decrement the number of active readers
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, wake up the writer
    }
    pthread_mutex_unlock(&mutex); // Release the mutex lock
}

int main()
{  
    pthread_t read[10],write[5]; // Declare arrays for reader and writer threads
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex
    sem_init(&wrt,0,1); // Initialize the writer semaphore

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; // Array used to number the readers and writers

    // Create reader threads
    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    
    // Create writer threads
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    // Wait for all reader threads to finish
    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    
    // Wait for all writer threads to finish
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destroy the mutex
    sem_destroy(&wrt); // Destroy the writer semaphore

    return 0; // Exit the program
}
