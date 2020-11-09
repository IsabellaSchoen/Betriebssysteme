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

    
    printf("hello world (PID:%d)\n", (int) getpid()); //getpid(): getting the processID

    int doc = open("open_document.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    char *child = "I am the child\n";
    char *parent = "I am the parent\n";


    int forkc = fork(); //child is created

    if(forkc < 0) 
    {
        fprintf(stderr, "fail\n");
        exit(1);
    } else if (forkc == 0)
    {
        write(doc, child, strlen(child));
        printf("child (PID:%d)\n", (int) getpid());
    } else {
        write(doc, parent, strlen(parent));
        printf("parent of %d (PID:%d)\n", forkc, (int) getpid());
    }
    close(doc);
    return 0;
}