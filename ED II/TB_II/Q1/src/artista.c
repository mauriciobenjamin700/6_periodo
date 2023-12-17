#include <stdio.h>
#include <stdlib.h>
#include "musica.c"
#include "album.c"
#define VERMELHO 1
#define PRETO 0 

#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{
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

void preencher_artista(Artista *artista,char nome[NOME], char tipo[TIPO], char estilo[ESTILO], int num_albuns)
{
    strcpy(artista->nome,nome);
    strcpy(artista->tipo,tipo);
    strcpy(artista->estilo,estilo);
    artista->num_albuns = num_albuns;
}

RB_artista * cria_no_artista(int cor,Artista artista)
{
    RB_artista *no;
    no = (RB_artista *)malloc(sizeof(RB_artista));

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


