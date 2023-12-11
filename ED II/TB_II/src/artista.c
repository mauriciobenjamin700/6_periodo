#include <stdio.h>
#include <stdlib.h>
#include "musica.c"
#include "album.c"
#define VERMELHO 1
#define PRETO 0 

typedef struct Artista
{
    char nome[50];
    char tipo[20];
    char estilo[20];
    int num_albuns;
    Album * Album;

}Artista;


typedef struct RB_artista
{
    int id;
    int cor;

    Artista *artista;
    struct RB_artista *esquerda;
    struct RB_artista *direita;
    
}RB_artista;




