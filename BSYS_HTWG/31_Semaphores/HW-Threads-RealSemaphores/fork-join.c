#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"
#include <semaphore.h>

sem_t s; 

void *child(void *arg) {
    printf("child\n");
    // use semaphore here
    sleep(1); //es wird sichergestellt, dass child dran ist
    sem_post(&s); //child -> sem++ -> sem=1
    
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init semaphore here
    sem_init(&s, 0, 0); //value semaphore = 0
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s); //parent -> sem==0 -> schlafen
    printf("parent: end\n");
    return 0;
}

