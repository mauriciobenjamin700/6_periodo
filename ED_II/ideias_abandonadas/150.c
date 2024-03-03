#include <stdio.h>
#include <time.h>
#include "funcionario.c"

#define TAMANHO_LINHA 7 // 6 caracteres + 1 para o caractere nulo '\0'
#define TAM_VETOR 150

typedef struct Tabela_Hash
{
    Chave_hash *itens[TAM_VETOR];
} Tabela_Hash;

Tabela_Hash criar_tabela()
{
    Tabela_Hash tabela;

    for (int i = 0; i < TAM_VETOR; i++)
    {
        tabela.itens[i] = (Chave_hash *)malloc(sizeof(Chave_hash));

        tabela.itens[i] = NULL;
    }

    return tabela;
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
int hash_a(char matricuta[])
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

    return valorInteiro % TAM_VETOR;
}

// Etapa 4
int colisao_a(int hash, char primeiro_digito)
{
    return (hash + atoi(&primeiro_digito));
}

Chave_hash *cria_chave_a(Funcionario f)
{

    Chave_hash *novo_item = (Chave_hash *)malloc(sizeof(Chave_hash));

    novo_item->hash = hash_a(f.matricula);
    novo_item->funcionario = f;
    novo_item->next = NULL;

    return novo_item;
}

int insere_a(Tabela_Hash *t, Chave_hash *item)
{
    int colisao = 0;

    // Verifica se a posição na tabela está vazia
    if (t->itens[item->hash] == NULL)
    {
        t->itens[item->hash] = (Chave_hash *)malloc(sizeof(Chave_hash));
        (t->itens[item->hash]) = item;
        (t->itens[item->hash])->next = NULL;
    }

    else
    {
        Chave_hash *aux = t->itens[item->hash];

        while (aux->next != NULL)
        {
            aux = aux->next;
            item->hash = colisao_a(item->hash, item->funcionario.matricula[0]);
            colisao += 1;
        }
        item->hash = colisao_a(item->hash, item->funcionario.matricula[0]);
        colisao += 1;

        aux->next = (Chave_hash *)malloc(sizeof(Chave_hash));
        aux->next = item;
    }

    return colisao;
}

Funcionario *buscar_a(Tabela_Hash *t, char matricula[])
{
    int hash = hash_a(matricula);
    Funcionario *alvo = NULL;

    Chave_hash *aux = t->itens[hash];

    while (aux != NULL && strcmp(matricula, aux->funcionario.matricula) != 0)
    {
        aux = aux->next;
    }
    // caso tenhamos encontrado nosso alvo, vamos pegar o endereço do funcionario
    if (aux != NULL)
        alvo = &(aux->funcionario);

    return alvo;
}

/*
1 - fole shift com 3 dígitos da seguinte forma: o 1o, 3 e   6o; 2o, 4o e 5o
2 - depois obtenha o resto da divisão do resultado pelo tamanho do vetor destino.
3 - As colisões devem ser realizadas somando 7 ao valor obtido.
*/
int hash_b(char matricuta[])
{
    char aux[MATRICULA];

    // Etapa 1
    aux[0] = matricuta[1 - 1];
    aux[1] = matricuta[3 - 1];
    aux[2] = matricuta[6 - 1];
    aux[3] = matricuta[2 - 1];
    aux[4] = matricuta[4 - 1];
    aux[5] = matricuta[5 - 1];

    // Etapa 2

    // Converte a string para um valor inteiro
    int valorInteiro = atoi(aux);

    return valorInteiro % TAM_VETOR;
}
int colisao_b(int hash)
{
    return (hash + 7);
}

Chave_hash *cria_chave_b(Funcionario f)
{

    Chave_hash *novo_item = (Chave_hash *)malloc(sizeof(Chave_hash));

    novo_item->hash = hash_b(f.matricula);
    novo_item->funcionario = f;
    novo_item->next = NULL;

    return novo_item;
}

int insere_b(Tabela_Hash *t, Chave_hash *item)
{
    int colisao = 0;

    // Verifica se a posição na tabela está vazia
    if (t->itens[item->hash] == NULL)
    {
        t->itens[item->hash] = (Chave_hash *)malloc(sizeof(Chave_hash));
        (t->itens[item->hash]) = item;
        (t->itens[item->hash])->next = NULL;
    }

    else
    {
        Chave_hash *aux = t->itens[item->hash];

        while (aux->next != NULL)
        {
            aux = aux->next;
            item->hash = colisao_b(item->hash);
            colisao += 1;
        }
        item->hash = colisao_b(item->hash);
        colisao += 1;

        aux->next = (Chave_hash *)malloc(sizeof(Chave_hash));
        aux->next = item;
    }

    return colisao;
}

Funcionario *buscar_b(Tabela_Hash *t, char matricula[])
{
    int hash = hash_b(matricula);
    Funcionario *alvo = NULL;

    Chave_hash *aux = t->itens[hash];

    while (aux != NULL && strcmp(matricula, aux->funcionario.matricula) != 0)
    {
        aux = aux->next;
    }
    // caso tenhamos encontrado nosso alvo, vamos pegar o endereço do funcionario
    if (aux != NULL)
        alvo = &(aux->funcionario);

    return alvo;
}

