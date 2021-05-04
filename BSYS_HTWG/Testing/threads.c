#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit() {
    printf("now the exit\n");
    pthread_mutex_lock(&m);
    printf("first exit\n");
    done = 1;
    printf("second exit\n");
    pthread_cond_signal(&c);
    printf("third exit\n");
    pthread_mutex_unlock(&m);
}

void *child(void *arg) {
    printf("now the child\n");
    printf("child\n");
    printf("first child\n");
    thr_exit();
    printf("second child\n");
    return NULL;
}

void thr_join() {
    printf("now the join\n");
    pthread_mutex_lock(&m);
    printf("first join\n");
    while(done == 0){
        printf("second join\n");
        pthread_cond_wait(&c, &m);
        printf("third join\n");
    }
    pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    pthread_t p;
    pthread_create(&p, NULL, child, NULL);
    printf("first: between create and join\n");
    thr_join();
    printf("after join\n");
    printf("parent: end\n");
    return 0;
}