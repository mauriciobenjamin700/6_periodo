#include <stdio.h>

#define L 3
#define C 20

/*
Faça uma função em C que leia um vetor de string não ordenado e depois faça:
    a) uma função recursiva com pendência que devolva a string de maior tamanho.
    b) uma função recursiva sem pendencia que devolva a quantidade de strings que iniciam com vogal
    c) uma função recursiva que devolva um vetor contendo somente as strings com tamanho >= 4 e que iniciam
    com letra maiúscula.
*/

int main(void)
{
    char matriz[L][C] = 
    {
        "Casa", "UFPI", "Trabalho"
    };

    int i;
    for (i = 0; i < L; i++)
    {
        printf("%s\n", matriz[i]);
    }
    return 0;
}
