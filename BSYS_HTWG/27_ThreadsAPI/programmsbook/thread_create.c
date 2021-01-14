#include <assert.h>
#include <stdio.h>
#include <pthread.h>

/*struct myarg_t{
    int a;
    int b;
};*/


typedef struct {
    int a;
    int b;
} defi;

void *mythread(void *arg) {
    //struct myarg_t *value = (struct myarg_t *) arg;
    defi *value = (defi *) arg;
    printf("%d %d\n", value->a, value->b);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    //myarg_t args = { 10, 20 };
    //struct myarg_t args;
    defi args;
    args.a = 10;
    args.b = 20;

    int rc = pthread_create(&p, NULL, mythread, &args);
    assert(rc == 0);

    (void) pthread_join(p, NULL);
    
    printf("fertig\n");
    return 0;
}