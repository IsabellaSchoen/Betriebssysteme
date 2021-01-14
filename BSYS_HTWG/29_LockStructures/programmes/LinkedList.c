/*
Gruppe: 22
Autor1: Isabella Schön
Autor2: Leon Budimovic

Kapitel 29 Aufgabe 4

Deadlock - keinen Lösungsweg gefunden

Quellen:
 - die Codes von den Aufgaben davor
 - Internet bzw. Terminal - manual page für measurement
 - Folien von Semester 2 für LinkedList
 - Buch
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#define BILLION  1000000000

typedef struct __node_t {
    int key;
    struct __node_t *next;
    pthread_mutex_t lock;
} node_t;

typedef struct __myargs_t {
    struct __node_t *pointer;
    int id;
} myargs_t;


void node_Init(node_t *node /*list_t *L*/) { //für den Startknoten
    node->next = NULL;
    pthread_mutex_init(&node->lock, NULL); //lock von der gesamten Liste
}


void List_Insert(node_t *L, int key) {
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->key = key; //eine Zahl
    // just lock critical section
    //jedes node hat ein eigenes lock -> freigeben um zur Verwendung
    
    pthread_mutex_lock(&L->lock);
    new->next = L; //neues Element vor den Anfang
    //nochmal anschauen ab hier............
    pthread_mutex_init(&new->lock, NULL); //??
    node_t *oldL = L;
    L = new; //head wir zu dem neuen
    pthread_mutex_unlock(&oldL->lock);
}
        
int List_Lookup(node_t *L, int key) {
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L;
    while (curr) {
        if (curr->key == key) {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
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


void *mythread(void *args) {
    myargs_t *p = (myargs_t *) args;
    List_Insert(p->pointer, p->id);
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
    node_t liste;

    node_Init(&liste);

    myargs_t args[numthreads];
    for(int i = 0; i < numthreads; i++)
    {
        args[i].pointer = &liste;
        args[i].id = 0;
    }


    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);
    for(int i = 0; i < numthreads; i++) {
        pthread_create(&thread[i], NULL, mythread, &args[i]);
    }
    for(int i = 0; i < numthreads; i++) {
        pthread_join(thread[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);


    diff_time(begin, end, &result);
    unsigned long time = result.tv_sec * BILLION + result.tv_nsec;
    printf("Measured time: %lu ns \n", time);
    printf("Measured time: %lu microsec \n", time/1000);


    return 0;
}