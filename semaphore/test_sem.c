#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define LOOP_COUNTER 100000

void *thread_function1(void *arg);
void *thread_function2(void *arg);

int counter;
sem_t bin_sem;

int main() {
    int res1, res2;
    pthread_t a_thread1, a_thread2;
    void *thread_result;

    res1 = sem_init(&bin_sem, 0, 1);

    if (res1 != 0) {
        perror("Semaphore initialization failed");
	exit(EXIT_FAILURE);
    }

    res1 = pthread_create(&a_thread1, NULL, thread_function1, NULL);
    res2 = pthread_create(&a_thread2, NULL, thread_function2, NULL);

    if (res1 != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    if (res2 != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res1 = pthread_join(a_thread1, &thread_result);
    res2 = pthread_join(a_thread2, &thread_result);

    printf("main: Final counter: %d\n", counter);
    
    exit(EXIT_SUCCESS);
}

void *thread_function1(void *arg) {
    int i = 0;

    for (i = 0; i < LOOP_COUNTER; i++) {
        sem_wait(&bin_sem);
	counter = counter + 1;
	sem_post(&bin_sem);
    }
    pthread_exit("Thank you for the CPU time");
}

void *thread_function2(void *arg) {
    int i = 0;

    for (i = 0; i < LOOP_COUNTER; i++) {
        sem_wait(&bin_sem);
	counter = counter - 1;
	sem_post(&bin_sem);
    }
}
