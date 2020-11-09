#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

//int pipe(int pipefd[2]);
//pipefd[0] -> read
//pipefd[1] -> write

int main(){
    char buffer[80];
    int pipefd[2];

    if(pipe(pipefd) < 0){
        exit(1);
    }

    int child1 = fork(); //erstes Kind wird erstellt

    if(child1 < 0)
    {
        fprintf(stderr, "child1 failed\n");
        exit(1);
    } else if (child1 == 0)
    {
        //von child1 wird output benötigt, somit soll nur schreiben können
        printf("child1\n");
        close(pipefd[0]); //close input; nicht lesen, nur schreiben
        dup2(pipefd[1],1); //stdout to pipe/child2
        printf("sending message to pipe\n");
    } else //zweites Kind wird erstellt
    {
        int child2 = fork();
        if (child2 < 0) {
            fprintf(stderr, "child2 failed\n");
            exit(1);
        } else if (child2 == 0)
        {
            printf("child2\n");
            close(pipefd[1]);//close output
            dup2(pipefd[0], 0);//stdin to pipe
            //read(STDIN_FILENO, buffer, 80);
            read(pipefd[0], buffer, sizeof(child1));
            printf("received message: %s\n", buffer);
        } else 
        {
            int wc = wait(NULL); //parent has to wait for children
            printf("parent and wc:%d\n", wc);
        }
    }

    return 0;
}