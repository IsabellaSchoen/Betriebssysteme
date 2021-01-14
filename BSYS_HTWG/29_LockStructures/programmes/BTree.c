/*
Gruppe: 22
Autor1: Isabella Schön
Autor2: Leon Budimovic

Kapitel 29 Aufgabe B-Tree

leider wussten wir die richtige Implementierung nicht....
Deshalb haben wir anbei unsere Idee und dafür die ConcurrentQueue probiert :)

Quellen:
 - Internet bzw. Terminal - manual page für measurement
 - Folien von Semester 2 für B-Tree
 - Buch
 - Stackoverflow
 - GeeksforGeeks
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#define BILLION  1000000000

struct __tree_t {
    int data;
    struct node *left;
    struct node *right;
    pthread_mutex_t lock;
} tree_t;


typedef struct __myargs_t {
    struct __hash_t *pointer;
    int value;
} myargs_t;



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
    B_init(p->value);
    return NULL;
}


void B_init(queue_t *p, queue_t *left, queue_t *right) {
    tree_t *tmp = malloc(sizeof(node_t));
    tmp->next = NULL;
    p->head = tmp;
    p->left = NULL;
    p->right = NULL
    pthread_mutex_init(&p->head_lock, NULL);
}

void B_Insert(tree *p, int child) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->child = child;
    pthread_mutex_init(&new->lock, NULL);
    pthread_mutex_lock(&L->lock);
    .....
    pthread_mutex_unlock(&L->lock);
}

void *mythread(void *args) {
    myargs_t *p = (myargs_t *) args;
    B_Insert(p->pointer, p->value);
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
    tree_t tree; //da node statt listentyp, weil listenkopf node ist

    B_init(&tree);

    myargs_t args[numthreads];
    for(int i = 0; i < numthreads; i++)
    {
        args[i].pointer = tree;
        args[i].value = i;
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