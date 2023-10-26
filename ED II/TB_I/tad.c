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

    struct Temporada* direita;
    struct Temporada* esquerda;

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
/////////////////// Serie//////////////////

void iniciarS(Serie** s)
{
    *s = (Serie*) malloc(sizeof(Serie));

    if (s)
    {
        
        *s = NULL;
    } 
}

void preencherS(Serie **s, int id)
{
    printf("\nPrencha as inforamções da Serie a baixo.");

    *s = (Serie *)malloc(sizeof(Serie)); // Aloca memória para a nova série

    (*s)->cod = id;

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

int cadastrarS(Serie **s, int id)
{
    int sinal = 0;



    if(*s == NULL)
    {
        Serie* new;
        preencherS(&new, id);
        *s = new;
        sinal = 1;
    }
    // vamos salvar as series com o maior para a direita e o menor para esquerda
    else if (id > (*s)->cod)
    {
        sinal = cadastrarS(&(*s)->direita, id);
    }

    else
    {
        sinal = cadastrarS(&(*s)->esquerda, id);
    }

    return sinal;
}

int buscarS(Serie *s, int id)
{
    int sinal = 0;
    if(s != NULL)
    {
        if (s->cod == id)
        {
            sinal = 1;
        }
        // todos os ID pares ficam a direita
        else if(id > s->cod)
        {
            sinal = buscarS(s->direita, id);
        }
        //se o ID não for par, então é impar, logo vamos pra esquerda
        else
        {
            sinal = buscarS(s->esquerda, id);
        }
    }

    return sinal;
}

int geraId(Serie **s){
    srand(1);
    int n;
    do{
        n = rand()%100+1;

    }while(buscarS((*s),n));
    
    return n;
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

void liberar_all_S(Serie **s)
{
    if (*s != NULL)
    {
        liberar_all_S(&(*s)->esquerda);
        liberar_all_S(&(*s)->direita);
        free(&(*s));
        printf("\nremovi\n");
    }
    
}

///////////Temporada ///////////////




void preencherT(Temporada **t, int num)
{
    printf("\nPrencha as inforamções da Temporada a baixo.");

    *t = (Temporada *)malloc(sizeof(Temporada)); // Aloca memória para a nova série

    (*t)->num = num;

    printf("\nTitulo da Temporada: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]", (*t)->titulo);
    
    printf("\nNumero de Temporadas: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*t)->qtd_episodios);

    printf("\nAno: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*t)->ano);

    (*t)->lista = NULL;

    (*t)->direita = NULL;
    (*t)->esquerda = NULL;
}

/*
int cadastrarT(Serie** s)
{
    
    Para cadastrar um temporada, deve existir uma serie
    buscar se a serie existe
    se existir, verificar quantas temporadas tem
    cada temporada par fica a direita da arvore
    cada temporada impar fica a esquerda da arvore
    
    int sinal = 0;
    

    if((*s)->t == NULL)
    {
        Temporada* new;
        preencherT(&new);
        (*s)->t = new;
        sinal = 1;
    }
    // vamos salvar as Tempordas com id par a direita e os impares a esquerda
    else if ((*s)->numTemp % 2 == 0)
    {
        sinal = cadastrarT(&(*t)->direita);
    }

    else
    {
        sinal = cadastrarT(&(*t)->esquerda);
    }

    return sinal;
}
*/