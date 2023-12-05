#include <stdio.h>
#include "musica.c"

typedef struct Album
{
    char titulo[50];
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
