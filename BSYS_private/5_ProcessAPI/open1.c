//Write a program that opens a ﬁle (with the open() system call) and then calls fork() to create a new process. 
//Can both the child and parent access the ﬁle descriptor returned by open()? What happens when they are writing 
//to the ﬁle concurrently, i.e., at the same time?


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int op = open("./textfile1.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU); //a texfile - empty or not - is opened
    char *child = "I am child and will run at first\n";
    char *parent = "I am parent and will wait for the child\n";


    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        write(op, child, strlen(child));
    } else {

        write(op, parent, strlen(parent));
    }


    return 0;
}
