#include <stdio.h>
#include <string.h>

#define L 3
#define C 20

int tamanho(char vetor[])
{
    int cont = 0;
    while (vetor[cont] != '\0')
    {
        cont++;
    }
    return cont;
}

void maior(char matriz[L][C], char *resultado)
{
    int i = 0;
    int maior_tamanho = tamanho(matriz[i]);
    strcpy(resultado, matriz[i]);

    for (i = 1; i < L; i++)
    {
        int tam = tamanho(matriz[i]);
        if (tam > maior_tamanho)
        {
            maior_tamanho = tam;
            strcpy(resultado, matriz[i]);
        }
    }
}

int comecaComVogal(char str[])
{
    if (str[0] == '\0')
    {
        return 0;
    }

    char primeira_letra = str[0];
    char vogais[] = "AEIOUaeiou";

    for (int i = 0; vogais[i] != '\0'; i++)
    {
        if (primeira_letra == vogais[i])
        {
            return 1;
        }
    }

    return 0;
}

int contaVogaisIniciais(char matriz[L][C], int linha)
{
    if (linha == L)
    {
        return 0;
    }

    int contador = contaVogaisIniciais(matriz, linha + 1);

    if (comecaComVogal(matriz[linha]))
    {
        contador++;
    }

    return contador;
}

void stringsComTamanhoEInicialMaiuscula(char matriz[L][C], char resultado[L][C], int *posicao, int linha)
{
    if (linha == L)
    {
        return;
    }

    if (tamanho(matriz[linha]) >= 4 && matriz[linha][0] >= 'A' && matriz[linha][0] <= 'Z')
    {
        strcpy(resultado[(*posicao)++], matriz[linha]);
    }

    stringsComTamanhoEInicialMaiuscula(matriz, resultado, posicao, linha + 1);
}

int main(void)
{
    char matriz[L][C] =
    {
        "Casa", "UFPI", "Trabalho"
    };

    printf("Tamanhos das strings:\n");
    for (int i = 0; i < L; i++)
    {
        printf("%s -> %d\n", matriz[i], tamanho(matriz[i]));
    }

    char resultado_maior[C];
    maior(matriz, resultado_maior);
    printf("\nMaior string = %s\n", resultado_maior);

    int contador_vogais = contaVogaisIniciais(matriz, 0);
    printf("\nQuantidade de strings que iniciam com vogal: %d\n", contador_vogais);

    char resultado_strings_maiusculas[L][C];
    int posicao = 0;
    stringsComTamanhoEInicialMaiuscula(matriz, resultado_strings_maiusculas, &posicao, 0);

    printf("\nStrings com tamanho >= 4 e iniciais maiúsculas:\n");
    for (int i = 0; i < posicao; i++)
    {
        printf("%s\n", resultado_strings_maiusculas[i]);
    }

    return 0;
}
