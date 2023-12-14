#include <stdio.h>

#define L 4
#define C 20

/*
Faça uma função em C que leia um vetor de string não ordenado e depois faça:
    a) uma função recursiva com pendência que devolva a string de maior tamanho.
    b) uma função recursiva sem pendencia que devolva a quantidade de strings que iniciam com vogal
    c) uma função recursiva que devolva um vetor contendo somente as strings com tamanho >= 4 e que iniciam
    com letra maiúscula.
*/

int ehMaiusculo(char c)
{
    int sinal = 0;

    if (c > 64 && c < 91)
    {
        sinal = 1;
    }

    return sinal;
}

int ehVogal(char c)
{
    char vogais[10] =
        {
            'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

    int sinal = 0;
    int i = 0;

    for (; i < 10; i++)
    {
        if (vogais[i] == c)
        {
            sinal = 1;
        }
    }

    return sinal;
}

int tamanho(char vetor[])
{
    int cont = 0;
    while (vetor[cont] != '\0')
    {
        cont++;
    }
    return cont;
}

int inicialVogal(char matriz[L][C])
{
    int cont = 0;
    int i = 0;
    for (; i < L; i++)
    {
        if (ehVogal(matriz[i][0]))
        {
            cont++;
        }
    }

    return cont;
}

int fC(char matriz[L][C], char valido[L][C])
{
    // controle da matriz
    int i = 0, j;

    // controle da matriz de validos
    int x = 0, y;

    for (; i < L; i++)
    {
        if (tamanho(matriz[i]) >= 4 && ehMaiusculo(matriz[i][0]))
        {
            // Iniciando as colunas da matriz de validos em 0
            y = 0;
            j = 0;
            while (matriz[i][j] != '\0')
            {
                // Copiando os caracteres de uma string valdia da matriz original para a matriz de valido
                valido[x][y] = matriz[i][j];

                y++;
                j++;

                // Atualizando as posições
            }

            // Pulando para a proxima linha do vetor
            x++;
        }
    }
    return x;
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
    int i = 0;
    char *maior;
    maior = matriz[i];
    for (i = 1; i < L; i++)
    {
        if (tamanho(maior) < tamanho(matriz[i]))
        {
            maior = matriz[i];
        }
    }
    printf("\nA) Maior String: %s\n", maior);
}

int main(void)
{
    char matriz[L][C] =
        {
            "Casa", "Viajem", "Trabalho", "Aves"
        };

    char validos[L][C];

    int quantidade_validos;

    int i;

    maior(matriz);

    printf("B) Quantidade que iniciam com vogal: %d\n", inicialVogal(matriz));

    quantidade_validos = fC(matriz, validos);

    printf("\n\nItens Validos: %d -> [>=4 and upper()]\n", quantidade_validos);

    for (i = 0; i < quantidade_validos; i++)
    {
        printf("%s = %d\n", validos[i], tamanho(validos[i]));
    }

    return 0;
}
