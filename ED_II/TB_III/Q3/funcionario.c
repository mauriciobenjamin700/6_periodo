#include <stdio.h>
#include <stdlib.h>
#define MATRICULA 6

typedef struct Funcionario
{
    char matricula[MATRICULA];
    char nome[50];
    char funcao[50];
    float salario;


}Funcionario;

/*
Etapa 1 - rotação de 2 dígitos para a esquerda 
Etapa 2 - depois extrai o 2, 4 e 6 dígitos e 
Etapa 3 - obtenha o resto da divisão pelo tamanho do vetor destino. 
Etapa 4 - As colisões devem ser tratadas somando ao resto da divisão o primeiro dígito da matrícula. 
*/
int hash_a(char matricuta[], int tam_vetor)
{
    char aux[MATRICULA];
    int i,j=2;

    //Etapa 1
    aux[0] = matricuta[MATRICULA-2];
    aux[1] = matricuta[MATRICULA-1];
    for (i=0;i<MATRICULA-2;i++)
    {
        aux[j]=matricuta[i];
        j++;
    }

    //Etapa 2

    char digitos[4] =  {aux[1], aux[3], aux[5], '\0'};

    // Converte a string para um valor inteiro
    int valorInteiro = atoi(digitos);

    //Etapa 3

    return valorInteiro % tam_vetor;
}