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

    //Versuch1
/*
    int child = fork(); //child is created

    if(child < 0) 
    {
        fprintf(stderr, "fail\n");
        exit(1);
    } else if (child == 0)
    {
        //int wc = wait(NULL);
        //printf("child (wait:%d) \n", wc);

        printf("child mit %d pid \n", getpid());

    } else 
    {
        int wc = wait(NULL);
        printf("parent with PID:%d and wc:%d\n", (int) getpid(), wc);
        //für wait() bekommen wir den value = -1
        //somit hat der parent nicht auf das child gewartet

        //printf("parent\n");
    }
    //resultat:
    //child mit 2205 pid 
    //parent with PID:2204 and wc:2205
*/





    //Versuch2 - gelingt nicht

    int retval = fork(); //child is created

    if(retval < 0) 
    {
        fprintf(stderr, "fail\n");
        exit(1);
    } else if (retval == 0) {
        printf("child with %d pid and value %d \n", getpid(), retval);

    } else {
        //printf("value of fork: %d\n", retval);
        int value = retval;
        //printf("value of value: %d\n", value);
        wait(&value);
        //wait(value);
        printf("parent with pid %d and value %d\n", (int) getpid(), retval);
        //printf("parent");
    }

    //child with 2362 pid and value 0 
    //parent with pid 2361 and value 2362





    return 0;
}