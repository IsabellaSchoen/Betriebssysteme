/*
Gruppe: 22
Autor1: Isabella Schön
Autor2: Leon Budimovic

Kapitel 29 Aufgabe 2

Quellen:
 - Internet bzw. Terminal - manual page für measurement
 - Buch
- Stackoverflow
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#define BILLION  1000000000


int loops = 20;

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;


typedef struct __myargs_t {
    counter_t *counter;
} myargs_t;


void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value = c->value + 1;
    pthread_mutex_unlock(&c->lock);
}


/* void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}*/


/*void get(count *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}*/


void *mythread(void *args) {
    myargs_t *p = (myargs_t *) args;
    for(int i = loops; i < loops; i++)
    {
        increment(p->counter);
    }
    return NULL;
}


struct timespec * diff_time (struct timespec before, struct timespec after, struct timespec *result) {
    if (result==NULL)
        return NULL;
    if ((after.tv_sec<before.tv_sec) || ((after.tv_sec==before.tv_sec) && 
         (after.tv_nsec<=before.tv_nsec))) { /* after before before */ 
          result->tv_sec = result->tv_nsec = 0;
    }
    result->tv_sec = after.tv_sec - before.tv_sec; 
    result->tv_nsec= after.tv_nsec- before.tv_nsec;
    if (result->tv_nsec<0) {
         result->tv_sec--;
         /* result->tv_nsec is negative, therefore we use "+" */ 
         result->tv_nsec = BILLION+result->tv_nsec;
    }
        return result;
}


int main(int argc, char *argv[]) {
    if(argc < 2)
    {
        fprintf(stderr, "FAILURE: too less arguments\n");
        return 1;
    }


    struct timespec begin;
    struct timespec end;
    struct timespec result;
    int numthreads = atoi(argv[1]);
    //int loops = atoi(argv[2]);
    pthread_t thread[numthreads];
    //int counter = 0;

    //pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    counter_t c;
    init(&c);

    myargs_t args[numthreads];
    for(int i = 0; i < numthreads; i++)
    {
        args[i].counter = &c;
    }


    clock_gettime(CLOCK_REALTIME, &begin);
    for(int i = 0; i < numthreads; i++) {
        pthread_create(&thread[i], NULL, mythread, &args[i]);
    }
    /*for(int i = 0; i < loops; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }*/
    for(int i = 0; i < numthreads; i++) {
        pthread_join(thread[i], NULL);
    }
    clock_gettime(CLOCK_REALTIME, &end);


    //unsigned long time = (end.tv_sec - begin.tv_sec) * BILLION + end.tv_nsec - begin.tv_nsec;

    //printf("Measured time: %lu ns \n", time);

    diff_time(begin, end, &result);
    unsigned long time = result.tv_sec * BILLION + result.tv_nsec;

    printf("Measured time: %lu ns \n", time);

    printf("Measured time: %lu microsec \n", time/1000);


    return 0;
}

