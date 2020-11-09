#include <stdlib.h>
#include <stdio.h>


int main(void) {

    int *pointer = (int*) malloc(sizeof(int));
    pointer = NULL;
    printf("%d\n", *pointer);
    free(pointer);
    return 0;
}