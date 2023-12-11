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
    struct Lista_musicas *proximo_no;
    struct Lista_musicas *anterior_no;

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
    strcpy(musica->titulo, titulo);
}

Lista_musicas *iniciar_no_lista()
{
    Lista_musicas *lista = (Lista_musicas *)malloc(sizeof(Lista_musicas));

    if (lista)
    {
        lista->musica = NULL;
        lista->anterior_no = NULL;
        lista->proximo_no = NULL;
    }
    else
        lista = NULL;

    return lista;
}
// Adiciona no final


int adicionar_musica_ordenada(Lista_musicas **raiz, Musica *musica)
{
    int insere = 0;
    Lista_musicas *aux = *raiz;

    if ((aux)->musica == NULL)
    {
        (aux)->musica = musica;
        insere = 1;
    }

    while (insere == 0)
    {
        //compara a primeira com a segunda e retorna 0 caso sejam iguais, num < 0 caso a primeira seja menor ou n > 0 caso o primeiro seja maior que o segundo.

        int result = strcmp(musica->titulo, aux->musica->titulo);
        if (result == 0)
        {
            insere = 1;
        }
        else if (result < 0)
        {
            if (aux->anterior_no == NULL)
            {
                Lista_musicas *new = iniciar_no_lista();
                new->musica = musica;
                aux->anterior_no = new;
                new->proximo_no = aux;
                *raiz = new;
                insere = 1;
            }
            else
            {
                Lista_musicas *new = iniciar_no_lista();
                new->musica = musica;
                Lista_musicas *auxAnt = aux->anterior_no;
                aux->anterior_no = new;
                auxAnt->proximo_no = new;
                new->proximo_no = aux;
                new->anterior_no = auxAnt;
                insere = 1;
            }
        }
        else if (result > 0)
        {
            if (aux->proximo_no == NULL)
            {
                Lista_musicas *new = iniciar_no_lista();
                new->musica = musica;
                aux->proximo_no = new;
                new->anterior_no = aux;
                insere = 1;
            }
            else
            {
                if (aux->proximo_no != NULL)
                {
                    aux = aux->proximo_no;
                }
                else
                {
                    Lista_musicas *new = iniciar_no_lista();
                    new->musica = musica;
                    new->anterior_no = aux;
                    aux->proximo_no = new;
                    insere = 1;
                }
            }
        }
    }
    return insere;
}

void mostar_musica(Musica *musica)
{
    if (musica == NULL)
        printf("\nZero musicas cadastradas");
    else
        printf("\n\nTitulo: %s\nTempo: %.2f", musica->titulo, musica->minutos);
}

void mostar_todas_musicas(Lista_musicas *no)
{
    Lista_musicas *aux = no;

    if (aux == NULL)
        printf("\nZero musicas cadastradas");
    else
    {
        while (aux != NULL)
        {
            mostar_musica(aux->musica);
            aux = aux->proximo_no;
        }
    }
}

Musica* buscar_musica(Lista_musicas *raiz, char titulo[])
{
    Lista_musicas *aux = raiz;
    Musica *musica_buscada = NULL;
    int sinal = 0;
    int result;
    while (sinal == 0)
    {
        if (aux == NULL)
            sinal = 1;
        else if (aux != NULL)
        {
            result = strcmp(aux->musica->titulo,titulo);

            if (result == 0)
            {
                musica_buscada = aux->musica;
                sinal = 1;
            }
            else
                aux = aux->proximo_no;
        }
    }
    
    return musica_buscada;
}