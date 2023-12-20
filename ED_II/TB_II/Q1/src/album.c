#include <stdio.h>
#include <string.h>
#include "musica.c"

#define TAM_TITULO 50
#define VERMELHO 1
#define PRETO 0

typedef struct Album
{
    char titulo[TAM_TITULO];
    int ano;
    int qtd_musicas;
    Lista_musicas *musicas;

} Album;

typedef struct RB_album
{
    int cor;
    Album album;
    struct RB_album *esquerda;
    struct RB_album *direita;

} RB_album;

//////////////////////////////////////////////////////////////////////////////////////////////////

void preencher_album(Album *album, char titulo[TAM_TITULO], int ano)
{
    strcpy(album->titulo, titulo);
    album->ano = ano;
    album->qtd_musicas = 0;
    album->musicas = iniciar_no_lista();
}

int adiciona_musica_album(Album *album, Musica *musica)
{
    int adicionei = adicionar_musica_ordenada(&(album->musicas), musica);
    if (adicionei)
        album->qtd_musicas += 1;
    // contar_musicas(album->musicas);

    return adicionei;
}

int remover_musica_album(Album *album, char titulo[TAM_TITULO])
{
    int removi = remover_musica(&(album->musicas), titulo);
    if (removi)
        album->qtd_musicas -= 1;
    // contar_musicas(album->musicas);

    return removi;
}

void mostrar_album(Album *album)
{
    if (album != NULL)
    {
        printf("\n\nTitulo: %s\nAno: %d\nQuantidade de Musicas: %d\nMusicas:\n", album->titulo, album->ano, album->qtd_musicas);
        if (album == NULL)
            printf("\n\nZero Musicas Cadatradas");
        else
            mostar_todas_musicas(album->musicas);
    }
    else
    {
        printf("\nSem album cadastrado!");
    }
}

void mostrar_todos_nos_album(RB_album *no)
{
    if (no != NULL)
    {
        mostrar_album(&(no->album));
    }
}

/////////////////////////////////////////////////////////////////////////////////////////// Funções nativas da RB

/*
Retorna a cor do nó passado
    0: Caso seja preto
    1: Caso seja vermelho
*/
int cor_album(RB_album *raiz)
{
    int cor;

    if (raiz == NULL)
        cor = PRETO;
    else
        cor = raiz->cor;

    return cor;
}

void swap_cor_album(RB_album *raiz)
{
    if (raiz != NULL)
    {
        raiz->cor = !raiz->cor;

        if (raiz->direita != NULL)
            raiz->direita->cor = !raiz->direita->cor;

        if (raiz->esquerda != NULL)
            raiz->esquerda->cor = !raiz->esquerda->cor;
    }
}

