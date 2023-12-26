#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmp.c"
#include "musica.h"

#define TAM_TITULO 50

typedef struct Musica
{
    char titulo[TAM_TITULO];
    float minutos;
} Musica;

typedef struct Lista_musicas
{
    Musica musica;
    struct Lista_musicas *proximo_no;
    struct Lista_musicas *anterior_no;

} Lista_musicas;

/*
Preenche os campos de uma estrutura Musica com seus respectivos campos

Args:
    musica::Musica*: Ponteiro para uma variável do tipo Musica que será preenchido;
    titulo::char: Titulo da musica;
    float::minutos: Duração da musica em minutos.

Return:
    None
*/
void preencher_musica(Musica *musica, char titulo[], float minutos)
{
    musica->minutos = minutos;
    strcpy(musica->titulo, titulo);
}

/*
Aloca memória para um nó do tipo Lista_musicas;
Caso a aloacão seja um sucesso, cria um nó do tipo Lista_musicas com titulo vazio e duração de 0.
Caso contrario retorna NULL

Args:
    None

Return:
    Lista::Lista_musicas: Nó para uma lista de musicas.
*/
Lista_musicas *iniciar_no_lista()
{
    Lista_musicas *lista = (Lista_musicas *)malloc(sizeof(Lista_musicas));

    if (lista)
    {
        char t[1] = {""};
        preencher_musica(&(lista->musica), t, 0);
        lista->anterior_no = NULL;
        lista->proximo_no = NULL;
    }
    else
        lista = NULL;

    return lista;
}

/*
Adiciona uma musica na lista de musicas passada por parâmetro e retorna uma sinalização de acordo com o resultado obtido.
Tipos de sinalização:
    1 - Sucesso ao adicionar;
    0 - Falha ao adicionar;
   -1 - Musica já estava cadastrada.

Args:
    raiz::Lista_musicas: Referência do ponteiro que guarda o início da lista de musicas;
    musica::Musica*: Ponteiro para uma música que será copiada e guardada na lista de musicas.

Retorno:
    insere::int: Valor inteiro representando o resultado da operação de inserção
*/
int adicionar_musica_ordenada(Lista_musicas **raiz, Musica *musica)
{
    int insere = 0;

    if ((*raiz)->musica.minutos == 0)
    {
        (*raiz)->musica = *musica;
        insere = 1;
    }
    else
    {
        Lista_musicas *aux = *raiz;
        int result;
        while (insere == 0)
        {
            // compara a primeira com a segunda e retorna 0 caso sejam iguais, num < 0 caso a primeira seja menor ou n > 0 caso o primeiro seja maior que o segundo.
            //  -a-b-c-f

            result = compara_string(musica->titulo, aux->musica.titulo);

            if (result == 0)
                insere = -1;

            else if (result < 0)
            {
                if (aux->anterior_no == NULL)
                {
                    Lista_musicas *new = iniciar_no_lista();
                    new->musica = *musica;
                    aux->anterior_no = new;
                    new->proximo_no = aux;
                    *raiz = new;
                    insere = 1;
                }
                else
                {
                    Lista_musicas *new = iniciar_no_lista();
                    new->musica = *musica;
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
                    new->musica = *musica;
                    aux->proximo_no = new;
                    new->anterior_no = aux;
                    insere = 1;
                }
                else
                {
                    if (aux->proximo_no != NULL)
                        aux = aux->proximo_no;
                    else
                    {
                        Lista_musicas *new = iniciar_no_lista();
                        new->musica = *musica;
                        new->anterior_no = aux;
                        aux->proximo_no = new;
                        insere = 1;
                    }
                }
            }
        }
    }

    return insere;
}

/*
Mostra todos os dados de uma música

Args:
    musica::Musica*: Ponteiro para uma música que será mostrada

Return:
    None
*/
void mostrar_musica(Musica *musica)
{
    if (musica->minutos != 0)
        printf("\n\n\tMUSICA:\n\n\t\tTITULO: %s\n\t\tDURACAO: %.2f", musica->titulo, musica->minutos);
}

/*
Mostra todos os dados de uma música contida em um nó da Lista ordenada de músicas.

Args:
    no::Lista_musicas*: Ponteiro para um no da Lista de musicas

Return:
    None
*/
void mostrar_no_musica(Lista_musicas *no)
{
    if (no != NULL)
        mostrar_musica(&no->musica);
}

