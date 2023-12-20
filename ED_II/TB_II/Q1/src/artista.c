#include "album.c"

#define VERMELHO 1
#define PRETO 0

#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{
    char nome[NOME];
    char tipo[TIPO];
    char estilo[ESTILO];
    int num_albuns;
    RB_album * albuns;

} Artista;

typedef struct RB_artista
{
    int cor;

    Artista artista;
    struct RB_artista *esquerda;
    struct RB_artista *direita;

} RB_artista;

void preencher_artista(Artista *artista, char nome[NOME], char tipo[TIPO], char estilo[ESTILO])
{
    strcpy(artista->nome, nome);
    strcpy(artista->tipo, tipo);
    strcpy(artista->estilo, estilo);
    artista->num_albuns = 0;
    artista->albuns = NULL;
}

RB_artista *cria_no_artista(int cor, Artista artista)
{
    RB_artista *no = (RB_artista *)malloc(sizeof(RB_artista));

    if (no)
    {
        no->cor = cor;
        no->artista = artista;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

void trocar_cor(RB_artista *no)
{
    if (no != NULL)
    {
        no->cor = !no->cor;

        if (no->direita != NULL)
            no->direita->cor = !no->direita->cor;

        if (no->esquerda != NULL)
            no->esquerda->cor = !no->esquerda->cor;
    }
}

void trocar_cor_raiz(RB_artista *no)
{
    if (no != NULL)
    {
        no->cor = PRETO;
    }
}

int cor(RB_artista *no)
{
    int color = 0;
    if (no != NULL)
    {
        color = no->cor;
    }

    return color;
}

RB_artista *rotacao_direita_artista(RB_artista *raiz)
{
    RB_artista *aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_artista *rotacao_esquerda_artista(RB_artista *raiz)
{
    RB_artista *aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_artista *move2EsqRED(RB_artista *no)
{
    trocar_cor(no);
    if (cor(no->direita->esquerda) == VERMELHO)
    {
        no->direita = rotacao_direita_artista(no->direita);
        no = rotacao_esquerda_artista(no);
        trocar_cor(no);
    }
    return no;
}

RB_artista *move2DirRED(RB_artista *no)
{
    trocar_cor(no);
    if (cor(no->esquerda->esquerda) == VERMELHO)
    {
        no = rotacao_direita_artista(no);
        trocar_cor(no);
    }
    return no;
}

RB_artista *balancear_RB_artista(RB_artista *no)
{
    if (cor(no->direita) == VERMELHO)
    {
        no = rotacao_esquerda_artista(no);
    }

    if (no->esquerda != NULL && cor(no->direita) == VERMELHO && cor(no->esquerda->esquerda) == VERMELHO)
    {
        no = rotacao_direita_artista(no);
    }

    if (cor(no->esquerda) == VERMELHO && cor(no->direita) == VERMELHO)
    {
        trocar_cor(no);
    }

    return no;
}

void insere_no_artista(RB_artista **raiz, RB_artista *novo_no)
{
    if (*raiz == NULL)
    {
        *raiz = novo_no;
    }
    else
    {
        /*
            Nesse caso ele verifica se o id do artista é maior ou menor e
            segue até chegar na raiz nula, insere nela, o ultimo else é no caso de ser igual
            nesse caso a arvore permanece igual.
        */
        if (compara_string(novo_no->artista.nome,(*raiz)->artista.nome) < 0)
        {
            insere_no_artista(&(*raiz)->esquerda, novo_no);
        }
        else if (compara_string(novo_no->artista.nome,(*raiz)->artista.nome) > 0)
        {
            insere_no_artista(&(*raiz)->direita, novo_no);
        }
    }
    (*raiz) = balancear_RB_artista((*raiz));

}

RB_artista *busca_no_artista(RB_artista *raiz, char nome_artista[NOME])
{
    RB_artista *artista_buscado = NULL;

    if (raiz != NULL)
    {
        if (compara_string(nome_artista,raiz->artista.nome) == 0)
            artista_buscado = raiz;

        else if (compara_string(nome_artista,raiz->artista.nome) < 0)
            artista_buscado = busca_no_artista(raiz->esquerda,nome_artista);

        else
            artista_buscado = busca_no_artista(raiz->direita,nome_artista);
    }
 
    return artista_buscado;
}

void mostrar_artista(Artista artista)
{
    printf("\n---------------");
    printf("\nNOME: %s\nTIPO: %s\nESTILO: %s\nTOTAL DE ALBUNS: %d\nALBUNS: ",artista.nome,artista.tipo,artista.estilo,artista.num_albuns);
    mostrar_tudo_RB_album((artista.albuns));
    printf("\n---------------");
}


