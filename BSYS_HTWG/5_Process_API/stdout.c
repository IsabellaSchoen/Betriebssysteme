//Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO).
//What happens if the child calls printf() to print some output after closing the descriptor?


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        close(STDOUT_FILENO);
        printf("Hi I am Child with (pid:%d)\n", (int) getpid());
    } else {
        printf("Hi I am Parent with (pid:%d)\n", (int) getpid());
    }

    return 0;

/*
The following symbolic constants shall be defined for file streams:

STDERR_FILENO
    File number of stderr; 2.
STDIN_FILENO
    File number of stdin; 0.
STDOUT_FILENO
    File number of stdout; 1.
*/

}

