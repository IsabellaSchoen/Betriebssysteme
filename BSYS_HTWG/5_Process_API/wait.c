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
        //int wc = wait(NULL);
        //printf("child (wait:%d) \n", wc);

        printf("child\n");

    } else 
    {
        int wc = wait(NULL);
        printf("parent with PID:%d and wc:%d\n", (int) getpid(), wc);

        //printf("parent\n");
    }

    return 0;
}