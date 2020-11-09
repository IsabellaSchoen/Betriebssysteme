//open() and fork()



#include <stdlib.h> //size_t
#include <stdio.h> //printf()
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[])
{

    int child = fork(); //child is created

    if(child < 0) 
    {
        fprintf(stderr, "fail\n");
        exit(1);
    } else if (child == 0)
    {
        printf("hello\n");
    } else 
    {
        sleep(1);
        printf("goodbye\n");
    }

    return 0;
}