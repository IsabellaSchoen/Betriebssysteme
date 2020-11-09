#include <stdlib.h>
#include <stdio.h>


int main(void)
{

    int *data = (int*) malloc(10 * sizeof(int));
    int size = 10;
    data[size] = 0;
    free(data);
    printf("%d\n", *data);

    return 0;
}