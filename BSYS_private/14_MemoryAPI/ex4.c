//allocate memory using malloc()
//forget to free before exiting


#include <stdlib.h>

int main(void) {

    int *point = (int*) malloc(sizeof(int));
    //int i = 5;
    //*point = i;
    return 0;
}