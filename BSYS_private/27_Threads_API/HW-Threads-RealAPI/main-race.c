/*#include <stdio.h>

#include "mythreads.h"

int balance = 0;

void* worker(void* arg) {
    balance++; // unprotected access 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    balance++; // unprotected access
    Pthread_join(p, NULL);
    return 0;
}*/
#include <stdio.h>

#include "mythreads.h"

int balance = 0;


void* worker(void* arg) {
    //pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    //pthread_mutex_t *argLock = (pthread_mutex_t *) arg;
    //pthread_mutex_lock(&mutex);
    balance++; // unprotected access 
    //pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    Pthread_create(&p, NULL, worker, NULL);
    pthread_mutex_lock(&mutex);
    balance++; // unprotected access
    pthread_mutex_unlock(&mutex);
    Pthread_join(p, NULL);
    return 0;
}
