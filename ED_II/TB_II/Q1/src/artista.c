#include <stdio.h>
#include <stdlib.h>
#include "album.c"
#define VERMELHO 1
#define PRETO 0 

#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{   
    int id;
    char nome[NOME];
    char tipo[TIPO];
    char estilo[ESTILO];
    int num_albuns;

}Artista;

typedef struct RB_artista
{
    int cor;

    Artista artista;
    struct RB_artista *esquerda;
    struct RB_artista *direita;
    
}RB_artista;

Artista *criar_Artista()
{
    Artista *artista;
    artista = (Artista *)malloc(sizeof(Artista));

    if (!artista)
        artista = NULL;

    return artista;
}

void preencher_artista(Artista *artista,char nome[NOME], char tipo[TIPO], char estilo[ESTILO], int num_albuns, int id)
{   
    artista->id = id;
    strcpy(artista->nome,nome);
    strcpy(artista->tipo,tipo);
    strcpy(artista->estilo,estilo);
    artista->num_albuns = num_albuns;
}

RB_artista * cria_no_artista(int cor,Artista artista)
{
    RB_artista *no = (RB_artista *)malloc(sizeof(RB_artista));

    if(no)
    {
        no->cor = cor;
        no->artista = artista;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;
    
    return no;
}

void trocar_cor(RB_artista *no) {
    if (no != NULL)
    {
        no->cor = !no->cor;

        if (no->direita != NULL)
            no->direita->cor = !no->direita->cor;

        if (no->esquerda != NULL)
            no->esquerda->cor = !no->esquerda->cor;
    }
}

void trocar_cor_raiz(RB_artista *no) {
    if (no != NULL)
    {
        no->cor = PRETO;
    }
}

int cor(RB_artista *no) {
    return (no != NULL) ? PRETO : no->cor;
}

RB_artista* rotacao_direita_artista(RB_artista *raiz)
{
    RB_artista *aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}


RB_artista* rotacao_esquerda_artista(RB_artista *raiz)
{
    RB_artista *aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_artista *move2EsqRED(RB_artista *no){
    trocar_cor(no);
    if(cor(no->direita->esquerda) == VERMELHO){
        no->direita = rotacao_direita_artista(no->direita);
        no = rotacao_esquerda_artista(no);
        trocar_cor(no);
    }
    return no;
}

RB_artista *move2DirRED(RB_artista *no){
    trocar_cor(no);
    if(cor(no->esquerda->esquerda) == VERMELHO){
        no = rotacao_direita_artista(no);
        trocar_cor(no);
    }
    return no;
}

RB_artista *balancear_RB_artista(RB_artista *no){
    if(cor(no->direita) == VERMELHO){
        no = rotacao_esquerda_artista(no);
    }

    if(no->esquerda != NULL && cor(no->direita) == VERMELHO && cor(no->esquerda->esquerda) == VERMELHO){
        no = rotacao_direita_artista(no);
    }

    if(cor(no->esquerda) == VERMELHO && cor(no->direita) == VERMELHO){
        trocar_cor(no);
    }

    return no;
}


RB_artista *insere_no_artista(RB_artista *raiz, RB_artista *novo_no)
{
    if(raiz == NULL){
        return novo_no; 
    }
    else{
    /*
        Nesse caso ele verifica se o id do artista é maior ou menor e 
        segue até chegar na raiz nula, insere nela, o ultimo else é no caso de ser igual
        nesse caso a arvore permanece igual.
    */
        if(novo_no->artista.id < raiz->artista.id){
            raiz->esquerda = insere_no_artista(raiz->esquerda, novo_no);
        }else if(novo_no->artista.id > raiz->artista.id){
            raiz->direita = insere_no_artista(raiz->direita, novo_no);
        }else return raiz;
    }

    raiz = balancear_RB_artista(raiz);

    return raiz;
}