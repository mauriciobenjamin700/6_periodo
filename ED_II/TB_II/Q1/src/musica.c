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
Esta função tenta alocar um espaço de memoria para guardar uma música
Caso consiga, retorna o endereço alocado
Caso Falhe, retorna NULL;

Parâmetros:
    void;

Return :
    musica::(Musica || NULL): Retorna uma musica em caso de sucesso e NULL caso falhe.
*/


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
        char t[1] = {""};
        preencher_musica(&(lista->musica),t,0);
        lista->anterior_no = NULL;
        lista->proximo_no = NULL;
    }
    else
        lista = NULL;

    return lista;
}

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
            //compara a primeira com a segunda e retorna 0 caso sejam iguais, num < 0 caso a primeira seja menor ou n > 0 caso o primeiro seja maior que o segundo.
            // -a-b-c-f

            result = compara_string(musica->titulo, aux->musica.titulo);
            if (result == 0)
            {
                insere = 1;
            }
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
                    {
                        aux = aux->proximo_no;
                    }
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

void mostar_musica(Musica *musica)
{
    if (musica->minutos != 0)
        printf("\n\tTitulo: %s\n\tTempo: %.2f", musica->titulo, musica->minutos);
}

void mostar_todas_musicas(Lista_musicas *no)
{
    
    if (no == NULL)
        printf("\nZero musicas cadastradas");
    else
    {
        Lista_musicas *aux = no;
        while (aux != NULL)
        {
            mostar_musica(&(aux->musica));
            aux = aux->proximo_no;
        }
    }
}

int contar_musicas(Lista_musicas *raiz)
{
    int qtd = 0;

    if (raiz != NULL)
    {
        Lista_musicas *aux = raiz;
        while (aux != NULL)
        {
            qtd++;
            aux = aux->proximo_no;
        }
    }
    return qtd;
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
            result = compara_string(aux->musica.titulo,titulo);

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

//Não faz sentido editar as musicas pois são poucos campos, é melhor apenas remover e recadastrar;

int remover_musica(Lista_musicas **raiz, char titulo[])
{

    int sinal = 0;
    
    Musica *musica = buscar_musica(*raiz,titulo);

    if(musica != NULL)
    {
        Lista_musicas *aux = *raiz;
        //Procura todas as musicas até achar a correta
        while (compara_string(aux->musica.titulo,musica->titulo)!=0)
        {
            aux = aux->proximo_no;    
        }
        //caso seja o unico elemento da lista
        if(aux->anterior_no == NULL && aux->proximo_no == NULL)
        {
            char t[1] = {""};
            preencher_musica(&(aux->musica),t,0);
           sinal = 1;
        }
        // caso seja o primeiro elemento da lista
        else if(aux->anterior_no == NULL && aux->proximo_no != NULL)
        {
            //Lista_musicas *no_removido = aux;

           *raiz = aux->proximo_no;
            free(aux);
            sinal = 1;
        }
        //caso esteja no meio da lista
        else if(aux->anterior_no != NULL && aux->proximo_no != NULL)
        {

            aux->anterior_no->proximo_no = aux->proximo_no;
            aux->proximo_no->anterior_no = aux->anterior_no;
            free(aux);
            sinal = 1;
        }
        // caso seja o ultimo elemento da lista
        else if(aux->anterior_no != NULL && aux->proximo_no == NULL)
        {
            aux->anterior_no->proximo_no = NULL;
            free(aux);
            sinal = 1;
        }
    }

    return sinal;
}
void remover_todas_musicas(Lista_musicas **raiz)
{   
    if(*raiz != NULL)
    {
        Lista_musicas *aux = *raiz;
        Lista_musicas *auxProx;

        while (aux!=NULL)
        {
            auxProx = aux->proximo_no;
            free(aux);
            aux = auxProx;
        }
        *raiz = NULL;
        
    }
}