#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRICULA 6

typedef struct Funcionario
{
    char matricula[MATRICULA];
    char nome[20];
    char funcao[50];
    float salario;

} Funcionario;

typedef struct Chave_hash
{
    int hash;
    struct Funcionario funcionario;
    struct Chave_hash *next;

} Chave_hash;


void mostrar_funcionario(Funcionario *f)
{
    if(f != NULL)
        printf("\n\nNome: %s\nMatricula: %s\nFuncao: %s\nSalario: %f", f->nome,f->matricula,f->funcao,f->salario);
    else
        printf("\nFuncionario nao encontrado!");
}

void preencher_funcionario(Funcionario *f,char nome[], char matricula[], char funcao[], float salario)
{
    strcpy(f->nome,nome);
    strcpy(f->matricula,matricula);
    strcpy(f->funcao,funcao);
    f->salario = salario;
}