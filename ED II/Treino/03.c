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

int ehVogal(char c)
{
    char vogais[10] = 
    {
        'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'
    };

    int sinal = 0;
    int i = 0;

    for(;i<10;i++)
    {
        if(vogais[i]==c)
        {
            sinal = 1;
        }
    }

    return sinal;
    
}

int tamanho(char vetor[])
{
    int cont=0;
    while (vetor[cont]!= '\0')
    {
        cont++;
    }
    return cont;
}

int vogal(char matriz[][])
{
    int cont = 0;
    int i=0;
    if (matriz[i][0] != '\0')
    {
        cont++;
    }
    return cont;
}
/*
int tamanho(char vetor[])
{
    int cont=0;
    while (vetor[cont]!= '\0')
    {
        cont++;
    }
    return cont;
}
*/
void maior(char matriz[L][C])
{
    int i=0;
    char *maior;
    maior = matriz[i];
    for(i=1;i<L;i++)
    {
        if(tamanho(maior) < tamanho(matriz[i]))
        {
            maior = matriz[i];
        }
    }
    printf("\nMaior = %s\n", maior);
}

int main(void)
{
    char matriz[L][C] = 
    {
        "Casa", "UFPI", "Trabalho"
    };

    int i;
    for (i = 0; i < L; i++)
    {
        printf("\nTamanho da string %s -> %d\n", matriz[i],tamanho(matriz[i]));
    }

    maior(matriz);

    return 0;
}
