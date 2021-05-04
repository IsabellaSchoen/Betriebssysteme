#include <stdlib.h>
#include <stdio.h>

int main() {

    int i, n;
    printf("Please enter a number: ");
    scanf("%d", &n); //& -> address of n
    int *ptr = (int *) malloc(n*sizeof(int)); //3 * 4bytes = 12 bytes gesamt
    //ptr zeigt auf den ersten integer wert
    //da es insgesamt drei integers sind, sieht es wie folgt aus:
    //1000-1003 = 4byte
    //1004-1007 = 4byte
    //1008-1011 = 4byte

    if (ptr == NULL){
        printf("Memory not availabe.");
        exit(1);
    }

    for(i = 0; i<n; i++) {
        printf("Enter an integer: ");
        scanf("%d", ptr + i); //weil prt auf das erste integer zeigt und int 4 byte hat
        //ptr gibt uns schon die Adresse, weil es ein pointer ist
    }

    for(i=0; i<n; i++) {
        printf("%d \n", *(ptr + i)); //* -> value <- dereference
    }

    //free(prt);
    return 0;
}