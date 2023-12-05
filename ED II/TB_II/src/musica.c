#include <stdio.h>

typedef struct Musica
{
    char titulo[50];
    float minutos;

}Musica;

typedef struct Lista_musicas 
{
    Musica *musica;
    Musica *proxima;
    Musica *anterior;

}Lista_musicas;