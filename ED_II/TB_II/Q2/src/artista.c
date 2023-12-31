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

void quebra_no_artista(Arv_23_artista **no, Artista artista, Arv_23_artista *novo_no, Artista *vai_subir, Arv_23_artista *esquerda_novo_no, Arv_23_artista *direita_novo_no)
{

    Artista temp[3];
    temp[0] = (*no)->info1;
    temp[1] = (*no)->info2;
    temp[2] = artista;

    ordenar_artistas(&temp[0], &temp[1], &temp[2]);
    // garantirmos que o maior fique no novo nó e o do meio fique na info2
    (*no)->info1 = temp[0];
    (*no)->info2 = temp[1];

    novo_no->info1 = temp[2];

    (*no)->qtd_infos = 1;
    novo_no->qtd_infos = 1;

    novo_no->esquerda = esquerda_novo_no;
    novo_no->centro = direita_novo_no;

    *vai_subir = (*no)->info2;
}

Arv_23_artista * sobe_artista(Arv_23_artista **pai, Arv_23_artista **raiz ,Artista sobe, Arv_23_artista * novo_no)
{
    Arv_23_artista * head = NULL;
    // se não existe um pai (então é a raiz)
    if (((*pai)) == NULL)
    {
        Arv_23_artista *padrasto = cria_no_artista();

        if (padrasto != NULL)
        {
            padrasto->info1 = sobe;
            padrasto->esquerda = *raiz;
            padrasto->centro = novo_no;
            padrasto->qtd_infos = 1;

            (*raiz)->pai = padrasto;
            (*raiz)->direita = NULL;
            novo_no->pai = padrasto;
            
            head = padrasto; // questionavel
        }
        else
            printf("\nFALHA AO ALOCAR MEMORIA");
    }
    // caso exista um pai
    else
    {
        // checar se tem espaço, se tiver inserir na posição correta
        if ((*pai)->qtd_infos == 1)
        {
            int retorno = compara_string((*pai)->info1.nome, sobe.nome);

            if (retorno < 0)
            {
                (*pai)->info2 = sobe;
                (*pai)->direita = novo_no;
                (*pai)->qtd_infos = 2;

                novo_no->pai = (*pai);

                head = *pai;
            }
            else if (retorno > 0)
            {
                (*pai)->info2 = (*pai)->info1;
                (*pai)->info1 = sobe;
                (*pai)->direita = novo_no;
                (*pai)->qtd_infos = 2;
                
                novo_no->pai = (*pai);

                head = *pai;
            }
        }
        // caso não tenha espaço, precisa quebrar o nó novamente e repetir o processo
        else if ((*pai)->qtd_infos == 2)
        {
            Arv_23_artista *aux = cria_no_artista();
            Artista sobe_quebra_dupla;
            novo_no->pai = aux;  
            quebra_no_artista(&(*pai),sobe,aux,&sobe_quebra_dupla,*raiz,novo_no);
            //teste
            (*pai)->direita = NULL;

            head = sobe_artista(&(*pai)->pai,&(*pai),sobe_quebra_dupla,aux);
        }
    }

    return head;
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
Arv_23_artista* inserir_artista_arv23(Arv_23_artista *raiz, Artista artista)
    {
    Arv_23_artista *aux = raiz;

        if (aux == NULL)
        {
            aux = cria_no_artista();
            if (aux != NULL)
            {
                (aux)->info1 = artista;
                (aux)->qtd_infos = 1;
            }
        }
        else if (no_artista_eh_folha(aux))
        {
            if ((aux)->qtd_infos == 1)
            {
                int retorno = compara_string((aux)->info1.nome, artista.nome);
                // caso o novo valor seja maior que o valor em info1
                if (retorno < 0)
                {
                    (aux)->info2 = artista;
                    (aux)->qtd_infos = 2;
                }
                else if (retorno > 0)
                {
                    (aux)->info2 = (aux)->info1;
                    (aux)->info1 = artista;
                    (aux)->qtd_infos = 2;
                }
            }
            // caso sejá folha e tenha 2 infos, precisamos quebrar o nó (mas vamos garantir que a info não seja igual as que ja temos)
            else if ((aux)->qtd_infos == 2)
            {
                if(compara_string(aux->info1.nome,artista.nome) != 0 && compara_string(aux->info2.nome,artista.nome) != 0 )
                {
                    Arv_23_artista *novo_no =  cria_no_artista();
                    Artista vai_subir;
                    quebra_no_artista(&(raiz), artista, novo_no,&vai_subir,NULL,NULL);
                    aux = sobe_artista(&((raiz)->pai),&raiz,vai_subir,novo_no);
                }
                
            }
        }
        // Caso não seja folha vamos ter que percorrer a arvore para achar uma folha pronta para ser inserida
        else
        {
            int retorno = compara_string((aux)->info1.nome, artista.nome);

            // caso info 1 seja maior que o artista vamos pra esquerda
            if (retorno > 0)
                aux = inserir_artista_arv23(aux->esquerda, artista);

            // caso info 1 seja menor que o artista, precisamos ver existe info2, caso exista vamos comparar com info 2, caso não vamos apenas ir para a direita de info 1 que será nosso centro
            else if (retorno < 0)
            {
                // se a direita for diferente de null, então existe info 2 para compararmos
                if ((aux)->direita != NULL)
                {
                    retorno = compara_string(aux->info2.nome, artista.nome);

                    // caso info 2 seja menor que o artista, então vamos para a direita
                    if (retorno < 0)
                        aux = inserir_artista_arv23(aux->direita, artista);

                    // caso info 2 seja maior que o artista, então vamos pro centro
                    else if (retorno > 0)
                        aux = inserir_artista_arv23(aux->centro, artista);
                }
                // já que não existe info 2, vamos para o centro
                else
                    aux = inserir_artista_arv23(aux->centro, artista);
            }
        }
        while (aux->pai != NULL)
        {
            aux = aux->pai;
        }
            
        return aux;
}

    void mostrar_no_artista(Arv_23_artista * no)
    {
        if (no != NULL)
        {
            printf("\n\nInfo1: %s", no->info1.nome);
            if (no->qtd_infos == 2)
                printf("\tInfo2: %s", no->info2.nome);
        }
    }

    void mostrar_arv_artistas(Arv_23_artista * raiz)
    {
        if (raiz != NULL)
        {
            mostrar_no_artista(raiz);
            mostrar_arv_artistas(raiz->esquerda);
            mostrar_arv_artistas(raiz->centro);
            mostrar_arv_artistas(raiz->direita);
        }
    }