/*
Mostra todos os dados de todas as musicas contida em uma Lista ordenada de músicas.

Args:
    no::Lista_musicas*: Ponteiro para um no da Lista de musicas

Return:
    None
*/
void mostar_todas_musicas(Lista_musicas *no)
{

    if (no != NULL)
    {
        Lista_musicas *aux = no;
        while (aux != NULL)
        {
            mostrar_musica(&(aux->musica));
            aux = aux->proximo_no;
        }
    }
}


/*
Busca um nó musica dentro de uma lista de músicas com base no título da musica

Args:
    raiz::Lista_musicas*: Raiz da lista de musicas que iremos percorrer visando encontrar a música buscada.
    titulo::char: Título da Musica que estamos buscando.

Return:
    aux::Lista_musicas*: Apontamento para o nó da musica buscada em casa de sucesso na busca ou NULL caso a musica não seja encontrada
*/
Lista_musicas *buscar_no_musica(Lista_musicas *raiz, char titulo[])
{
    Lista_musicas *aux = raiz;
    int sinal = 0;
    int result;

    while (sinal == 0)
    {
        if (aux == NULL)
            sinal = 1;
        else if (aux != NULL)
        {
            result = compara_string(aux->musica.titulo, titulo);

            if (result == 0)
                sinal = 1;
            else
                aux = aux->proximo_no;
        }
    }
    return aux;
}

/*
Busca uma musica dentro de uma lista de músicas com base no título da musica

Args:
    raiz::Lista_musicas*: Raiz da lista de musicas que iremos percorrer visando encontrar a música buscada.
    titulo::char: Título da Musica que estamos buscando.

Return:
    musica_buscada::Musica*: Apontamento para a musica buscada em casa de sucesso na busca ou NULL caso a musica não seja encontrada
*/
Musica *buscar_musica(Lista_musicas *raiz, char titulo[])
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
            result = compara_string(aux->musica.titulo, titulo);

            if (result == 0)
            {
                musica_buscada = &(aux->musica);
                sinal = 1;
            }
            else
                aux = aux->proximo_no;
        }
    }

    return musica_buscada;
}

/*
Remove uma música da lista de musicas e sinaliza o resultado da remoção:
    0 - Fracasso
    1 - Sucesso

Args:
    raiz::Lista_musicas**: Referência da raiz da lista de musicas
    titulo::char: Titulo da musica que estamos querendo remover

Return:
    sinal::int: Sinalização referente ao resultado da operação 
*/
int remover_musica(Lista_musicas **raiz, char titulo[])
{
    int sinal = 0;

    Musica *musica = buscar_musica(*raiz, titulo);

    if (musica != NULL)
    {
        Lista_musicas *aux = *raiz;
        // Procura todas as musicas até achar a correta
        while (compara_string(aux->musica.titulo, musica->titulo) != 0)
        {
            aux = aux->proximo_no;
        }
        // caso seja o unico elemento da lista
        if (aux->anterior_no == NULL && aux->proximo_no == NULL)
        {
            char t[1] = {""};
            preencher_musica(&(aux->musica), t, 0);
            sinal = 1;
        }
        // caso seja o primeiro elemento da lista
        else if (aux->anterior_no == NULL && aux->proximo_no != NULL)
        {
            *raiz = aux->proximo_no;
            free(aux);
            sinal = 1;
        }
        // caso esteja no meio da lista
        else if (aux->anterior_no != NULL && aux->proximo_no != NULL)
        {

            aux->anterior_no->proximo_no = aux->proximo_no;
            aux->proximo_no->anterior_no = aux->anterior_no;
            free(aux);
            sinal = 1;
        }
        // caso seja o ultimo elemento da lista
        else if (aux->anterior_no != NULL && aux->proximo_no == NULL)
        {
            aux->anterior_no->proximo_no = NULL;
            free(aux);
            sinal = 1;
        }
    }

    return sinal;
}

/*
Remove todas as músicas de uma lista de musicas:
    
Args:
    raiz::Lista_musicas**: Referência da raiz da lista de musicas
    
Return:
    None
*/
void remover_todas_musicas(Lista_musicas **raiz)
{
    if (*raiz != NULL)
    {
        Lista_musicas *aux = *raiz;
        Lista_musicas *auxProx;

        while (aux != NULL)
        {
            auxProx = aux->proximo_no;
            free(aux);
            aux = auxProx;
        }
        *raiz = NULL;
    }
}