#Isabella Schön
#Leon Budimovic
#Gruppen-Nr.: 22

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#define BILLION  1000000000



int main(int argc, char *argv[])
{

    if(argc < 3)
    {
        fprintf(stderr, "FAILURE: too less arguments\n");
        return 1;
    }

    int NUMPAGES = atoi(argv[1]);
    //printf("Number of Pages: %d\n", NUMPAGES);
    int NUMTRIALS = atoi(argv[2]);
    //printf("Number of Processes: %d\n", NUMTRIALS);
    int PAGESIZE = getpagesize();

    int *a = (int *) calloc(PAGESIZE * NUMPAGES, sizeof(int));

    int jump = PAGESIZE/sizeof(int);

    struct timespec begin;
	struct timespec end;


    clock_gettime(CLOCK_REALTIME, &begin);
    for(int j = 0; j < NUMTRIALS; j++) //count how many processes
    {
        for(int i = 0; i < NUMPAGES * jump; i += jump) //updating the number of pages in array
        { }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    unsigned long accessing = (end.tv_sec - begin.tv_sec) * BILLION + end.tv_nsec - begin.tv_nsec;
    //printf("Time to access the array: %ld\n", accessing);


    clock_gettime(CLOCK_REALTIME, &begin);
    for(int j = 0; j < NUMTRIALS; j++) //count how many processes
    {
        for(int i = 0; i < NUMPAGES * jump; i += jump) //updating the number of pages in array
        { 
            a[i] += 1; 
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    unsigned long time = (end.tv_sec - begin.tv_sec) * BILLION + end.tv_nsec - begin.tv_nsec - accessing;
    //printf("Time to access the pages: %ld\n", time);

    unsigned long endtime = time / (NUMPAGES * NUMTRIALS);
    //unsigned long endtime = time / NUMPAGES;

    printf("%lu", endtime);



    free(a);
    return 0;
}