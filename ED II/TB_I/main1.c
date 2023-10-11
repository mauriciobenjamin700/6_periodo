#include <stdio.h>
#include "tad.c"

int main()
{
    struct Serie *s;
    int sinal;

    iniciarS(s);

    sinal = cadastrarS(&s);
    
    if(sinal)
    {
        printf("\nCadastrei a serie!");
    }
    else
    {
        printf("\nNao cadastrei a serie");
    }

    mostarS()

    free(s); 
    printf("\nliberei\n");

    return 0;
}