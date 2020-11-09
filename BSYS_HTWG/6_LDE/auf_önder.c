//measure cost of context switch and system call
#define _GNU_SOURCE
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sched.h>
#include <string.h>
#define loop 100000
#define BILLION  1000000000

int main() 
{

//-------------------------------------------------------------------------measure system call

    struct timespec start_sc, end_sc;

    clock_gettime(CLOCK_REALTIME, &start_sc);
    for(int i = 0; i < loop; i++)
    {
        clock_gettime(CLOCK_REALTIME, &end_sc);
    }
    clock_gettime(CLOCK_REALTIME, &end_sc);
    printf("Time of the system call nr. 1: %f ns\n", (float) ((end_sc.tv_sec - start_sc.tv_sec) * BILLION + (end_sc.tv_nsec -      start_sc.tv_nsec)) / loop);
    

    struct timespec start_loop, end_loop;

    clock_gettime(CLOCK_REALTIME, &start_loop);
    for(int i = 0; i < loop; i++) { }
    clock_gettime(CLOCK_REALTIME, &end_loop);
    printf("Time of the system call nr. 2: %f ns\n", (float) ((end_loop.tv_sec - start_loop.tv_sec) * BILLION + (end_loop.tv_nsec - start_loop.tv_nsec)) / loop);


     printf("Time of the system call final: %f ns\n", ((float) ((end_sc.tv_sec - start_sc.tv_sec) * BILLION + (end_sc.tv_nsec -  start_sc.tv_nsec)) / loop) - ((float) ((end_loop.tv_sec - start_loop.tv_sec) * BILLION + (end_loop.tv_nsec - start_loop.tv_nsec)) / loop));




//--------------------------------------------------------------------------measure context switch
    //two process on the CPU
    //two UNIX pipes between them
    //pipe -> communication
    //first process: issues write to first pipe, waits for read on second pipe
    //first process: when waiting for read OS puts first process in blocked state
    //second process: reads form first pipe, blocks -> back-and-forth cycle of communicate
    //


    //parent and child would work:

    //The cpu_set_t data structure represents a set of CPUs. 
    //CPU sets are used by sched_setaffinity(2) and similar interfaces. 






    struct timespec start,end;
    cpu_set_t set;
    CPU_ZERO(&set); //Clears set, so that it contains no CPUs. 
    CPU_SET(0, &set); //0 = Kern eines CPUs //Add CPU cpu to set. 


    int pipefd_first[2], pipefd_second[2];
    if (pipe(pipefd_first) == -1) 
    {
      perror("pipe first failed");
      exit(1);
    }
    if (pipe(pipefd_second) == -1) 
    {
      perror("pipe second failed");
      exit(1);
    }



    int child = fork();

    if(child < 1) 
    {
        fprintf(stderr, "error\n");
        exit(1);
    } else if (child == 0) //child - 2.Prozess
    {
        if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) 
        {
            exit(1);
        }

        //clock_gettime(CLOCK_REALTIME, &start);
        for (int i = 0; i < loop; i++) 
        {
            read(pipefd_first[0], NULL, 0);
            write(pipefd_second[1], NULL, 0);
        }
        //clock_gettime(CLOCK_REALTIME, &end);
        
    } else //parent - 1. Prozess
    {
         if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
            exit(1);
        }

        clock_gettime(CLOCK_REALTIME, &start);
        for (int i = 0; i < loop; i++) 
        {
            write(pipefd_first[1], NULL, 0);
            read(pipefd_second[0], NULL, 0);
        }
        clock_gettime(CLOCK_REALTIME, &end);

        printf("Context Switch: %f ns\n", ((float) ((end.tv_sec - start.tv_sec) * BILLION 
            + (end.tv_nsec - start.tv_nsec)) / loop));
    }


    return 0;
}





//___________________________________________________________________________notes
    //system call = switch from user to kernel
    //zb read(), write(), open()
    //timer: gettimeofday() = int gettimeofday ( struct timeval *tp ,  struct timezone *tz )
    //clock_gettime(); --> gettimeofday is bad

    //int doc = open("open_document.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    //char *new = "Hello, this is the new text";

    //write(doc, new, strlen(new));
    //write(doc,NULL,0);

    //printf("Time of the system call: %f ns\n", (float) ((((float)end.tv_nsec - (float)start.tv_nsec) + ((float)end.tv_sec - (float)start.tv_sec )) * BILLION)/loop);
    //printf("time: %f ns\n", (float) (end.tv_sec * BILLION + end.tv_nsec - start.tv_sec * BILLION - start.tv_nsec)/loop);

    //close(doc);

