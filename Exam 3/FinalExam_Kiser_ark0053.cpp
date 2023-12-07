// Please change the following into your name
// #0#BEGIN# DO NOT MODIFY COMMENT LINE!
// Aidan
// Kiser
// #0#END# DO NOT MODIFY COMMENT LINE!
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include <iostream>
using namespace std;

#define N 5
// We need 5 different semaphores, because we use each semaphore value indicates the usage
// of each resource(chopstick). Initially, the semaphore value for each chopstick is 1.
// After using it, the value decrease 1 and becames 0.
// In other words, zero means chopstick currently is occupied and not available.
// We define a semaphore type array of total 5 chopsticks. (N=5):
sem_t chopsticks[N];

// Please define a new semaphore type single variable called m
// #1#BEGIN# DO NOT MODIFY COMMENT LINE!
sem_t m;
// #1#END# DO NOT MODIFY COMMENT LINE!
// m indicates the total number of philosorphers are eating at the same time

// We have Philosopher Zero, Philosopher One, ..., Philosopher Four.
// The id of 5 philosophers stored in the integer array philosophers
int philosophers[N] = {0, 1, 2, 3, 4};

void delay (int len) {
    int i = rand() % len;
    int x;
    while (i > 0) {
        x = rand() % len;
        while (x > 0) {
            x--;
        }
        i--;
    }
}

void *philosopher (void* arg) {
    int i = *(int *)arg;

    // index right hand chopstick as the same id of the philosopher
    int right = i;

    // left hand chopstick should be indexed as the id of the philosopher + 1
    // it is also the right hand chopstick of the next philosopher sit after him
    // if the value equals 5, the left hand chopsticks of the last philosopher
    // also be the first philosopher's right hand chopsticks, because the table
    // is round

    // index left hand chopstick as the id of the philosopher + 1
    // Note the value loop back to 0 when equals N. Consider use % operation.
    // #2#BEGIN# DO NOT MODIFY COMMENT LINE!
    int left = i + 1;
    // #2#END# DO NOT MODIFY COMMENT LINE!

    while (1) {
        printf("Philosopher %d is thinking.\n", i);
        delay(60000);

        printf("Philosopher %d is hungry.\n", i);

        // wait for the semaphore m first, make sure no more than 4 philosophers
        // pick their first chopstick at the same time.
        // after using it, the value will decrease 1
        // THAT IS WHY use need to use &, because the semaphore need to be modifie
        sem_wait(&m);


        // Please wait for first (right) chopstick to use
        // Pay attention to the & operator
		// #3#BEGIN# DO NOT MODIFY COMMENT LINE!
        sem_wait(&chopsticks[right]);
		// #3#END# DO NOT MODIFY COMMENT LINE!

        printf("Philosopher %d picked up Chopstick %d, can NOT eat with one chopstick.\n", i, right);

        // wait to use the left chopstick
        sem_wait(&chopsticks[left]);


        printf("Philosopher %d picked up Chopstick %d, now is eating with two chopsticks.\n", i, left);
        delay(60000);

        // release the first chopstick, increase the semaphore 1 by sem_post
		sem_post(&chopsticks[right]);


        printf("Philosopher %d put down Chopstick %d.\n", i, right);

        // when any right chopstick been released,
        // increase semaphore m to release one of capacity of philosophers eats
        // at the same time

        // please release one unit capacity of philosophers
        // #4#BEGIN# DO NOT MODIFY COMMENT LINE!
        sem_post(&m);
        // #4#END# DO NOT MODIFY COMMENT LINE!

        sem_post(&chopsticks[left]);
        printf("Philosopher %d put down Chopstick %d.\n", i, left);
    }
}

int main (int argc, char **argv) {
	// Use srand function to create dynamic random numbers
    // based on time(NULL) function result.
    // #5#BEGIN# DO NOT MODIFY COMMENT LINE!
    srand(time(NULL));
    // #5#END# DO NOT MODIFY COMMENT LINE!
    pthread_t philo[N];

    int i;
    // change your the following id into your banner id
    // #6#BEGIN# DO NOT MODIFY COMMENT LINE!
    int banner_id = 904120137;
    // #6#END# DO NOT MODIFY COMMENT LINE!
    printf("Banner id: %d\n", banner_id);

    // use sem_init(&semaphore_variable, 0, initial_semaphore_value) function
    // to initialize all the chopstick semaphore
    for (i=0; i<N; i++) {
    // #7#BEGIN# DO NOT MODIFY COMMENT LINE!
    sem_init(&chopsticks[i], 0, 1);
    // #7#END# DO NOT MODIFY COMMENT LINE!
    }

    // initialize the new semaphore m
    // think what should be the initial value, and why?
    // #8#BEGIN# DO NOT MODIFY COMMENT LINE!
    sem_init(&m, 0, 1);
    // #8#END# DO NOT MODIFY COMMENT LINE!

    // use pthread_create function to create threads
    for (i=0; i<N; i++) {
        // #9#BEGIN# DO NOT MODIFY COMMENT LINE!
        pthread_create(&philo[i], NULL, philosopher, &philosophers[i]);
        // #9#END# DO NOT MODIFY COMMENT LINE!
    }

    // put threads into the system
    for (i=0; i<N; i++) {
        pthread_join(philo[i], NULL);
    }

    // destroy semaphores
    for (i=0; i<N; i++) {
       sem_destroy(&chopsticks[i]);
    }

    // also do not forgot to destroy the m semaphore
    // #10#BEGIN# DO NOT MODIFY COMMENT LINE!
    sem_destroy(&m);
    // #10#END# DO NOT MODIFY COMMENT LINE!

    return 0;
}
