//array of integers
//size of 100 using malloc()
//set data[100] to zeor


#include <stdlib.h>
#include <stdio.h>


int main(void){

    int *data = (int*) malloc(100 * sizeof(int));
    int size = 100;
    data[size] = 0;

    printf("%d\n", *data);

    free(data);

    return 0;
}