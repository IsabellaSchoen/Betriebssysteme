//using fork()


#include <stdlib.h> //size_t
#include <stdio.h> //printf()
#include <unistd.h>


int main(int argc, char *argv[])
{


    printf("hello world (PID:%d)\n", (int) getpid()); //getpid(): getting the processID

    int x;
    x= 100;
    printf("value x at the beginning: %d\n", x);

    int child = fork(); //child is created

    //now we ask if the child is created - yes:print, no:parent or error

    if(child < 0) 
    {
        //fork() failed
        fprintf(stderr, "fail\n");
        exit(1);
    } else if (child == 0)
    {
        //child is created
        x= 800;
        printf("child (PID:%d) with value x:%d\n", (int) getpid(), x);
    } else {
        //parent prints
        x = 500;
        printf("parent of %d (PID:%d) with value x:%d\n", child, (int) getpid(), x);
    }

    return 0;
}

