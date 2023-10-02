#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define L 4
#define C 20

/*
Faça uma função em C que leia um vetor de string não ordenado e depois faça:
    a) uma função recursiva com pendência que devolva a string de maior tamanho.
    b) uma função recursiva sem pendencia que devolva a quantidade de strings que iniciam com vogal
    c) uma função recursiva que devolva um vetor contendo somente as strings com tamanho >= 4 e que iniciam
    com letra maiúscula.
*/

int fA(char matriz[L][C], int maior, int idx)
{
    if (idx <= L)
    {

        if (strlen(matriz[idx]) > strlen(matriz[maior]))
        {
            maior = idx;
        }

        maior = fA(matriz, maior, idx + 1);
    }

    return maior;
}

int ehVogal(char c)
{
    c = toupper(c);
    switch (c)
    {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':

        return 1; // É uma vogal

    default:

        return 0; // Não é uma vogal
    }
}

void fB(char matriz[L][C], int idx, int *qtd)
{
    if (idx < L)
    {
        if (ehVogal(matriz[idx][0]))
        {
            (*qtd)++;
        }
        fB(matriz, idx + 1, qtd);
    }
}

void fC(char matriz[L][C], char vetor[L][C], int idx, int *idx_vetor)
{
    if (idx < L)
    {
        if (strlen(matriz[idx]) >= 4 && isupper(matriz[idx][0]))
        {
           
            strcpy(vetor[idx], matriz[*idx_vetor]);
            (*idx_vetor)++;
        }

        fC(matriz, vetor, idx + 1, idx_vetor);
    }
}

int main(void)
{

    char matriz[L][C] =
        {
            "Casa", "Viajem", "Trabalho", "aaves"};

    char validos[L][C];

    int total_vogais = 0;

    printf("\nA) Maior String %s", matriz[fA(matriz, 0, 0)]);

    fB(matriz, 0, &total_vogais);
    printf("\nB) Quantidade de strings que começam com vogais: %d", total_vogais);

    int i = 0, idx_validos = 0;

    fC(matriz, validos, 0, &idx_validos);
    printf("\nC) strings com tamanho >= 4 e que iniciam com letra maiúscula: ");

 
    while (i<idx_validos)
    {
        printf("\n\t%s",validos[i]);
        i++;
    }
 
    return 0;
}