#include <stdio.h>
#include <string.h>
#include "musica.c"

#define TAM_TITULO 50

typedef struct Album
{
    char titulo[TAM_TITULO];
    int ano;
    int qtd_musicas;
    Lista_musicas *musicas;

}Album;


typedef struct RB_album
{
    int id;
    int cor;
    Album *album;
    Album *esquerda;
    Album *direita;

}RB_album;

Album *criar_Album()
{
    Album *album;
    album = (Album *)malloc(sizeof(Album));

    if (!album)
        album = NULL;

    return album;
}

void preencher_album(Album *album,char titulo[TAM_TITULO], int ano)
{
    strcpy(album->titulo,titulo);
    album->ano = ano;
    album->qtd_musicas = 0;
    album->musicas = iniciar_no_lista();
}

int adiciona_musica_album(Album *album, Musica *musica)
{
    int adicionei = adicionar_musica_ordenada(&(album->musicas),musica);
    if(adicionei)
        album->qtd_musicas += 1; 
        //contar_musicas(album->musicas);

    return adicionei;
}

int remover_musica_album(Album *album,char titulo[TAM_TITULO])
{
    int removi = remover_musica(&(album->musicas),titulo);
    if (removi)
        album->qtd_musicas -= 1; 
        //contar_musicas(album->musicas);
    
    return removi;
}


RB_album * cria_no_album(int id,int cor,Album *album)
{
    RB_album *no;
    no = (RB_album *)malloc(sizeof(RB_album));

    if(no)
    {
        no->id = id;
        no->cor = cor;
        no->album = album;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;
    
    return no;
}