/*
int menu()
{
    int opc;

    printf("\n\n[1] - Cadatrar Funcionario\n[2] - Buscar Funcionario\n[0] - Sair\n\nResposta: ");
    setbuf(stdin, NULL);
    scanf("%d", &opc);

    return opc;
}

int main(void)
{
    Tabela_Hash t = criar_tabela();
    Funcionario f;
    Chave_hash *c;

    char matricula[MATRICULA];
    char nome[20];
    char funcao[50];
    float salario;

    int colisoes = 0;

    int opc = 1;

    while (opc != 0)
    {

        opc = menu();

        switch (opc)
        {
        case 1:
            printf("\n\nNome: ");
            setbuf(stdin, NULL);
            scanf("%s", nome);

            printf("\n\nMatricula: ");
            setbuf(stdin, NULL);
            scanf("%s", matricula);

            printf("\n\nFuncao: ");
            setbuf(stdin, NULL);
            scanf("%s", funcao);

            printf("\n\nSalario: ");
            setbuf(stdin, NULL);
            scanf("%f", &salario);

            preencher_funcionario(&f, nome, matricula, funcao, salario);

            c = cria_chave_a(f);
            colisoes = insere_a(&t, c);

            printf("\n\nInserido com sucesso ao custo de %d colisoes ", colisoes);

            break;

        case 2:
            printf("\n\nMatricula: ");
            setbuf(stdin, NULL);
            scanf("%s", matricula);

            f = *(buscar_a(&t, matricula));

            mostrar_funcionario(&f);

        default:
            break;
        }
    }

    return 0;
}
*/

char *int2str(int valorInteiro)
{
    // Defina o tamanho da string conforme necessário
    char *string;
    string = (char *)malloc(sizeof(char) * 6); // Alocando memória para a string

    if (string != NULL)
    {
        // Usando snprintf para converter o inteiro em uma string
        snprintf(string, 20, "%d", valorInteiro);
        // O segundo argumento (20) é o tamanho máximo da string que pode ser armazenado, ajuste conforme necessário
    }

    return string;
}

void carregar_matriculas(char matriculas[1000][MATRICULA])
{
    FILE *arquivo;
    char linha[TAMANHO_LINHA];

    // Abra o arquivo para leitura
    arquivo = fopen("matriculas.txt", "r");

    // Leia cada linha do arquivo e armazene no vetor de strings
    for (int i = 0; i < 1000; ++i)
    {
        if (fgets(linha, sizeof(linha), arquivo) != NULL)
        {
            // Remova o caractere de nova linha, se presente
            linha[strcspn(linha, "\n")] = '\0';
            strcpy(matriculas[i], linha);
        }
        else
        {
            // Se chegarmos ao final do arquivo antes de 1000 linhas, pare o loop
            break;
        }
    }
    fclose(arquivo);
}

int avaliar_modelo_a(char matriculas[1000][MATRICULA])
{

    int i;

    Tabela_Hash t = criar_tabela();
    Funcionario f;
    Chave_hash *c;

    int colisoes = 0;

    /* Imprima o vetor de strings (apenas para verificar)
    for (int i = 0; i < 1000; ++i)
    {
        printf("%s\n", matriculas[i]);
    }
    */

    for (i = 0; i < 1000; i++)
    {
        preencher_funcionario(&f, int2str(i), matriculas[i], int2str(i), i);
        c = cria_chave_a(f);
        colisoes += insere_a(&t, c);
    }

    return colisoes;
}

int avaliar_modelo_b(char matriculas[1000][MATRICULA])
{

    int i;

    Tabela_Hash t = criar_tabela();
    Funcionario f;
    Chave_hash *c;

    int colisoes = 0;

    /* Imprima o vetor de strings (apenas para verificar)
    for (int i = 0; i < 1000; ++i)
    {
        printf("%s\n", matriculas[i]);
    }
    */

    for (i = 0; i < 1000; i++)
    {
        preencher_funcionario(&f, int2str(i), matriculas[i], int2str(i), i);
        c = cria_chave_b(f);
        colisoes += insere_b(&t, c);
    }

    return colisoes;
}

int main()
{
    char matriculas[1000][MATRICULA];
    carregar_matriculas(matriculas);
    clock_t inicio = clock();
    int colisoes = avaliar_modelo_a(matriculas);
    clock_t fim = clock();

    double tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;
    printf("\nNumero de colisões usando letra A: %d", colisoes);
    printf("\nTempo gasto: %f milissegundos usando letra A\n", tempoGasto);

    inicio = clock();
    colisoes = avaliar_modelo_b(matriculas);
    fim = clock();
    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    printf("\nNumero de colisões usando letra B: %d", colisoes);
    printf("\nTempo gasto: %f milissegundos usando letra B\n", tempoGasto);
    
    return 0;
}