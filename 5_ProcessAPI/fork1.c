//Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) 
//and set its value to something (e.g., 100). What value is the variable in the child process? 
//What happens to the variable when both the child and parent change the value of x?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char **argv) {
    int x = 100;

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        printf("I am the child (pid: %d) with the value x: %d \n", (int) getpid(), x);
         x = 20;
        printf("I am the child (pid: %d) with the new value x: %d \n", (int) getpid(), x);
    } else {
        printf("I am the parent (pid: %d) with the value x: %d \n", (int) getpid(), x);
        x = 405;
        printf("I am the parent (pid: %d) with the new value x: %d \n", (int) getpid(), x);
    } 
    printf("final value %d", x);
    return 0;

}