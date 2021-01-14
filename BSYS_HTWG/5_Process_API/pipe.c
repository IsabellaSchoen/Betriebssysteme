#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

//int pipe(int fd[2]);
//pipefd[0] -> read
//pipefd[1] -> write

int main(){
    char readbuffer[80];
    //char string[] = "Child1 und Child2 tauschen sich aus";
    int fd[2]; //um read und write von der pipe zu bestimmen

    if(pipe(fd) < 0){
        exit(1);
    }

    int child1 = fork(); //erstes Kind wird erstellt
    int child2 = fork(); //zweites Kind wird erstellt

    if(child1 < 0)
    {
        fprintf(stderr, "child1 failed\n");
        exit(1);
    } 
    else if (child1 == 0) //erstes Kind - hier nur write() möglich
    {
        //von child1 wird output benötigt, somit soll nur schreiben können
        printf("child1 starts:\n");
        close(fd[0]); //input wird geschlossen, damit nur schreiben möglich ist, lesen somit nicht mehr
        dup2(fd[1],1); //stdout to pipe bzw. child2 - es findet somit ein Verbung von output und input statt
        printf("Sending message of child1 to pipe\n");
    } 
    else //zweites Kind
    {
        if (child2 < 0) {
            fprintf(stderr, "child2 failed\n");
            exit(1);
        } 
        else if (child2 == 0)
        {
            printf("child2 starts:\n");
            close(fd[1]);//output wird geschlossen, damit nur lesen möglich ist, schreiben somit nicht mehr
            dup2(fd[0], 0);//stdin to pipe bzw. child1
            //read(STDIN_FILENO, buffer, 80);
            read(fd[0], readbuffer, sizeof(child1)); //hier findet nun statt, dass child2 von child1 liest
            //read(fd[0], readbuffer, strlen(string) + 1);
            printf("Received message: %s\n", readbuffer);
        } 
        else 
        {
            int wc = wait(NULL); //parent has to wait for children
            printf("parent and wc:%d\n", wc);
        }
    }

    return 0;
}