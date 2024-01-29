#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRICULA 6

typedef struct Funcionario
{
    char matricula[MATRICULA];
    char nome[50];
    char funcao[50];
    float salario;

} Funcionario;

typedef struct Tabela_hashing
{
    struct Funcionario funcionario;
    int status; // 0 - Não cadastrado , 1 - Cadastrado
} Tabela_hashing;

typedef struct Retorno
{
    int num_colisoes;
    int resultado; // -1 -> Já cadastrado; 0 -> Tabela cheia; 1 - Cadastado com sucesso
} Retorno;

Tabela_hashing *cria_vetor(int tamanho)
{
    Tabela_hashing t[tamanho];

    for (int i = 0; i < tamanho; i++)
        t[i].status = 0;

    return t;
}

/*
Etapa 1 - rotação de 2 dígitos para a esquerda
Etapa 2 - depois extrai o 2, 4 e 6 dígitos e
Etapa 3 - obtenha o resto da divisão pelo tamanho do vetor destino.
Etapa 4 - As colisões devem ser tratadas somando ao resto da divisão o primeiro dígito da matrícula.

123456
561234
624 % 101
*/
int hash_a(char matricuta[], int tam_vetor)
{
    char aux[MATRICULA];
    int i, j = 2;

    // Etapa 1
    aux[0] = matricuta[MATRICULA - 2];
    aux[1] = matricuta[MATRICULA - 1];
    for (i = 0; i < MATRICULA - 2; i++)
    {
        aux[j] = matricuta[i];
        j++;
    }

    // Etapa 2

    char digitos[4] = {aux[1], aux[3], aux[5], '\0'};

    // Converte a string para um valor inteiro
    int valorInteiro = atoi(digitos);

    // Etapa 3

    return valorInteiro % tam_vetor;
}

// Etapa 4
Retorno colisao_a(Funcionario f, int hash, Tabela_hashing vetor[], int tam_tabela)
{
    Retorno r;


    if (hash < tam_tabela)
    {
        // caso não haja valor naquela posição, basta inserir
        if (vetor[hash].status == 0)
        {
            vetor[hash].funcionario = f;
            vetor[hash].status = 1;
            r.resultado = 1;
            r.num_colisoes = 0;
        }

        // caso já exista uma informação nessa posição
        else if (vetor[hash].status == 1)
        {
            // caso o funcionario já esteja cadastrado
            if (strcmp(vetor[hash].funcionario.matricula, f.matricula) == 0)
                r.resultado = -1; // -1 significa nem quem foi cadastrado pois já está

            // caso já exista um funcionario diferente cadastrado nessa posição, vamos tratar a colisão
            else
            {
                hash = hash + atoi(&f.matricula[0]);
                r = colisao_a(f,hash,vetor,tam_tabela);
            }
        }
    }
}