#include <stdlib.h>

int main(void)
{
    int *point = (int*) malloc(sizeof(int));
    int a = 4;
    *point = a;
    return 0;
}