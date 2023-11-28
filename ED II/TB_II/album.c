#include <stdio.h>
#include <stdlib.h>


typedef struct Info_Artista
{
    char nome[50];
    char tipo[10];
    char estilo[30];
    int num_albuns;
    struct Album * Album;

}Info_Artista;


typedef struct Artista
{

}Artista;
