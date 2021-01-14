#include <stdio.h>

int main() {
    int i = 3, *j, k;
    printf("%d\n",i);
    //printf("%d\n",k);
    printf("%d\n",*j);
    j = &i;
    printf("%d\n",*j);
    printf("%d\n", i**j*i+*j);

    printf("%s\n", "neues testen");

    char str[20] = "Hello";
    printf("%s\n", str);
    char *p = str;
    printf("%c\n", *p);
    *p = 'M';
    printf("%s\n", str);





   return 0;
}