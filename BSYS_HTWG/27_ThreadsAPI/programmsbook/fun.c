#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    printf("i: %d\n", i);
    int *const p = &i;
    *p = 10;
    int point = *p;
    //printf("*p: %ls\n", p);
    printf("point: %d\n", point);
    //*p = 1;


    return 0;
}