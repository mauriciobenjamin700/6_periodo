#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica
{
    char titulo[50];
    float minutos;
}Musica;


typedef struct Lista_musicas
{
    Musica *musica;
    struct Lista_musicas *proximo_no;
    struct Lista_musicas *anterior_no;

}Lista_musicas;

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
int adicionar_musica_final(Lista_musicas **raiz, Musica *musica)
{
    int sinal = 0;
    Lista_musicas *aux = *raiz;

    if((aux)->musica == NULL)
    {
        (aux)->musica = musica;

        sinal = 1;
    }
    else
    {
        while (aux->proximo_no != NULL)
        {
            aux = aux->proximo_no;
        }

        aux->proximo_no->musica = musica;
        aux->proximo_no->anterior_no = aux; 
        aux->proximo_no->proximo_no = NULL;
        
    }

    return sinal;
    
}

// b, a
int adicionar_musica_ordenada(Lista_musicas **raiz, Musica *musica)
{
    int sinal = 0;
    Lista_musicas *aux = *raiz;
    
    if((aux)->musica == NULL)
    {
        (aux)->musica = musica;

        sinal = 1;
    }
    else
    {
        
        Lista_musicas *new = iniciar_no_lista();
        int resultado;

        for(aux = *raiz;((aux != NULL) && (sinal==0));aux = aux->proximo_no)
        {
            resultado = strcmp(musica->titulo,aux->musica->titulo);
            //caso o primeiro venha antes do segundo (nesse caso, caso o novo nó seja inserido antes do nó atual)
            if (resultado==-1)
            {
                //Criamos um novo nó para guardar a musica antiga
                new->musica = aux->musica;
                //o nó que guardava a musica antiga agora ira guardar a nova musica
                aux->musica = musica;
                //a musica antiga vai apontar para tras onde tem a nova musica
                new->anterior_no = aux;
                // o proximo nó da musica antiga continua sendo o proximo nó que ja existia antigamente
                new->proximo_no = aux->proximo_no;
                //o proximo no da nova musica sera a musica antiga
                aux->proximo_no = new;

                sinal = 1;
            }
            //caso não venha antes, vai sempre depois no nosso caso

            aux = aux->proximo_no;
        }
        
        if (sinal == 0)
        {
            new->musica = musica;
            new->anterior_no = aux;
            aux->proximo_no = new;     
            sinal = 1;
        }
    }

    return sinal;
    
}

void mostar_musica(Musica *musica)
{
    if(musica == NULL)
        printf("\nZero musicas cadastradas");
    else
        printf("\n\nTitulo: %s\nTempo: %.2f",musica->titulo,musica->minutos);
}

void mostar_todas_musicas(Lista_musicas *no)
{
    Lista_musicas *aux = no;

    if(aux == NULL)
        printf("\nZero musicas cadastradas");
    else
    {
        while(aux!=NULL)
        {
            mostar_musica(aux->musica);
            aux = aux->proximo_no;
        }
    }
}