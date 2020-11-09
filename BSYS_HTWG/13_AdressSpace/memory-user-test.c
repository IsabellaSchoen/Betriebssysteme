#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{

    if(argc < 3)
    {
        fprintf(stderr, "call: programm, size of bytes, time for the program ");
        return 1;
    }

    printf("PID: %d\n",getpid());

    int alloc = atoi(argv[1]) * 1000000 ;

    int time = atoi(argv[2]);

    char *bytes = (char*) calloc(alloc, sizeof(char));

    for (int i = 0; i < alloc; i++) {
        bytes[i] = 1;
    }



    if(bytes == NULL)
    {
        fprintf(stderr, "failed to allocate bytes");
        return 1;
    }

    printf("old bytes: %d\n", alloc);

    sleep(time);

    free(bytes);

    return 0;
}
