#include "album.c"
#include "artista.h"

#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{
    char nome[NOME];
    char tipo[TIPO];
    char estilo[ESTILO];
    int num_albuns;
    Arv_23_album *albuns;

} Artista;

typedef struct Arv_23_artista
{
    int qtd_infos;
    Artista info1;
    Artista info2;
    struct Arv_23_artista *pai;
    struct Arv_23_artista *esquerda;
    struct Arv_23_artista *centro;
    struct Arv_23_artista *direita;

} Arv_23_artista;

/*
Preenche um artista com seus respectivos dados

Args:
    artista::Artista*: Ponteiro para o artista que será preenchido
    nome::char: Nome do Artista
    tipo::char: Tipo do Artista
    estilo::char: Estilo do Artista

Return:
    None
*/
void preencher_artista(Artista *artista, char nome[], char tipo[], char estilo[])
{
    strcpy(artista->nome, nome);
    strcpy(artista->tipo, tipo);
    strcpy(artista->estilo, estilo);
    artista->num_albuns = 0;
    artista->albuns = NULL;
}

/*
Cria um nó para um artista e dependendo do caso retorna:
    Nó do artista quando criado com sucesso
    NULL quando não consegue alocar o nó

Args:
    None

Return:
    no::Arv_23_artista*: Endereço de um nó artista;

*/
Arv_23_artista *cria_no_artista()
{
    Arv_23_artista *no = (Arv_23_artista *)malloc(sizeof(Arv_23_artista));

    if (no)
    {
        no->qtd_infos = 0;
        no->pai = NULL;
        no->esquerda = NULL;
        no->centro = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

/*
Verifica se um nó artista é falho ou não
    1 - Caso seja folha
    0 - Caso não seja folha

Args:
    no::Arv_23_artista*: Ponteiro para o nó que será checado

Return:
    sinal::int: Sinalização referente a checagem se é ou não folha
*/
int no_artista_eh_folha(Arv_23_artista *no)
{
    int sinal = 0;
    if (no->direita == NULL && no->centro == NULL && no->esquerda == NULL)
        sinal = 1;

    return sinal;
}

/*
Troca a posicação de dois artistas com base na ordem alfabetica dos mesmos
o menor sempre ficará em a1, o do meio em a2 e o maior em a3

Args:
    a1::Artista*: Ponteiro para artista que será o menor
    a2::Artista*: Ponteiro para artista que será o do meio
    a3::Artista*: Ponteiro para artista que será o maior

Return:
    None

*/
void ordenar_artistas(Artista *a1, Artista *a2, Artista *a3)
{
    Artista aux;
    // caso o primeiro seja maior que o segundo, e do que o terceiro
    if (compara_string(a1->nome, a2->nome) > 0 && compara_string(a1->nome, a3->nome) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a1;
        *a1 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {

            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o segundo seja o maior de todos
    else if (compara_string(a2->nome, a1->nome) > 0 && compara_string(a2->nome, a3->nome) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a2;
        *a2 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o terceiro seja o maior de todos
    else if (compara_string(a3->nome, a1->nome) > 0 && compara_string(a3->nome, a2->nome) > 0)
    {
        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
}

/*Dica do GPT
void quebra_no_artista(Arv_23_artista **raiz, Artista artista)
    {
    if ((*raiz)->qtd_infos == 2)
    {
        // Criando um novo nó para acomodar a terceira informação
        Arv_23_artista *novo_no = cria_no_artista();

        if (novo_no != NULL)
        {
            Artista temp[3];
            temp[0] = (*raiz)->info1;
            temp[1] = (*raiz)->info2;
            temp[2] = artista;

            ordenar_artistas(&temp[0], &temp[1], &temp[2]);

            // Atribuindo as informações aos nós
            (*raiz)->info1 = temp[0];
            (*raiz)->info2 = temp[1];
            novo_no->info1 = temp[2];

            // Dividindo os filhos (se existirem)
            novo_no->esquerda = (*raiz)->esquerda;
            novo_no->centro = (*raiz)->direita;

            (*raiz)->esquerda = NULL;
            (*raiz)->direita = NULL;

            (*raiz)->qtd_infos = 1;
            novo_no->qtd_infos = 1;

            // Se o nó for raiz, redefinir a raiz
            if ((*raiz) == (*raiz)->direita)
            {
                Arv_23_artista *nova_raiz = cria_no_artista();
                nova_raiz->info1 = temp[1];
                nova_raiz->esquerda = (*raiz);
                nova_raiz->centro = novo_no;
                (*raiz) = nova_raiz;
            }
            else
            {
                // Promovendo o elemento do meio para o nó pai
                artista = temp[1];
                (*raiz)->info1 = temp[0];
                (*raiz)->info2 = temp[1];
                (*raiz)->qtd_infos = 1;

                // Recursão para inserir no nó pai
                if (compara_string(artista.nome, (*raiz)->info1.nome) < 0)
                    inserir_artista_arv23(&(*raiz)->esquerda, artista);
                else
                    inserir_artista_arv23(&(*raiz)->centro, artista);
            }
        }
    }
}
*/

/*
Sobe uma informação de um nó atual para o seu pai,  para tentar inserir no pai essa informação

Args:
    raiz::Arv_23_artista**: Referência do ponteiro que aponta para o nó que guarda o pai

*/


Arv_23_artista *quebra_no_artista(Arv_23_artista *raiz, Artista artista)
{

    Arv_23_artista *novo_no = cria_no_artista();


    Artista temp[3];
    temp[0] = raiz->info1;
    temp[1] = raiz->info2;
    temp[2] = artista;

    ordenar_artistas(&temp[0], &temp[1], &temp[2]);
    //garantirmos que o maior fique no novo nó e o do meio fique na info2
    raiz->info1 = temp[0];
    raiz->info2 = temp[1];
    novo_no->info1 = temp[2];

    novo_no->qtd_infos = 1;
    raiz->qtd_infos = 1;

    Artista subiu = raiz->info2;
    Arv_23_artista *esquerda = raiz;
    Arv_23_artista *direita = novo_no;

    Arv_23_artista *nova_raiz = raiz->pai;
    //se não existe um pai (o no anterior já era a raiz)
    if((nova_raiz) == NULL)
    {
        Arv_23_artista *padrasto = cria_no_artista();

        if(padrasto != NULL)
        {
            padrasto->info1 = subiu;
            padrasto->esquerda = esquerda;
            padrasto->centro = direita;
            padrasto->qtd_infos = 1;
            nova_raiz = padrasto;
            
            esquerda->pai = nova_raiz;
            direita->pai = nova_raiz;
        }
        else
            printf("\nFALHA AO ALOCAR MEMORIA");
    }
    //caso exista um pai
    else
    {
        //checar se tem espaço, se tiver inserir na posição correta
        if((nova_raiz)->qtd_infos == 1)
        {
            int retorno = compara_string((nova_raiz)->info1.nome,subiu.nome);
            
            if (retorno < 0)
            {
                nova_raiz->info2 = subiu;
                nova_raiz->direita = direita;
                nova_raiz->qtd_infos = 2;

                direita->pai = nova_raiz;
            }
            else if (retorno > 0)
            {
                nova_raiz->info2 = (nova_raiz)->info1;
                nova_raiz->info1 = subiu;

                nova_raiz->direita = direita;
                nova_raiz->qtd_infos = 2;

                direita->pai = nova_raiz;      
            }
        }
        //caso não tenha espaço, precisa quebrar o nó novamente e repetir o processo
        else
            nova_raiz = quebra_no_artista(nova_raiz,subiu);
        
    }

    return nova_raiz;
}



/*
Insere um novo nó artista em uma arvore de artistas
    1 - Sucesso
    0 - Já cadastrado
   -1 - Falha ao alocar memoria para a inserção

Args:
    raiz::Arv_23_artista**: Referência do Ponteiro que guarda a raiz da arvore
    novo_no::Arv_23_artista**: Ponteiro para o novo nó que será inserido na arvore

Return:
    inseri::int: Sinalização sobre o resultado da inserção
*/
int inserir_artista_arv23(Arv_23_artista **raiz, Artista artista)
{
    int inseri = 0;
    if (*raiz == NULL)
    {
        *raiz = cria_no_artista();
        if (*raiz != NULL)
        {
            (*raiz)->info1 = artista;
            (*raiz)->qtd_infos = 1;
            inseri = 1;
        }
        else
            inseri = -1;
    }
    else if (no_artista_eh_folha(*raiz))
    {
        if ((*raiz)->qtd_infos == 1)
        {
            int retorno = compara_string((*raiz)->info1.nome, artista.nome);
            //caso o novo valor seja maior que o valor em info1
            if (retorno < 0)
            {
                (*raiz)->info2 = artista;
                (*raiz)->qtd_infos = 2;
                inseri = 1;
            }
            else if (retorno > 0)
            {
                (*raiz)->info2 = (*raiz)->info1;
                (*raiz)->info1 = artista;
                (*raiz)->qtd_infos = 2;
                inseri = 1;
            }
        }
        // caso sejá folha e tenha 2 infos, precisamos quebrar o nó
        else if ((*raiz)->qtd_infos == 2)
        {
            *raiz = quebra_no_artista((*raiz),artista);
            if(raiz!=NULL)
                inseri = 1;
        }
    }
    // Caso não seja folha vamos ter que percorrer a arvore para achar uma folha pronta para ser inserida
    else
    {
        int retorno = compara_string((*raiz)->info1.nome, artista.nome);

        // caso info 1 seja maior que o artista vamos pra esquerda
        if (retorno > 0)
            inseri = inserir_artista_arv23(&(*raiz)->esquerda, artista);

        // caso info 1 seja menor que o artista, precisamos ver existe info2, caso exista vamos comparar com info 2, caso não vamos apenas ir para a direita de info 1 que será nosso centro
        else if (retorno < 0)
        {
            // se a direita for diferente de null, então existe info 2 para compararmos
            if ((*raiz)->direita != NULL)
            {
                retorno = compara_string((*raiz)->info2.nome, artista.nome);

                // caso info 2 seja menor que o artista, então vamos para a direita
                if (retorno < 0)
                    inseri = inserir_artista_arv23(&(*raiz)->direita, artista);

                // caso info 2 seja maior que o artista, então vamos pro centro
                else if (retorno > 0)
                    inseri = inserir_artista_arv23(&(*raiz)->centro, artista);
            }
            // já que não existe info 2, vamos para o centro
            else
                inseri = inserir_artista_arv23(&(*raiz)->centro, artista);
        }
    }

    return inseri;
}

void mostrar_no_artista(Arv_23_artista *no)
{
    if(no != NULL)
    {
        printf("\n\nInfo1: %s", no->info1.nome);
        if(no->qtd_infos==2)
            printf("\nInfo2: %s", no->info2.nome);
    }
}

void mostrar_arv_artistas(Arv_23_artista *raiz)
{
    if(raiz != NULL)
    {
        mostrar_no_artista(raiz);
        mostrar_arv_artistas(raiz->esquerda);
        mostrar_arv_artistas(raiz->centro);
        mostrar_arv_artistas(raiz->direita);
    }
}
