#include <stdlib.h>
#include <stdio.h>


int main()
{

    typedef struct _node_t {
        int size;
        struct _node_t *next;
    } node_t;

    printf("Bytes: %d\n", sizeof(node_t));

    return 0;
}