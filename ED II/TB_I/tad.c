#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

# define NAME 50
# define TEXT 200
# define TITTEL 30
struct Participante
{
    char nomeArtista[NAME];
    char nomePersonagem[NAME];
    char descPersonagem[TEXT];

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
    char titulo[TITTEL];
    int numTemp;
    struct Temporada *t;
//<<<<<<< HEAD

};

int iniciarS(struct Serie* s)
{
    int sinal = 0;

    s = (struct Serie*) malloc(sizeof(struct Serie));

    if (s)
    {
        sinal = 1;
        s = NULL;
    } 

    

    return sinal;

}

void preencherS(struct Serie *s)
{
    printf("\nPrencha as inforamções da Serie a baixo.");

    printf("\nCodigo: ");
    scanf("%d", s->cod);

    printf("\nTitulo da Serie: ");
    scanf("%[^\n]", s->titulo);
    
    printf("\nNumero de Temporadas: ");
    scanf("%d", s->numTemp);
    
    s->t = NULL;
}

int cadastrarS(struct Serie* s)
{
    int sinal = 0;
    struct Serie* new;

    if(s == NULL)
    {
        s = new;
    }

    return sinal;
}
//=======
//};
//>>>>>>> 500bfe7be0e0a939d085e077998693c64e9e22b1
