



#include <stdlib.h>
#include <stdio.h>


int main(void){

    int *data = (int*) malloc(100 * sizeof(int));
    int size = 100;
    data[size] = 0;

    free(data);

    printf("%d\n", data[0]);

    return 0;
}