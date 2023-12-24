#include <stdio.h>
#include <string.h>
#include "musica.c"

#define TAM_TITULO 50
#define VERMELHO 1
#define PRETO 0

typedef struct Album
{
    char titulo[TAM_TITULO];
    int ano;
    int qtd_musicas;
    Lista_musicas *musicas;

} Album;

typedef struct RB_album
{
    int cor;
    Album album;
    struct RB_album *esquerda;
    struct RB_album *direita;

} RB_album;

//////////////////////////////////////////////////////////////////////////////////////////////////
/*
Preenche um album com seus respectivos dados

Args:
    album::Album*: Ponteiro para o album que será preenchido
    titulo::char: Titulo do album
    ano::int: Ano de publicação do album.

Return:
    None
*/
void preencher_album(Album *album, char titulo[TAM_TITULO], int ano)
{
    strcpy(album->titulo, titulo);
    album->ano = ano;
    album->qtd_musicas = 0;
    album->musicas = iniciar_no_lista();
}

/*
Adiciona uma música em um album e retorna uma sinalização de acordo com o resultado do processo.
Retornos possíveis:
     1 - Cadastrou
     0 - Não Cadastrou
    -1 - Já estava cadastrado

Args:
    album::Album*: Ponteiro para o album que armazenará a musica passada
    musica::Musica: Ponteiro para uma musica onde iremos copiar seus dados para o nosso album.
    
Return:
    adicionei::int: Sinalização de acordo com o resultado do processo. 

*/
int adiciona_musica_no_album(RB_album *album, Musica *musica)
{
    int adicionei = adicionar_musica_ordenada(&(album->album.musicas), musica);
    if (adicionei)
        album->album.qtd_musicas += 1;

    return adicionei;
}

/*
Busca um nó Lista_musicas dentro de um nó RB_album.

Args:
    album::RB_album*: Ponteiro para um nó RB_album 
    titulo::char: Título da musica que estamos buscando

Return:
    aux::Lista_musicas*: Apontamento para o nó da musica buscada em casa de sucesso na busca ou NULL caso a musica não seja encontrada

*/
Lista_musicas * buscar_musica_no_album(RB_album *album,char titulo[TAM_TITULO])
{

    return buscar_no_musica(album->album.musicas,titulo);
}

/*
Remove uma música da lista de musicas contida em um album e sinaliza o resultado da remoção:
    0 - Fracasso
    1 - Sucesso

Em caso de sucesso, decrementa a quantidade de musicas do album.

Args:
    album::Album*: Ponteiro para o album que terá uma musica removida.
    titulo::char: Titulo da musica que estamos querendo remover

Return:
    sinal::int: Sinalização referente ao resultado da operação 
*/
int remover_musica_album(Album *album, char titulo[TAM_TITULO])
{
    int removi = remover_musica(&(album->musicas), titulo);
    if (removi)
        album->qtd_musicas -= 1;

    return removi;
}

/*
Printa na tela todos os dados de um Album

Args:
    album::Album*: Ponteiro para o album que será impresso na tela

Return:
    None
*/
void mostrar_album(Album *album)
{
    if (album != NULL)
    {
        printf("\n\nALBUM:\n\tTITULO: %s\n\tANO: %d\n\tTOTAL DE MUSICAS: %d\n", album->titulo, album->ano, album->qtd_musicas); 
        mostar_todas_musicas(album->musicas);   
    }
}

/*
Printa na tela todos os dados de um Album contido em um nó

Args:
    no::RB_album*: Ponteiro para o album que será impresso na tela

Return:
    None
*/
void mostrar_no_RB_album(RB_album *no)
{
    if (no != NULL)
        mostrar_album(&(no->album));
}


/////////////////////////////////////////////////////////////////////////////////////////// Funções nativas da RB

/*
Retorna a cor do nó passado
    0: Caso seja preto
    1: Caso seja vermelho

Args:
    raiz::RB_album: Nó de uma arvore Rubro Negro de albuns

Return:
    cor::int: Valor que representa a cor do nó.
*/
int cor_album(RB_album *raiz)
{
    int cor;

    if (raiz == NULL)
        cor = PRETO;
    else
        cor = raiz->cor;

    return cor;
}
/*
Troca a cor do nó passado e de seus filhos

Args:
    raiz::RB_album: Nó de uma arvore Rubro Negro de albuns

Return:
    None
*/
void troca_cor_album(RB_album *raiz)
{
    if (raiz != NULL)
    {
        raiz->cor = !raiz->cor;

        if (raiz->direita != NULL)
            raiz->direita->cor = !raiz->direita->cor;

        if (raiz->esquerda != NULL)
            raiz->esquerda->cor = !raiz->esquerda->cor;
    }
}

