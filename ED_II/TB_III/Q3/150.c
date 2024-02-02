#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MATRICULA 6
#define TAMANHO_LINHA 7
#define TAM_VETOR 150

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

char int2digit(int num)
{
    char result = num + '0';
    return result;
}

int digit2int(char digit)
{
    int result = digit - '0';
    return result;
}

void preencher_funcionario(Funcionario *f, char nome[], char matricula[], char funcao[], float salario)
{
    strcpy(f->nome, nome);
    strcpy(f->matricula, matricula);
    strcpy(f->funcao, funcao);
    f->salario = salario;
}

Tabela_Hash criar_tabela()
{
    Tabela_Hash t;
    int i;
    for (i = 0; i < TAM_VETOR; i++)
        t.itens[i].hash = -1;

    return t;
}

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

int colisao_a(int hash, char primeiro_digito)
{
    return (hash + digit2int(primeiro_digito));
}

Chave_hash cria_chave_a(Funcionario f)
{
    Chave_hash novo_item;
    novo_item.hash = hash_a(f.matricula);
    novo_item.funcionario = f;

    return novo_item;
}

int insere_a(Tabela_Hash *t, Chave_hash item)
{
    int colisao = 0;
    int inseri = 0;

    int hash_inicial = item.hash;
    while (item.hash < TAM_VETOR && inseri == 0)
    {
        if (t->itens[item.hash].hash == -1)
        {
            (t->itens[item.hash]) = item;
            inseri = 1;
        }
        else
        {
            item.hash = colisao_a(item.hash, item.funcionario.matricula[0]);
            colisao++;
        }
    }

    if (inseri == 0)
    {
        t->itens[hash_inicial] = item;
    }

    return colisao;
}

int hash_b(char matricula[])
{
    char aux[MATRICULA];

    aux[0] = matricula[1 - 1];
    aux[1] = matricula[3 - 1];
    aux[2] = matricula[6 - 1];
    aux[3] = matricula[2 - 1];
    aux[4] = matricula[4 - 1];
    aux[5] = matricula[5 - 1];

    int valorInteiro = atoi(aux);

    return valorInteiro % TAM_VETOR;
}

int colisao_b(int hash)
{
    return (hash + 7);
}

Chave_hash cria_chave_b(Funcionario f)
{
    Chave_hash novo_item;
    novo_item.hash = hash_b(f.matricula);
    novo_item.funcionario = f;

    return novo_item;
}

int insere_b(Tabela_Hash *t, Chave_hash item)
{
    int colisao = 0;
    int inseri = 0;
    int hash_inicial = item.hash;

    while (item.hash < TAM_VETOR && inseri == 0)
    {
        if (t->itens[item.hash].hash == -1)
        {
            (t->itens[item.hash]) = item;
            inseri = 1;
        }
        else
        {
            item.hash = colisao_b(item.hash);
            colisao++;
        }
    }

    if (inseri == 0)
    {
        t->itens[hash_inicial] = item;
    }

    return colisao;
}

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


void gerar_matricula(char matricula[6])
{
    int i, num;

    for (i = 0; i < 6; i++)
    {
        num = rand() % 10;
        if(num == 0)
            num+=1;
        
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
