#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MATRICULA 6
#define TAMANHO_LINHA 7
#define TAM_VETOR 101

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
} Chave_hash;

typedef struct Tabela_Hash
{
    Chave_hash itens[TAM_VETOR];
} Tabela_Hash;

/*Conveter um valor inteiro de 0 a 9 para sua versão em char*/
char int2digit(int num)
{
    char result = num + '0';
    return result;
}

// Converte um char entre 0 e 9 para sua versão em int
int digit2int(char digit)
{
    int result = digit - '0';
    return result;
}

// preenche os dados de um funcionário
void preencher_funcionario(Funcionario *f, char nome[], char matricula[], char funcao[], float salario)
{
    strcpy(f->nome, nome);
    strcpy(f->matricula, matricula);
    strcpy(f->funcao, funcao);
    f->salario = salario;
}

// cria uma tabela hash com a config adequada para nosso uso, oned todos os campos vazios terão hash invalido (-1)
Tabela_Hash criar_tabela()
{
    Tabela_Hash t;
    int i;
    for (i = 0; i < TAM_VETOR; i++)
        t.itens[i].hash = -1;

    return t;
}

/*
Função para criar o hash solicitado na letra A da Q3
rotação de 2 dígitos para a esquerda depois extrai o 2, 4 e 6 dígitos e
obtenha o resto da divisão pelo tamanho do vetor destino.
*/
int hash_a(char matricula[])
{
    char aux[MATRICULA];
    int i, j = 2;

    aux[0] = matricula[MATRICULA - 2];
    aux[1] = matricula[MATRICULA - 1];
    for (i = 0; i < MATRICULA - 2; i++)
    {
        aux[j] = matricula[i];
        j++;
    }

    char digitos[4] = {aux[1], aux[3], aux[5], '\0'};
    int valorInteiro = atoi(digitos);

    return valorInteiro % TAM_VETOR;
}

/*
Trantando as colisões conforme o enunciado
As colisões devem ser tratadas somando ao resto da divisão o primeiro dígito da matrícula.
*/
int colisao_a(int hash, char primeiro_digito)
{
    return (hash + digit2int(primeiro_digito));
}

// Criamos uma strutura que tem a chave rash gerada e o funcionário que a mesma guarda
Chave_hash cria_chave_a(Funcionario f)
{
    Chave_hash novo_item;
    novo_item.hash = hash_a(f.matricula);
    novo_item.funcionario = f;

    return novo_item;
}

/*
Insere uma chave em uma tabela de forma a tratar os casos que venham a acontecer
    1 - Local vazio para cadastro
    2 - Local ocupado mas tabela com espaço
    3 - Local ocupado e tabela sem espaço
*/
int insere_a(Tabela_Hash *t, Chave_hash item)
{
    int colisao = 0;
    int inseri = 0;

    int hash_inicial = item.hash;

    while (item.hash < TAM_VETOR && inseri == 0)
    {
        // 1
        if (t->itens[item.hash].hash == -1)
        {
            (t->itens[item.hash]) = item;
            inseri = 1;
        }
        // 2
        else
        {
            item.hash = colisao_a(item.hash, item.funcionario.matricula[0]);
            colisao++;
        }
    }

    // 3
    if (inseri == 0)
    {
        t->itens[hash_inicial] = item;
    }

    return colisao;
}

/*
Função para criar o hash solicitado na letra B da Q3
fole shift com 3 dígitos da seguinte forma: o 1o, 3 e   6o; 2o, 4o e 5o, depois obtenha o resto da divisão do resultado pelo tamanho do vetor destino.
*/
int hash_b(char matricula[])
{

    // preparando a centena, dezena e unidade pra montar o número com os digitos
    int parte1 = (digit2int(matricula[1 - 1]) * 100) + (digit2int(matricula[3 - 1]) * 10) + (digit2int(matricula[6 - 1]));
    int parte2 = (digit2int(matricula[2 - 1]) * 100) + (digit2int(matricula[4 - 1]) * 10) + (digit2int(matricula[5 - 1]));

    int fole_shift = parte1 + parte2;

    return fole_shift % TAM_VETOR;
}

/*
Tratanto as colisões confore solicitado n enunciado
As colisões devem ser realizadas somando 7 ao valor obtido.
*/
int colisao_b(int hash)
{
    return (hash + 7);
}

// Criamos uma strutura que tem a chave rash gerada e o funcionário que a mesma guarda
Chave_hash cria_chave_b(Funcionario f)
{
    Chave_hash novo_item;
    novo_item.hash = hash_b(f.matricula);
    novo_item.funcionario = f;

    return novo_item;
}

/*
Insere uma chave em uma tabela de forma a tratar os casos que venham a acontecer
    1 - Local vazio para cadastro
    2 - Local ocupado mas tabela com espaço
    3 - Local ocupado e tabela sem espaço
*/
int insere_b(Tabela_Hash *t, Chave_hash item)
{
    int colisao = 0;
    int inseri = 0;
    int hash_inicial = item.hash;

    // 1
    while (item.hash < TAM_VETOR && inseri == 0)
    {
        if (t->itens[item.hash].hash == -1)
        {
            (t->itens[item.hash]) = item;
            inseri = 1;
        }
        // 2
        else
        {
            item.hash = colisao_b(item.hash);
            colisao++;
        }
    }

    // 3
    if (inseri == 0)
    {
        t->itens[hash_inicial] = item;
    }

    return colisao;
}

// função experimental para tentar converter um número inteiro de vários digitos para uma string de digitos
char *int2str(int valorInteiro)
{
    char *string;
    string = (char *)malloc(sizeof(char) * 6);

    if (string != NULL)
    {
        snprintf(string, 6, "%d", valorInteiro);
    }

    return string;
}

// Gera as matriculas para testes de forma aleatória usando números entre 1 e 9
void gerar_matricula(char matricula[6])
{
    int i, num;

    for (i = 0; i < 6; i++)
    {
        num = rand() % 10;
        if (num == 0)
            num += 1;

        matricula[i] = int2digit(num);
    }
}

int main()
{
    Tabela_Hash ta = criar_tabela();
    Tabela_Hash tb = criar_tabela();
    Funcionario f;
    Chave_hash c;

    int colisoes = 0, i;

    char matricula[6];

    clock_t inicio = clock();

    for (i = 0; i < 1000; i++)
    {
        gerar_matricula(matricula);
        preencher_funcionario(&f, "teste", matricula, "teste", 0);
        c = cria_chave_a(f);
        colisoes += insere_a(&ta, c);
    }

    clock_t fim = clock();

    double tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
    printf("\nNumero de colisões usando letra A: %d\n", colisoes);
    printf("\nTempo gasto: %lf milissegundos usando letra A\n", tempoGasto);

    colisoes = 0;
    inicio = clock();

    for (i = 0; i < 1000; i++)
    {
        gerar_matricula(matricula);
        preencher_funcionario(&f, "teste", matricula, "teste", 0);
        c = cria_chave_b(f);
        colisoes += insere_b(&tb, c);
    }

    fim = clock();
    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    printf("\nNumero de colisões usando letra B: %d\n", colisoes);
    printf("\nTempo gasto: %lf milissegundos usando letra B\n", tempoGasto);

    return 0;
}
