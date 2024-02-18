#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//o tamanho padrão das matriculas são 6 digitos com base
#define MATRICULA 6

//estrutura funcionário com os campos de acordo com o enunciado
typedef struct Funcionario
{
    char matricula[MATRICULA];
    char nome[20];
    char funcao[50];
    float salario;

} Funcionario;

/*
Cada estrutura Chave_Hash é um nó da tabela hash linear.
Enquanto houver espaço no vetor os chaves vão ser inseridas diretamente nele
Quando houver colisão, as chaves vão ser encadeadas dinamicamente no elemento que iniciou a colisão
ex:
    a
    b
    c -> c
    d
    e -> e -> e
    f
    g -> b

De forma que sempre que um mesmo hash seja gerado, ao inves de inserir em outro lugar, 
apenas encadeamos os elementos e sabemos que aquele elemento que procuramos está na posição do primeiro hash
entretanto está encadeado em algum lugar.
*/
typedef struct Chave_hash
{
    int hash;
    struct Funcionario funcionario;
    struct Chave_hash *next;

} Chave_hash;


/*
Mostra todos os campos de uma estrutura Funcionario

Args:
    f::Funcionario*: Ponteiro para uma estrutura funcionário

Return:
    None
*/
void mostrar_funcionario(Funcionario *f)
{
    if(f != NULL)
        printf("\n\nNome: %s\nMatricula: %s\nFuncao: %s\nSalario: %f", f->nome,f->matricula,f->funcao,f->salario);
    else
        printf("\nFuncionario nao encontrado!");
}

/*
Preenche todos os campos de uma estrutura Funcionario

Args:
    f::Funcionario*: Ponteiro para uma estrutura funcionário que terá seus campos atualizados
    nome::char*: string com o nome do funcionário
    matricula::char*: string com a matricula do funcionário
    funcao::char*: string com a função do funcionário
    salario::float: salário do funcionário

Return:
    None
*/
void preencher_funcionario(Funcionario *f,char nome[], char matricula[], char funcao[], float salario)
{
    strcpy(f->nome,nome);
    strcpy(f->matricula,matricula);
    strcpy(f->funcao,funcao);
    f->salario = salario;
}