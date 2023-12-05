#include <stdio.h>
#include <stdlib.h>
#include "musica.c"
#define VERMELHO 1
#define PRETO 0 

typedef struct RB_artista
{
    int id;
    int cor;
    Artista *artista;
    Artista *esquerda;
    Artista *direita;
    
}RB_artista;


typedef struct Artista
{
    char nome[50];
    char tipo[20];
    char estilo[20];
    int num_albuns;
    struct Album * Album;

}Artista;