RB_album *rotacao_direita_album(RB_album *raiz)
{
    RB_album *aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_album *rotacao_esquerda_album(RB_album *raiz)
{
    RB_album *aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_album *balancear_RB_album(RB_album **raiz)
{
    if (cor_album((*raiz)->direita) == VERMELHO)
        *raiz = rotacao_esquerda_album(*raiz);

    if ((*raiz)->esquerda != NULL && cor_album((*raiz)->direita) == VERMELHO && cor_album((*raiz)->esquerda->esquerda) == VERMELHO)
        *raiz = rotacao_direita_album(*raiz);

    if (cor_album((*raiz)->esquerda) == VERMELHO && cor_album((*raiz)->direita) == VERMELHO)
        swap_cor_album(*raiz);

    return *raiz;
}

////////////////////////////////  Funções do projeto

RB_album *cria_no_album(char titulo[TAM_TITULO], int ano)
{
    RB_album *no;
    no = (RB_album *)malloc(sizeof(RB_album));

    if (no)
    {

        no->cor = VERMELHO;
        preencher_album(&(no->album), titulo, ano);
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

/*
RB_album *balanceia_album(RB_album *raiz)
{
    if (cor_album(raiz->direita) == VERMELHO && cor_album(raiz->esquerda) == PRETO)
        raiz = rotacao_esquerda_album(&raiz);

    if (cor_album(raiz->esquerda) == VERMELHO && cor_album(raiz->esquerda->esquerda) == VERMELHO)
        raiz = rotacao_direita_album(&raiz);

    if (cor_album(raiz->esquerda) == VERMELHO && cor_album(raiz->direita) == VERMELHO)
        swap_cor_album(raiz);

    return raiz;
}
*/

int insere_no_RB_album(RB_album **raiz, RB_album *novo)
{
    int criou_no = 0;

    if (*raiz == NULL)
    {
        *raiz = novo;
        criou_no = 1;
    }
    else if (compara_string(novo->album.titulo,(*raiz)->album.titulo) == 0)
        criou_no = -1; // Nó já cadastrado

    else if (compara_string(novo->album.titulo,(*raiz)->album.titulo) > 0)
    {
        RB_album *aux = *raiz;
        criou_no = insere_no_RB_album(&((aux)->direita), novo);
    }

    else
    {
        RB_album *aux = *raiz;
        criou_no = insere_no_RB_album(&((aux)->esquerda), novo);
    }

    balancear_RB_album(&(*raiz));

    return criou_no;
}

void mostrar_tudo_RB_album(RB_album *raiz)
{
    if (raiz != NULL)
    {
        mostrar_tudo_RB_album(raiz->esquerda);
        mostrar_album(&(raiz->album));
        mostrar_tudo_RB_album(raiz->direita);
    }
}

RB_album *buscar_no_RB_album(RB_album *raiz,char titulo_buscado[TAM_TITULO])
{
    RB_album *no_buscado = NULL;

    if (raiz != NULL)
    {
        if (compara_string(titulo_buscado,raiz->album.titulo)==0)
            no_buscado = raiz;

        else if (compara_string(titulo_buscado,raiz->album.titulo) < 0)
            no_buscado = buscar_no_RB_album(raiz->esquerda, titulo_buscado);

        else
            no_buscado = buscar_no_RB_album(raiz->direita, titulo_buscado);
    }
    return no_buscado;
}

/*

Album *move_esq_red_album(Album *raiz)
{
    troca_Cor_album(raiz);
    if (cor_album(raiz->direita->esquerda) == VERMELHO)
    {
        rotacao_direita_album(raiz->direita);
        rotacao_esquerda_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album *move_dir_red_album(Album *raiz)
{
    troca_Cor_album(raiz);
    if (cor_album(*raiz->esquerda->esquerda) == VERMELHO)
    {
        rotacao_direita_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album *remove_menor_album(Album *raiz)
{
    if (raiz->esquerda == NULL)
    {
        free(raiz);
    }
    if (cor_album(raiz->esquerda) == PRETO && cor_album(raiz->esquerda->esquerda) == PRETO)
    {
        raiz = move_esq_red_album(raiz);
    }

    remove_menor_album(raiz->esquerda);
    return balanceia_album(raiz);
}

Album *procuraMenor_album(Album *atual)
{
    Album *no1 = atual;
    Album *no2 = atual->esquerda;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1;
}

Album *buscarFolha_album(Album *ultimo)
{
    if (ultimo->direita != NULL)
    {
        buscarFolha_album(ultimo->direita);
    }
    else
    {
        return ultimo;
    }
}

Album *remove_NO_album(Album **raiz, char titulo[])
{
    int remove = 0;
    Album *aux = NULL;

    if (*raiz != NULL)
    {
        if (strcmp((*raiz)->titulo, titulo) == 0)
        {
            aux = *raiz;

            if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL)
            {
                free(aux);
                *raiz = NULL;
            }
            else if ((*raiz)->esquerda == NULL || (*raiz)->direita == NULL)
            {
                *raiz = ((*raiz)->esquerda != NULL) ? (*raiz)->esquerda : (*raiz)->direita;
                free(aux);
            }
            else
            {
                aux = buscarFolha_album(&(*raiz)->esquerda);
                strcpy((*raiz)->titulo, aux->titulo);
                remove_NO_album(&(*raiz)->esquerda, aux->titulo);
            }

            remove = 1;
        }
        else if (strcmp((*raiz)->titulo, titulo) < 0)
        {
            remove = remove_NO_album(&((*raiz)->direita), titulo);
        }
        else if (strcmp((*raiz)->titulo, titulo) > 0)
        {
            remove = remove_NO_album(&((*raiz)->esquerda), titulo);
        }
    }

    balanceia_album(*raiz);

    return *raiz;
}
*/