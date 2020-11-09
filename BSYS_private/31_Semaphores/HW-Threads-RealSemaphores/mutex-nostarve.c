#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef __ns_mutex_t {
    sem_t lock;
} ns_mutex_t;

ns_mutex_t ns_mutex;

void ns_mutex_init(ns_mutex_t *m) { //Initialisierung
    sem_init(&m->lock);
}

void ns_mutex_acquire(ns_mutex_t *m) { //Anfrage auf Lock
    sem_wait(&m->lock);
}

void ns_mutex_release(ns_mutex_t *m) { //Lösen
    sem_post(&m->lock);
}


void *worker(void *arg) {
    ns_mutex_acquire(&ns_mutex);
    printf("Worker is working\n");
    ns_mutex_release(&ns_mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    assert(argc == 2); //assert -> to verify (=prüfen) number of arguments
    int nums = atoi(argv[1]);
    ns_mutex_init(&ns_mutex);
    Pthread_create pc[nums];

    printf("parent: begin\n");

    int i;
    for (i = 0; i < nums; i++)
	Pthread_create(&pc[i], NULL, worker, NULL);

    for (i = 0; i < nums; i++)
	Pthread_join(pc[i], NULL);


    printf("parent: end\n");
    return 0;
}

