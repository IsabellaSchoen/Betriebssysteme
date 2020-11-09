//Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. 
//See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), 
//execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {

        char *ls = "ls";
        char *myargs[2];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = NULL;


        //execl();
        //execle();
        //execlp();
        //execv();
        execvp(ls, myargs);
        //execvpe();

    } else { }

    return 0;
}