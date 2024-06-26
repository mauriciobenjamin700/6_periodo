#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME 50
#define TEXT 200
#define TITTEL 30
#define MAX(a, b) ((a > b) ? a : b)

typedef struct Participante
{
    char nomeArtista[NAME];
    char nomePersonagem[NAME];
    char descPersonagem[TEXT];
    struct Participante *prox;

} Participante;

typedef struct Temporada
{
    int num;
    char titulo[NAME];
    int qtd_episodios;
    int ano;
    struct Participante *lista;
    int altura;
    int fb;
    struct Temporada *direita;
    struct Temporada *esquerda;

} Temporada;

typedef struct Serie
{
    int cod;
    char titulo[TITTEL];
    int numTemp;
    struct Temporada *t;

    // ponteiros para os elementos da esquerda e direita ao montar a arvore
    int altura;
    int fb;
    struct Serie *esquerda;
    struct Serie *direita;

} Serie;
/////////////////// Serie//////////////////

int altura_Serie(Serie *s)
{
    return (s == NULL) ? 0 : s->altura;
}

int calcularFB_Serie(Serie *s)
{
    return altura_Serie(s->esquerda) - altura_Serie(s->direita);
}

void atualizarAltura_Serie(Serie *s)
{
    if (s != NULL)
    {
        s->altura = 1 + MAX(altura_Serie(s->esquerda), altura_Serie(s->direita));
    }
}

Serie *rotacaoDireita_Serie(Serie *s)
{
    Serie *aux = s->esquerda;
    Serie *aux2 = aux->direita;

    aux->direita = s;
    s->esquerda = aux2;

    atualizarAltura_Serie(s);
    atualizarAltura_Serie(aux);

    return aux;
}

Serie *rotacaoEsquerda_Serie(Serie *s)
{
    Serie *aux = s->direita;
    Serie *aux2 = aux->esquerda;

    aux->esquerda = s;
    s->direita = aux2;

    atualizarAltura_Serie(s);
    atualizarAltura_Serie(aux);

    return aux;
}

int iniciarS(Serie **s)
{
    *s = (Serie *)malloc(sizeof(Serie));
    int sinal = 0;
    if (s)
    {
        *s = NULL;
        sinal = 1;
    }

    return sinal;
}

void preencherS(Serie **s, int id, char titulo[])
{
    // printf("\nPrencha as inforamções da Serie a baixo.");

    *s = (Serie *)malloc(sizeof(Serie)); // Aloca memória para a nova série

    (*s)->cod = id;

    strcpy(((*s)->titulo), titulo);

    /*
    printf("\nNumero de Temporadas: ");
    setbuf(stdin,NULL);
    scanf("%d", &(*s)->numTemp);
    */
    (*s)->numTemp = 0;
    (*s)->t = NULL;
    (*s)->direita = NULL;
    (*s)->esquerda = NULL;
}

void mostrarS(Serie *s)
{
    printf("\n\n----------------------------");
    printf("\nCodigo: %d", s->cod);
    printf("\nSerie: %s", s->titulo);
    printf("\nNumero de Temporadas: %d\n", s->numTemp);
    printf("----------------------------");
}

int cadastrarS(Serie **s, Serie *novo)
{
    int sinal = 0;

    if (*s == NULL)
    {
        *s = novo;
        sinal = 1;
    }
    else if (novo->cod > (*s)->cod)
    {
        sinal = cadastrarS(&(*s)->direita, novo);
    }
    else if (novo->cod < (*s)->cod)
    {
        sinal = cadastrarS(&(*s)->esquerda, novo);
    }

    atualizarAltura_Serie(*s);
    int fb = calcularFB_Serie(*s);

    // Rebalanceamento da árvore
    if (fb == 2 && novo->cod < (*s)->esquerda->cod)
    {
        *s = rotacaoDireita_Serie(*s);
    }
    else if (fb == -2 && novo->cod > (*s)->direita->cod)
    {
        *s = rotacaoEsquerda_Serie(*s);
    }
    else if (fb == 2 && novo->cod > (*s)->esquerda->cod)
    {
        (*s)->esquerda = rotacaoEsquerda_Serie((*s)->esquerda);
        *s = rotacaoDireita_Serie(*s);
    }
    else if (fb == -2 && novo->cod < (*s)->direita->cod)
    {
        (*s)->direita = rotacaoDireita_Serie((*s)->direita);
        *s = rotacaoEsquerda_Serie(*s);
    }

    return sinal;
}

