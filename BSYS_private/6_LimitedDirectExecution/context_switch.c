// cost of a system call = time / number of iterations
// timer - gettimeofday() -> returning time in ms

//cost of context switch -> running two processes on a single CPU
//first: write to the first pipe, waits for a read on the second -> block state and switching to the second
//second: reads from the first 


#include <sys/time.h> //gettimeofday()


int main(int argc , char *argv[])
{




    return 0;
}