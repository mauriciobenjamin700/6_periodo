#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica
{
    char titulo[50];
    float minutos;
} Musica;


typedef struct Lista_musicas
{
    Musica *musica;
    Musica *proxima;
    Musica *anterior;

} Lista_musicas;

Musica *criar_musica()
{
    Musica *musica;
    musica = (Musica *)malloc(sizeof(Musica));

    if (!musica)
        musica = NULL;

    return musica;
}

void preencher_musica(Musica *musica, char titulo[], float minutos)
{
    musica->minutos = minutos;
    strcpy(musica->titulo,titulo);    
}

Lista_musicas *iniciar_lista()
{
    Lista_musicas *lista = (Lista_musicas *)malloc(sizeof(Lista_musicas));


    if (lista)
    {
        lista->musica = NULL;
        lista->anterior = NULL;
        lista->proxima = NULL;
    }
    else 
        lista = NULL;
        

    return lista;
}
// Falta fazer
int adicionar_musica(Lista_musicas **raiz, Musica *musica)
{
    int sinal = 0;

    if((*raiz)->musica == NULL)
    {
        (*raiz)->musica = musica;
        sinal = 1;
    }

    return sinal;
    
}