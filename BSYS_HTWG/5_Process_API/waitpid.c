//Write a slight modiﬁcation of the previous program, this time using waitpid() instead of wait().
//When would waitpid() be useful?


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
        printf("Hi I am Child with (pid:%d)\n", (int) getpid());
        //int rc_waitpid = waitpid(rc, NULL, 0);
        //printf("Hi I am Child and always wait for parent (rc_waitpid:%d)\n", rc_waitpid);
    } else {
        int rc_waitpid = waitpid(-1, NULL, 0);
        printf("Hi I am Parent and always wait for child (rc_waitpid:%d)\n", rc_waitpid);
        //printf("Hi I am Parent with (pid:%d)\n", (int) getpid());
    }

    return 0;
}