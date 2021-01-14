/*
Gruppe: 22
Autor1: Isabella Schön
Autor2: Leon Budimovic

Kapitel 29 Aufgabe 5

Quellen:
 - die Codes von den Aufgaben davor
 - Internet bzw. Terminal - manual page für measurement
 - Folien von Semester 2 für Queue
 - Buch
*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <assert.h>
#define BILLION  1000000000

typedef struct __node_t {
    int value;
    struct __node_t *next;
} node_t;

    
typedef struct __queue_t {
    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock, tail_lock;
} queue_t;


typedef struct __myargs_t {
    struct __queue_t *pointer;
    int id;
} myargs_t;



void Queue_Init(queue_t *q) {
    node_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    q->head = q->tail = tmp;
    pthread_mutex_init(&q->head_lock, NULL);
    pthread_mutex_init(&q->tail_lock, NULL);
}


void Queue_Enqueue(queue_t *q, int value) {
    node_t *tmp = malloc(sizeof(node_t));
    assert(tmp != NULL);
    tmp->value = value;
    tmp->next  = NULL;
    
    //das Ende wird um eins verlängert
    pthread_mutex_lock(&q->tail_lock);
    q->tail->next = tmp;
    q->tail = tmp;
    pthread_mutex_unlock(&q->tail_lock); 
}


int Queue_Dequeue(queue_t *q, int *value) {
    pthread_mutex_lock(&q->head_lock);
    node_t *tmp = q->head;
    node_t *new_head = tmp->next;
    if (new_head == NULL) {
        pthread_mutex_unlock(&q->head_lock);
        return -1; // queue was empty
    }
    *value = new_head->value;
    q->head = new_head;
    pthread_mutex_unlock(&q->head_lock);
    
    free(tmp);
    return 0;
}


struct timespec *diff_time (struct timespec before, struct timespec after, struct timespec *result) {
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


void *enquethread(void *args) {
    myargs_t *p = (myargs_t *) args;
    Queue_Enqueue(p->pointer, p->id);
    return NULL;
}

void *dequethread(void *args) {
    myargs_t *p = (myargs_t *) args;
    int *result = (int*) malloc(sizeof(int));
    Queue_Dequeue(p->pointer, result);
    return NULL;
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

    queue_t queue;
    Queue_Init(&queue);
    myargs_t args[numthreads];
    for(int i = 0; i < numthreads; i++)
    {
        args[i].pointer = &queue;
        args[i].id = 0;
    }


    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
    for(int i = 0; i < numthreads; i++) {
        pthread_create(&thread[i], NULL, enquethread, &args[i]);
    }
    for(int i = 0; i < numthreads; i++) {
        pthread_join(thread[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    diff_time(begin, end, &result);
    unsigned long time_en = result.tv_sec * BILLION + result.tv_nsec;
    printf("Measured time Enqueue: %lu ns \n", time_en);
    printf("Measured time Enqueue: %lu microsec \n", time_en/1000);


    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
    for(int i = 0; i < numthreads; i++) {
        pthread_create(&thread[i], NULL, dequethread, &args[i]);
    }
    for(int i = 0; i < numthreads; i++) {
        pthread_join(thread[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);


    diff_time(begin, end, &result);
    unsigned long time_de = result.tv_sec * BILLION + result.tv_nsec;
    printf("Measured time Dequeue: %lu ns \n", time_de);
    printf("Measured time Dequeue: %lu microsec \n", time_de/1000);


    return 0;
}