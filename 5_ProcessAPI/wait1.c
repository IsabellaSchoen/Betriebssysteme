//Now write a program that uses wait() to wait for the child process to ﬁnish in the parent. 
//What does wait() return? What happens if you use wait() in the child?


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        int rc_wait = wait(NULL);
        printf("Hi I am Child and always wait for parent (rc_wait:%d)\n", rc_wait);
        //printf("Hi I am Child with (pid:%d)\n", (int) getpid());
    } else {
        //int rc_wait = wait(NULL);
        //printf("Hi I am Parent and always wait for child (rc_wait:%d)\n", rc_wait);
        printf("Hi I am Parent with (pid:%d) \n", (int) getpid());
    }

    return 0;
}