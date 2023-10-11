#include <stdio.h>
#include "tad.c"

int main()
{
    struct Serie *s;

    if (iniciarS(s)==1) 
        printf("\ndeu certo");

    free(s); 
    printf("\nliberei\n");

    return 0;
}