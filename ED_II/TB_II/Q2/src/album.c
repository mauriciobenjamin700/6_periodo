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

typedef struct Arv_23_album
{
    Album album;
    struct Arv_23_album *esquerda;
    struct Arv_23_album *direita;
    int cor;

} Arv_23_album;


