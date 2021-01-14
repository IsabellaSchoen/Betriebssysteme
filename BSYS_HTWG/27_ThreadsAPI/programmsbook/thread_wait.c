#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include "common_threads.h"

typedef struct {
    int a;
    int b;
} myarg_t;

typedef struct {
    int x;
    int y;
} myret_t;

void *mythread(void *arg) {
    myarg_t *value = (myarg_t *) arg;
    printf("a: %d b: %d\n", value->a, value->b);

    myret_t *r = malloc(sizeof(myret_t));
    assert(r != NULL);
    r->x = 1;
    r->y = 2;
    return (void *) r;

    //return (void *) value;
    //a: 10 b: 20
    //x: 10 y: 20

}

int main(int argc, char *argv[]) {
    pthread_t p;
    myret_t *join;
    //myarg_t args = { 10, 20 };
    myarg_t args;
    args.a = 10;
    args.b = 20;

    pthread_create(&p, NULL, mythread, &args);
    pthread_join(p, (void **) &join);

    printf("x: %d y: %d\n", join->x, join->y);

    //free(join);
    return 0;
}