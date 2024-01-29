#include <stdio.h>
#include "funcionario.c"

#define TAM_VETOR 101

typedef struct Tabela_Hash
{
    Chave_hash *itens[TAM_VETOR];
} Tabela_Hash;


struct Tabela_Hash criar_tabela()
{
    struct Tabela_Hash tabela;

    for (int i = 0; i < TAM_VETOR; i++)
        tabela.itens[i] = NULL;

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

Chave_hash cria_chave(Funcionario f)
{
    
    Chave_hash novo_item;
    novo_item.hash = hash_a(f.matricula);
    novo_item.funcionario = f;
    novo_item.next = NULL;

    return novo_item;
}

int insere(Tabela_Hash *t, Chave_hash item)
{
    int colisao = 0;

    // Verifica se a posição na tabela está vazia
    if (t->itens[item.hash] == NULL)
    {
        t->itens[item.hash] = (Chave_hash*)malloc(sizeof(Chave_hash));
        *(t->itens[item.hash]) = item;
        (t->itens[item.hash])->next = NULL;
    }
        

    else
    {
        Chave_hash *aux = t->itens[item.hash];
        
        while (aux!= NULL)
        {
            aux = aux->next;
            item.hash = colisao_a(item.hash,item.funcionario.matricula[0]);
            colisao+=1;
        }

        aux = (Chave_hash*)malloc(sizeof(Chave_hash));
        *(aux) = item;
        aux->next = NULL;
    }

    return colisao;
}

Funcionario *buscar(Tabela_Hash *t,char matricula[])
{
    int hash = hash_a(matricula);
    Funcionario *alvo=NULL;

    Chave_hash *aux = t->itens[hash];

    while (aux != NULL && aux->hash != hash)
    {
        hash = colisao_a(hash,matricula[0]);
        aux = aux->next;
    }

    //caso tenhamos encontrado nosso alvo, vamos pegar o endereço do funcionario
    if(aux != NULL)
        alvo = &(aux->funcionario);

    return alvo;
}

int menu()
{
    int opc;


    printf("\n\n[1] - Cadatrar Funcionario\n[2] - Buscar Funcionario\n[0] - Sair\n\nResposta: ");
    setbuf(stdin,NULL);
    scanf("%d", &opc);


    return opc;
}



int main(void)
{
    Tabela_Hash t = criar_tabela();
    Funcionario f;
    Chave_hash c;


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
            setbuf(stdin,NULL);
            scanf("%s", nome);

            printf("\n\nMatricula: ");
            setbuf(stdin,NULL);
            scanf("%s", matricula);

            printf("\n\nFuncao: ");
            setbuf(stdin,NULL);
            scanf("%s", funcao);

            printf("\n\nSalario: ");
            setbuf(stdin,NULL);
            scanf("%f", &salario);

            preencher_funcionario(&f,nome,matricula,funcao,salario);

            c = cria_chave(f);
            colisoes = insere(&t,c);

            printf("\n\nInserido com sucesso ao custo de %d colisoes ", colisoes);

            break;

        case 2:
            printf("\n\nMatricula: ");
            setbuf(stdin,NULL);
            scanf("%s", nome);

            mostrar_funcionario( buscar(&t,matricula) );
        
        default:
            break;
        }
    
    }

    return 0;
}