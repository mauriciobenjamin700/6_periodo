#include <stdio.h>
#include "tad.h"

# define NAME 50

struct Participante
{
    char nomeArtista[NAME];
    char nomePersonagem[NAME];
    char descPersonagem[200];

};


struct Temporada
{
    int num;
    char titulo[NAME];
    int qtd_episodios;
    int ano;
    struct Participante *lista;
};


struct Serie
{
    int cod;
    char titulo[NAME];
    int numTemp;
    struct Temporada *t;

};
