#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{

    if(argc < 3)
    {
        fprintf(stderr, "call: programm, size of bytes, time for the program ");
        return 1;
    }

    printf("PID: %d\n",getpid());

    int memorySize = atoi(argv[1]) * 1000000; //bytes into megabytes - the number of MB of memory the program will use

    int amountOfTime = atoi(argv[2]); //certain amount of time

    
    //alloc(nitems, size)
    //nitems − This is the number of elements to be allocated.
    //size − This is the size of elements.

    //wenn wir free laufen lassen in der Konsole in der VM, dann wird uns eine Tabelle mit free und used memory gezeigt
    //dies passiert hier nun auch, indem wir eine bestimmte Anzahl von memory allokieren und durch die uns angegbene
    //Tabelle dann gehen und jeden Eintrag von dieser berühren, dies passiert im Folgenden:

    char *array = (char*) calloc(memorySize, sizeof(char)); //allocating array and stream through it and touching each entry
    if(array == NULL)
    {
        fprintf(stderr, "failed to allocate bytes");
        return 1;
    } else
    {
        for(int i = 0; i < sizeof(array); i++)
        {
            printf("Entry: %d\n", array[i]);
        }
    }
    

    printf("allocated bytes of memory: %d\n", memorySize);

    sleep(amountOfTime); //touching happens for a certain amount of time

    free(array);

    return 0;
}