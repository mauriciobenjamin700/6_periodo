#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

# define NAME 50
# define TEXT 200
# define TITTEL 30

typedef struct participante
{
    char nomeArtista[NAME];
    char nomePersonagem[NAME];
    char descPersonagem[TEXT];

}Participante;

typedef struct 
{
    int num;
    char titulo[NAME];
    int qtd_episodios;
    int ano;
    struct Participante *lista;

}Temporada;

typedef struct 
{
    int cod;
    char titulo[TITTEL];
    int numTemp;
    struct Temporada *t;

    //ponteiros para os elementos da esquerda e direita ao montar a arvore

    struct Serie* esquerda;
    struct Serie* direita;

}Serie;

int iniciarS(Serie* s)
{
    int sinal = 0;

    s = (Serie*) malloc(sizeof(Serie));

    if (s)
    {
        sinal = 1;
        s = NULL;
    } 

    return sinal;

}

void preencherS(Serie **s)
{
    printf("\nPrencha as inforamções da Serie a baixo.");

    *s = (Serie *)malloc(sizeof(Serie)); // Aloca memória para a nova série

    printf("\nCodigo: ");
    setbuf(stdin,NULL);
    scanf("%d", &((*s)->cod));

    printf("\nTitulo da Serie: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]", (*s)->titulo);
    
    printf("\nNumero de Temporadas: ");
    setbuf(stdin,NULL);
    scanf("%d", &((*s)->numTemp));
    
    (*s)->t = NULL;

    (*s)->direita = NULL;
    (*s)->esquerda = NULL;
}

int cadastrarS(Serie** s)
{
    int sinal = 0;
    Serie* new;

    preencherS(&new);

    if(*s == NULL)
    {
        *s = new;
        sinal = 1;
    }
    //ordenação por código, se o código do novo for maior que o da raiz, vamos para a esquerda
    else if (new->cod < (*s)->cod)
    {
        sinal = cadastrarS((*s)->esquerda);
    }
    // se o código do novo não é menor que o codigo da raiz, então vamos para a direita
    else
    {
        sinal = cadastrarS((*s)->direita);
    }

    return sinal;
}

void mostarS (Serie s)
{
    printf("\nSerie: %s", s.titulo);
    printf("\nCodigo: %d", s.cod);
    printf("\nNumero de Temporadas: %d", s.numTemp);
}