int validarS(Serie *s, int id)
{
    int sinal = 0;
    if (s != NULL)
    {
        if (s->cod == id)
        {
            sinal = 1;
        }

        else if (id > s->cod)
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

Serie *buscarS(Serie *s, int id)
{
    Serie *sinal = NULL;

    if (s != NULL)
    {
        if (s->cod == id)
        {
            sinal = s;
        }

        else if (id > s->cod)
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

int geraId(Serie **s)
{
    srand(1);
    int n;
    do
    {
        n = rand() % 10000 + 1;

    } while (validarS((*s), n));

    return n;
}

void mostrar_all_S(Serie **s)
{
    if (*s != NULL)
    {

        mostrar_all_S(&(*s)->esquerda);
        mostrarS(*s);
        mostrar_all_S(&(*s)->direita);
    }
}

void liberar_all_P(Participante **p)
{
    if (*p != NULL)
    {
        Participante *aux = (*p)->prox;
        free(*p);
        liberar_all_P(&aux);
    }
}

void liberar_all_T(Temporada **t)
{
    if (*t != NULL)
    {
        liberar_all_T(&(*t)->esquerda);
        liberar_all_T(&(*t)->direita);
        liberar_all_P(&(*t)->lista);
        free(*t);
    }
}

void liberar_all_S(Serie **s)
{
    if (*s != NULL)
    {
        liberar_all_S(&(*s)->esquerda);
        liberar_all_S(&(*s)->direita);
        liberar_all_T(&(*s)->t);
        free(*s);
    }
}

///////////Temporada ///////////////
int altura_Temporada(Temporada *t)
{
    return (t == NULL) ? 0 : t->altura;
}

int calcularFB_Temporada(Temporada *t)
{
    return altura_Temporada(t->esquerda) - altura_Temporada(t->direita);
}

void atualizarAltura_Temporada(Temporada *t)
{

    if (t != NULL)
    {
        t->altura = 1 + MAX(altura_Temporada(t->esquerda), altura_Temporada(t->direita));
    }
}

Temporada *rotacaoDireita_Temporada(Temporada *t)
{
    Temporada *aux = t->esquerda;
    Temporada *aux2 = aux->direita;

    aux->direita = t;
    t->esquerda = aux2;

    atualizarAltura_Temporada(t);
    atualizarAltura_Temporada(aux);

    return aux;
}

Temporada *rotacaoEsquerda_Temporada(Temporada **t)
{
    Temporada *aux = (*t)->direita;
    (*t)->direita = aux->esquerda;
    aux->esquerda = *t;
    atualizarAltura_Temporada(*t);
    atualizarAltura_Temporada(aux);

    return aux;
}

void troca(Participante **a, Participante **b)
{
    Participante *temp = *a;
    *a = *b;
    *b = temp;
}
/*
int comparaNomes(char name1[], char name2[])
{
    for (int i = 0; name1[i] && name2[i]; i++)
    {
        if (name1[i] < name2[i])
        {
            return -1;
        }
        else if (name1[i] > name2[i])
        {
            return 1;
        }
    }

    return 0; // Os nomes são iguais até onde foram comparados
}
*/
void OrdenaAtores(Participante **head)
{
    Participante *i, *j;
    Participante *min;

    for (i = *head; i != NULL; i = i->prox)
    {
        min = i;
        for (j = i->prox; j != NULL; j = j->prox)
        {
            // compara o primeiro com o segundo, retorna -1,0 e 1 caso primeiro seja menor, igual, maior
            if (strcmp(j->nomeArtista, min->nomeArtista) == -1)
            // if (comparaNomes(j->nomeArtista, min->nomeArtista) < 0)
            {
                min = j;
                troca(&i, &min);
            }
        }
    }
}

void cadastran_atores(Participante **l, int n_atores)
{
    if (n_atores == 1)
    {
        printf("\nNome do Artista: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", (*l)->nomeArtista);
        setbuf(stdin, NULL);
        printf("\nNome do Personagem:");
        scanf("%[^\n]", (*l)->nomePersonagem);
        printf("\nDescrição do Personagem:");
        setbuf(stdin, NULL);
        scanf("%[^\n]", (*l)->descPersonagem);
        (*l)->prox = NULL;
    }
    else if (n_atores > 1)
    {
        printf("\nNome do Artista: ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", (*l)->nomeArtista);
        setbuf(stdin, NULL);
        printf("\nNome do Personagem:");
        scanf("%[^\n]", (*l)->nomePersonagem);
        printf("\nDescrição do Personagem:");
        setbuf(stdin, NULL);
        scanf("%[^\n]", (*l)->descPersonagem);

        Participante *p;
        p = (Participante *)malloc(sizeof(Participante));

        (*l)->prox = p;
        cadastran_atores(&((*l)->prox), n_atores - 1);
    }
}

void preencherT(Temporada **t, int id)
{
    int n_atores;
    printf("\nPrencha as inforamções da Temporada a baixo:\n");

    *t = (Temporada *)malloc(sizeof(Temporada)); // Aloca memória para a nova série

    (*t)->num = id;

    printf("\nTitulo da Temporada: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]", (*t)->titulo);

    printf("\nNumero de Episodios: ");
    setbuf(stdin, NULL);
    scanf("%d", &(*t)->qtd_episodios);

    printf("\nAno: ");
    setbuf(stdin, NULL);
    scanf("%d", &(*t)->ano);

    printf("\nQuantidade de Atores: ");
    setbuf(stdin, NULL);
    scanf("%d", &n_atores);

    (*t)->lista = (Participante *)malloc(sizeof(Participante) * n_atores);
    cadastran_atores(&((*t)->lista), n_atores);
    OrdenaAtores(&((*t)->lista));
    (*t)->direita = NULL;
    (*t)->esquerda = NULL;
}

int cadastrarT(Temporada **t, int id)
{
    int sinal = 0;

    if (*t == NULL)
    {
        Temporada *novo;
        preencherT(&novo, id);
        (*t) = novo;
        sinal = 1;
    }
    else if (id > (*t)->num)
    {
        sinal = cadastrarT(&((*t)->direita), id);
    }
    else if (id < (*t)->num)
    {
        sinal = cadastrarT(&((*t)->esquerda), id);
    }

    atualizarAltura_Temporada(*t);
    int fb = calcularFB_Temporada(*t);

    // Rebalanceamento da árvore
    if (fb == 2 && id < (*t)->esquerda->num)
    {
        *t = rotacaoDireita_Temporada(*t);
    }
    else if (fb == -2 && id > (*t)->direita->num)
    {
        *t = rotacaoEsquerda_Temporada(&(*t));
    }
    else if (fb == 2 && id > (*t)->esquerda->num)
    {
        printf("\n450");
        (*t)->esquerda = rotacaoEsquerda_Temporada(&((*t)->esquerda));
        printf("452");
        *t = rotacaoDireita_Temporada(*t);
        printf("454");
    }
    else if (fb < -1 && id < (*t)->direita->num)
    {
        (*t)->direita = rotacaoDireita_Temporada((*t)->direita);
        *t = rotacaoEsquerda_Temporada(&(*t));
    }

    return sinal;
}

void mostrarT(Temporada *t)
{
    printf("\n-----------------------------------------------");
    printf("\nTemporada: %d", t->num);
    printf("\nTitulo: %s", t->titulo);
    printf("\nQuantidade de eps: %d", t->qtd_episodios);
    printf("\nAno: %d\n", t->ano);
    printf("-----------------------------------------------");
}

Temporada *buscarT(Temporada *t, int id)
{
    Temporada *sinal = NULL;

    if (t != NULL)
    {
        if (t->num == id)
        {
            sinal = t;
        }

        else if (id > t->num)
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
        mostrarT(t);
        mostrar_all_T(t->direita);
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

void mostrar_all_P(Participante *p)
{
    if (p != NULL)
    {
        mostrarP(p);
        mostrar_all_P(p->prox);
    }
}

void letra_D(Temporada *t)
{
    if (t != NULL)
    {
        letra_D(t->esquerda);
        letra_D(t->direita);
        mostrar_all_P(t->lista);
    }
}
