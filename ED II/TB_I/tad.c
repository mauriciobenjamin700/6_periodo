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
    struct Participante *prox;

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

void mostrarS (Serie *s)
{
    printf("\n\n----------------------------");
    printf("\nCodigo: %d", s->cod);
    printf("\nSerie: %s", s->titulo);
    printf("\nNumero de Temporadas: %d\n", s->numTemp);
    printf("----------------------------");
}

int cadastrarS(Serie **s, Serie *new)
{
    int sinal = 0;


    if(*s == NULL)
    {
        *s = new;

        sinal = 1;
        mostrarS(new);
    }
    // vamos salvar as series com o maior para a direita e o menor para esquerda
    else if (new->cod > (*s)->cod)
    {
        sinal = cadastrarS(&(*s)->direita, new);
    }

    else
    {
        sinal = cadastrarS(&(*s)->esquerda, new);
    }

    return sinal;
}

int validarS(Serie *s, int id)
{
    int sinal = 0;
    if(s != NULL)
    {
        if (s->cod == id)
        {
            sinal = 1;
        }
        
        else if(id > s->cod)
        {
            sinal = validarS(s->direita, id);
        }
        
        else
        {
            sinal = validarS(s->esquerda, id);
        }
    }

    return sinal;
}

Serie* buscarS(Serie *s, int id)
{
    Serie *sinal = NULL;

    if(s != NULL)
    {
        if (s->cod == id)
        {
            sinal = s;
        }
        
        else if(id > s->cod)
        {
            sinal = buscarS(s->direita, id);
        }
        
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

    }while(validarS((*s),n));
    
    return n;
}



void mostrar_all_S(Serie **s)
{
    if (*s != NULL)
    {
        mostrarS(*s);
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

void cadastraAtores(Participante **l, int atores)
{
    if (atores == 1)
    {
        printf("\nNome do Artista: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]",(*l)->nomeArtista);
        setbuf(stdin, NULL);
        printf("\nNome do Personagem:");
        scanf("%[^\n]",(*l)->nomePersonagem);
        printf("\nDescrição do Personagem:");
        setbuf(stdin, NULL);
        scanf("%[^\n]",(*l)->descPersonagem);
        (*l)->prox = NULL;
    }
    else if(atores > 1){
        printf("\nNome do Artista: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]",(*l)->nomeArtista);
        setbuf(stdin, NULL);
        printf("\nNome do Personagem:");
        scanf("%[^\n]",(*l)->nomePersonagem);
        printf("\nDescrição do Personagem:");
        setbuf(stdin, NULL);
        scanf("%[^\n]",(*l)->descPersonagem);

        Participante *p;
        p = (Participante*) malloc(sizeof(Participante));

        (*l)->prox = p;
        cadastraAtores(&((*l)->prox),atores-1);


    }


}


void preencherT(Temporada **t)
{   int atores;
    printf("\nPrencha as inforamções da Temporada a baixo:\n");

    *t = (Temporada *)malloc(sizeof(Temporada)); // Aloca memória para a nova série

    printf("\nCodigo da temporada:");
    scanf("%d",&(*t)->num);

    printf("\nTitulo da Temporada: ");
    setbuf(stdin,NULL);
    scanf("%[^\n]", (*t)->titulo);
    
    printf("\nNumero de Episodios: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*t)->qtd_episodios);

    printf("\nAno: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*t)->ano);

    printf("\nQuantidade de Atores: ");
    setbuf(stdin,NULL);
    scanf("%d", &atores);

    (*t)->lista = (Participante *)malloc(sizeof(Participante) * atores);
    cadastraAtores(&((*t)->lista),atores);

    (*t)->direita = NULL;
    (*t)->esquerda = NULL;
}


int cadastrarT(Temporada **s)
{  
    int sinal = 0;
    

    if( *s == NULL)
    {
        Temporada* new;
        preencherT(&new);
        (*s) = new;
        sinal = 1;
    }
    // vamos salvar as Tempordas com id par a direita e os impares a esquerda
    else if ((*s)->num > 0)
    {
        sinal = cadastrarT(&((*s)->direita));
    }

    else
    {
        sinal = cadastrarT( &((*s)->esquerda));
    }

    return sinal;
}


void mostrarT (Temporada *t)
{
    printf("\n-----------------------------------------------");
    printf("\nIdentificacao: %d", t->num);
    printf("\nSerie: %s", t->titulo);
    printf("\nQuantidade de eps: %d", t->qtd_episodios);
    printf("\nAno: %d\n", t->ano);
    printf("-----------------------------------------------");
}


Temporada* buscarT(Temporada *t, int id)
{
    Temporada *sinal = NULL;

    if(t != NULL)
    {
        if (t->num == id)
        {
            sinal = t;
        }
        
        else if(id > t->num)
        {
            sinal = buscarT(t->direita, id);
        }
        
        else
        {
            sinal = buscarT(t->esquerda, id);
        }
    }

    return sinal;
}

void mostrar_all_T(Temporada *t)
{
    if (t != NULL)
    {
        
        mostrar_all_T(t->esquerda);
        mostrar_all_T(t->direita);
        mostrarT(t);
    }
    
}


void mostrarP(Participante *p)
{
    printf("\n-----------------------------------------------");
    printf("\nNome do Artista: %s", p->nomeArtista);
    printf("\nPersonagem: %s", p->nomePersonagem);
    printf("\nDescricao do Personagem: %s", p->descPersonagem);
    printf("\n-----------------------------------------------");
}

void mostrar_all_P(Participante * p)
{
    if (p != NULL)
    {
        mostrarP(p);
        mostrar_all_P(p->prox);
    }
}

