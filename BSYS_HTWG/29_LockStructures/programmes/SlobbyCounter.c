/*
Gruppe: 22
Autor1: Isabella Schön
Autor2: Leon Budimovic

Kapitel 29 Aufgabe 3

Quellen:
 - an Code von simplecounter orientiert
 - Internet bzw. Terminal - manual page für measurement
 - Buch
*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
//#include common_threads.h
#define NUMCPUS 5
#define BILLION  1000000000

typedef struct __counter_t {
    int             global;         // global count
    pthread_mutex_t glock;          // global lock
    int             local[NUMCPUS]; // per-CPU count
    pthread_mutex_t llock[NUMCPUS]; // ... and locks
    int             threshold;      // update frequency
} counter_t;


typedef struct __myargs_t {
    int id;
    counter_t *c;
    int crement;
} myargs_t;


// init: record threshold, init locks, init values
// of all local counts and global count
/*
    counters:
    approximate counter wird durch 'single logical counter' und 'global counter' präsentiert
    der logical counter ist präsentiert durch numerous local physical counter -> one per CPU

    locks:
    one for each local counter
    one for each global counter
*/
void init(counter_t *c, int threshold) { //c is pointer to the structure
    c->threshold = threshold; //value for S
    c->global = 0; //starting at value 0

    pthread_mutex_init(&c->glock, NULL); //Lock für global counter
    for (int i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0; //local counter
        pthread_mutex_init(&c->llock[i], NULL); //Lock für logical counter
    }
}


// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void update(int threadID, counter_t *c, int amt) {
    //int amt = 1;
    int cpu = threadID % NUMCPUS;
    printf("ThreadID %d\n", threadID);
    //printf("%d\n", cpu);
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {// transfer to global (assumes amt>0)
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}


// get: just return global amount (approximate)
int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val; // only approximate!
}


void *mythread(void *arg) {
    myargs_t *p = (myargs_t *) arg;
    //myargs_t *p = (myargs_t) malloc(sizeof(myargs_t));
    update(p->id, p->c, p->crement);
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
    pthread_t thread[numthreads];

    counter_t c;
    init(&c, NUMCPUS);

    myargs_t args[numthreads];
    for(int i = 0; i < numthreads; i++)
    {
        args[i].id = i;
        args[i].c = &c;
        args[i].crement = 1; //++;
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
    for(int i = 0; i < numthreads; i++) {
        pthread_create(&thread[i], NULL, mythread, &args[i]);
    }
    for(int i = 0; i < numthreads; i++) {
        pthread_join(thread[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    
    //unsigned long time = (end.tv_sec - begin.tv_sec) * BILLION + end.tv_nsec - begin.tv_nsec;
    diff_time(begin, end, &result);
    unsigned long time = result.tv_sec * BILLION + result.tv_nsec;

    printf("Measured time: %lu ns \n", time);

    printf("Measured time: %lu microsec \n", time/1000);


    return 0;
}