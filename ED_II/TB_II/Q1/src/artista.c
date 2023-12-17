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
    RB_album *Album;

}Artista;

typedef struct RB_artista
{
    int id;
    int cor;
    Artista artista;
    struct RB_artista *esquerda;
    struct RB_artista *direita;
    
}RB_artista;