RB_album *rotacao_direita_album(RB_album *raiz)
{
    RB_album *aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_album *rotacao_esquerda_album(RB_album *raiz)
{
    RB_album *aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

RB_album *balancear_RB_album(RB_album **raiz)
{
    if (cor_album((*raiz)->direita) == VERMELHO)
        *raiz = rotacao_esquerda_album(*raiz);

    if ((*raiz)->esquerda != NULL) 
        if (cor_album((*raiz)->direita) == VERMELHO && cor_album((*raiz)->esquerda->esquerda) == VERMELHO)
            *raiz = rotacao_direita_album(*raiz);

    if (cor_album((*raiz)->esquerda) == VERMELHO && cor_album((*raiz)->direita) == VERMELHO)
        troca_cor_album(*raiz);

    return *raiz;
}

////////////////////////////////  Funções do projeto


/*
Cria um nó album para uma arvore RB caso tenha memória disponivel,
Caso consiga retorna o nó criado;
Caso contrario retorna NULL;

Args:
    titulo::char: Titulo do Album que será criado;
    ano::int: Ano de publicação do album

Return:
    no::RB_album*: No criado pela função ou NULL em caso de falha
*/
RB_album *cria_no_album(char titulo[TAM_TITULO], int ano)
{
    RB_album *no;
    no = (RB_album *)malloc(sizeof(RB_album));

    if (no)
    {

        no->cor = VERMELHO;
        preencher_album(&(no->album), titulo, ano);
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

int insere_no_RB_album(RB_album **raiz, RB_album *novo)
{
    int criou_no = 0;

    if (*raiz == NULL)
    {
        *raiz = novo;
        criou_no = 1;
    }

    else if (compara_string(novo->album.titulo,(*raiz)->album.titulo) == 0)
        criou_no = -1; // Nó já cadastrado

    else if (compara_string(novo->album.titulo,(*raiz)->album.titulo) > 0)
    {
        RB_album *aux = *raiz;
        criou_no = insere_no_RB_album(&((aux)->direita), novo);
    }

    else
    {
        RB_album *aux = *raiz;
        criou_no = insere_no_RB_album(&((aux)->esquerda), novo);
    }

    balancear_RB_album(&(*raiz));

    return criou_no;
}

void mostrar_tudo_RB_album(RB_album *raiz)
{
    if (raiz != NULL)
    {
        mostrar_tudo_RB_album(raiz->esquerda);
        mostrar_album(&(raiz->album));
        mostrar_tudo_RB_album(raiz->direita);  
    }
}

RB_album *buscar_no_RB_album(RB_album *raiz,char titulo_buscado[TAM_TITULO])
{
    RB_album *no_buscado = NULL;

    if (raiz != NULL)
    {
        if (compara_string(titulo_buscado,raiz->album.titulo)==0)
            no_buscado = raiz;

        else if (compara_string(titulo_buscado,raiz->album.titulo) < 0)
            no_buscado = buscar_no_RB_album(raiz->esquerda, titulo_buscado);

        else
            no_buscado = buscar_no_RB_album(raiz->direita, titulo_buscado);
    }
    return no_buscado;
}


/*
Album *move2esquerda_caso_direita_vermelha(RB_album *raiz)
{
    troca_Cor_album(raiz);
    if (cor_album(raiz->direita->esquerda) == VERMELHO)
    {
        rotacao_direita_album(raiz->direita);
        rotacao_esquerda_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album *move_dir_red_album(Album *raiz)
{
    troca_Cor_album(raiz);
    if (cor_album(*raiz->esquerda->esquerda) == VERMELHO)
    {
        rotacao_direita_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album *remove_menor_album(Album *raiz)
{
    if (raiz->esquerda == NULL)
    {
        free(raiz);
    }
    if (cor_album(raiz->esquerda) == PRETO && cor_album(raiz->esquerda->esquerda) == PRETO)
    {
        raiz = move2esquerda_caso_direita_vermelha(raiz);
    }

    remove_menor_album(raiz->esquerda);
    return balanceia_album(raiz);
}

Album *procuraMenor_album(Album *atual)
{
    Album *no1 = atual;
    Album *no2 = atual->esquerda;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esquerda;
    }
    return no1;
}

Album *buscarFolha_album(Album *ultimo)
{
    if (ultimo->direita != NULL)
    {
        buscarFolha_album(ultimo->direita);
    }
    else
    {
        return ultimo;
    }
}

Album *remove_NO_album(Album **raiz, char titulo[])
{
    int remove = 0;
    Album *aux = NULL;

    if (*raiz != NULL)
    {
        if (strcmp((*raiz)->titulo, titulo) == 0)
        {
            aux = *raiz;

            if ((*raiz)->esquerda == NULL && (*raiz)->direita == NULL)
            {
                free(aux);
                *raiz = NULL;
            }
            else if ((*raiz)->esquerda == NULL || (*raiz)->direita == NULL)
            {
                *raiz = ((*raiz)->esquerda != NULL) ? (*raiz)->esquerda : (*raiz)->direita;
                free(aux);
            }
            else
            {
                aux = buscarFolha_album(&(*raiz)->esquerda);
                strcpy((*raiz)->titulo, aux->titulo);
                remove_NO_album(&(*raiz)->esquerda, aux->titulo);
            }

            remove = 1;
        }
        else if (strcmp((*raiz)->titulo, titulo) < 0)
        {
            remove = remove_NO_album(&((*raiz)->direita), titulo);
        }
        else if (strcmp((*raiz)->titulo, titulo) > 0)
        {
            remove = remove_NO_album(&((*raiz)->esquerda), titulo);
        }
    }

    balanceia_album(*raiz);

    return *raiz;
}
*/