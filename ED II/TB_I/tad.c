#include <stdio.h>
#include <stdlib.h>

# define NAME 50
# define TEXT 200
# define TITTEL 30

typedef struct Participante
{
    char nomeArtista[NAME];
    char nomePersonagem[NAME];
    char descPersonagem[TEXT];

}Participante;

typedef struct Temporada
{
    int num;
    char titulo[NAME];
    int qtd_episodios;
    int ano;
    struct Participante *lista;

} Temporada;

typedef struct Serie
{
    int cod;
    char titulo[TITTEL];
    int numTemp;
    struct Temporada *t;

    //ponteiros para os elementos da esquerda e direita ao montar a arvore

    struct Serie* esquerda;
    struct Serie* direita;

} Serie;

int iniciarS(Serie** s)
{
    int sinal = 0;

    *s = (Serie*) malloc(sizeof(Serie));

    if (s)
    {
        sinal = 1;
        *s = NULL;
    } 

    return sinal;

}

void preencherS(Serie **s)
{
    printf("\nPrencha as inforamções da Serie a baixo.");

    *s = (Serie *)malloc(sizeof(Serie)); // Aloca memória para a nova série

    printf("\nCodigo: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*s)->cod);

    printf("\nTitulo da Serie: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]", (*s)->titulo);
    
    printf("\nNumero de Temporadas: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*s)->numTemp);
    
    (*s)->t = NULL;

    (*s)->direita = NULL;
    (*s)->esquerda = NULL;
}

int cadastrarS(Serie** s)
{
    int sinal = 0;
    Serie* new;

    if(*s == NULL)
    {
        preencherS(&new);
        *s = new;
        sinal = 1;
    }
    // vamos salvar as series com id par a direita e os impares a esquerda
    else if ((*s)->cod % 2 == 0)
    {
        cadastrarS(&(*s)->direita);
    }

    else
    {
        cadastrarS(&(*s)->esquerda);
    }
    

    return sinal;
}

void mostarS (Serie *s)
{
    printf("\nSerie: %s", s->titulo);
    printf("\nCodigo: %d", s->cod);
    printf("\nNumero de Temporadas: %d\n", s->numTemp);
}

void mostrar_all_S(Serie **s)
{
    if (*s != NULL)
    {
        mostarS(*s);
        mostrar_all_S(&(*s)->esquerda);
        mostrar_all_S(&(*s)->direita);
    }
    
}
