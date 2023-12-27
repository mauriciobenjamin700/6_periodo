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

typedef struct Arv_23_album
{
    Album album;
    struct Arv_23_album *esquerda;
    struct Arv_23_album *direita;
    int cor;

} Arv_23_album;


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
int adiciona_musica_no_album(Arv_23_album *album, Musica *musica)
{
    int adicionei = adicionar_musica_ordenada(&(album->album.musicas), musica);
    if (adicionei)
        album->album.qtd_musicas += 1;

    return adicionei;
}

/*
Busca um nó Lista_musicas dentro de um nó Arv_23_album.

Args:
    album::Arv_23_album*: Ponteiro para um nó Arv_23_album 
    titulo::char: Título da musica que estamos buscando

Return:
    aux::Lista_musicas*: Apontamento para o nó da musica buscada em casa de sucesso na busca ou NULL caso a musica não seja encontrada

*/
Lista_musicas * buscar_musica_no_album(Arv_23_album *album,char titulo[TAM_TITULO])
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
Retorna a cor do nó passado
    0: Caso seja preto
    1: Caso seja vermelho

Args:
    raiz::Arv_23_album: Nó de uma arvore Rubro Negro de albuns

Return:
    cor::int: Valor que representa a cor do nó.
*/
int cor_album(Arv_23_album *raiz)
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
    raiz::Arv_23_album: Nó de uma arvore Rubro Negro de albuns

Return:
    None
*/
void troca_cor_album(Arv_23_album *raiz)
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
/*
Realiza a rotação do nó passado para a direita de forma a esquerda se tornar a raiz e a antiga raiz se torna a direta da nova raiz

Args:
    raiz::Arv_23_album*: Ponteiro para o nó Arv_23_album que sofrerá a rotação

Return:
    aux::Arv_23_album*: Endereço do novo nó raiz
*/
Arv_23_album *rotacao_direita_album(Arv_23_album *raiz)
{
    Arv_23_album *aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}

/*
Realiza a rotação do nó passado para a esquerda de forma a direita se tornar a raiz e a antiga raiz se torna a esquerda da nova raiz

Args:
    raiz::Arv_23_album*: Ponteiro para o nó Arv_23_album que sofrerá a rotação

Return:
    aux::Arv_23_album*: Endereço do novo nó raiz
*/
Arv_23_album *rotacao_esquerda_album(Arv_23_album *raiz)
{
    Arv_23_album *aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return aux;
}
/*
Realiza o balanceamento do nó raiz de acordo com as clausulas usadas pela Arvore Rubro Negro, sendo elas:
    1 - Nós vermelhos devem ficar somente a esquerda da raiz
    2 - Se a esquerda e a direita do nó são vermelhos, então troca-se a cor do nó raiz e dos seus filhos da direita e da esquerda
    3 - Se a esquerda da esquerda for vermelha e a direita for vermelha

Args:
    raiz::Arv_23_album**: Endereço do Ponteiro para o nó Arv_23_album que sofrerá a rotação

Return:
    raiz::Arv_23_album*: Endereço do novo nó raiz
*/
Arv_23_album *balancear_RB_album(Arv_23_album **raiz)
{
    if (cor_album((*raiz)->direita) == VERMELHO && cor_album((*raiz)->esquerda) == PRETO)
        *raiz = rotacao_esquerda_album(*raiz);
    
    if ((*raiz)->esquerda != NULL) 
    {
        if (cor_album((*raiz)->direita) == VERMELHO && cor_album((*raiz)->esquerda->esquerda) == VERMELHO)
            *raiz = rotacao_direita_album(*raiz);

        if(cor_album((*raiz)->esquerda)== VERMELHO && cor_album((*raiz)->esquerda->esquerda)==VERMELHO)
            *raiz = rotacao_direita_album(*raiz);

    }
        
    if (cor_album((*raiz)->esquerda) == VERMELHO && cor_album((*raiz)->direita) == VERMELHO)
        troca_cor_album(*raiz);


    return *raiz;
}

/*
Realiza a rotação para a esquerda de um nó e retorna o novo nó central após a rotação

Args:
    no::RB_artista*: Ponteiro para o nó que será rotacionado

Return:
    no::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
Arv_23_album *move2EsqRED_album(Arv_23_album *no)
{
    troca_cor_album(no);
    if (cor_album(no->direita->esquerda) == VERMELHO)
    {
        no->direita = rotacao_direita_album(no->direita);
        no = rotacao_esquerda_album(no);
        troca_cor_album(no);
    }
    return no;
}

/*
Realiza a rotação para a direita de um nó e retorna o novo nó central após a rotação

Args:
    no::Arv_23_album*: Ponteiro para o nó que será rotacionado

Return:
    no::Arv_23_album*: Ponteiro para o novo nó que será a raiz
*/
Arv_23_album *move2DirRED_album(Arv_23_album *no)
{
    troca_cor_album(no);
    if (cor_album(no->esquerda->esquerda) == VERMELHO)
    {
        no = rotacao_direita_album(no);
        troca_cor_album(no);
    }
    return no;
}

/*
Realiza a remoção do menor nó Arv_23_album de uma arvore

Args:
    no::Arv_23_album*: Ponteiro para o nó que terá seu menor filho removido

Return:
    aux::Arv_23_album*: Ponteiro para o novo nó que será a raiz
*/
Arv_23_album * remover_menor_album(Arv_23_album *no)
{
    Arv_23_album *aux = NULL;

    if(no->esquerda==NULL)
        free(no);

    else
    {
        if(cor_album(no->esquerda)==PRETO && cor_album(no->esquerda->esquerda)==PRETO)
            no = move2EsqRED_album(no);

        no->esquerda = remover_menor_album(no->esquerda);
        aux = balancear_RB_album(&no);
    }

    return aux;
}

/*
Retorna o menor nó de uma arvore 

Args:
    no::Arv_23_album*: Ponteiro para o nó que terá seu menor filho procurado

Return:
    aux1::Arv_23_album*: Ponteiro para o menor nó
*/
Arv_23_album *procura_menor_album(Arv_23_album *no)
{
    Arv_23_album * aux1 = no;
    Arv_23_album * aux2 = no->esquerda;

    while (aux2 != NULL)
    {
        aux1 = aux2;
        aux2 = aux2->esquerda;
    }

    return aux1;
}

/*
Cria um nó album para uma arvore RB caso tenha memória disponivel,
Caso consiga retorna o nó criado;
Caso contrario retorna NULL;

Args:
    titulo::char: Titulo do Album que será criado;
    ano::int: Ano de publicação do album

Return:
    no::Arv_23_album*: No criado pela função ou NULL em caso de falha
*/
Arv_23_album *cria_no_album(char titulo[TAM_TITULO], int ano)
{
    Arv_23_album *no;
    no = (Arv_23_album *)malloc(sizeof(Arv_23_album));

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



/*
Insere um nó Arv_23_album em uma arvore Arv_23_album na posicação correta, usando o titulo do album como meio de ordenação
A inserção pode resultar em 3 casos:
    1 - Caso ensira com sucesso
    0 - Caso não consiga inserir
   -1 Caso já estivesse cadastrado na arvore

Args:
    raiz::Arv_23_album**: Endedereço do ponteiro que apontara para o nó raiz
    novo::Arv_23_album*: Ponteiro para o novo nó que será inserido na arvore

Return:
    criou_no::int: Sinalização referente ao resultado da operação de inserção
*/
int insere_no_RB_album(Arv_23_album **raiz, Arv_23_album *novo)
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
        Arv_23_album *aux = *raiz;
        criou_no = insere_no_RB_album(&((aux)->direita), novo);
    }

    else
    {
        Arv_23_album *aux = *raiz;
        criou_no = insere_no_RB_album(&((aux)->esquerda), novo);
    }

    balancear_RB_album(&(*raiz));

    return criou_no;
}

/*
Printa na tela todos os dados de um Album contido em um nó

Args:
    no::Arv_23_album*: Ponteiro para o album que será impresso na tela

Return:
    None
*/
void mostrar_no_RB_album(Arv_23_album *no)
{
    if (no != NULL)
        mostrar_album(&(no->album));
}

/*
Mostra todos os dados de todos os albuns em uma arvore Rubro Negro de albuns.

Args:
    raiz::Arv_23_album*: Ponteiro para a raiz da arvore que será percorrida para mostrar todos os seus albuns

Return:
    None
*/
void mostrar_tudo_RB_album(Arv_23_album *raiz)
{
    if (raiz != NULL)
    {
        mostrar_tudo_RB_album(raiz->esquerda);
        mostrar_album(&(raiz->album));
        mostrar_tudo_RB_album(raiz->direita);  
    }
}

/*
Busca um nó Arv_23_album dentro de uma arvore Rubro negro de albuns pelo titulo.

Args:
    raiz::Arv_23_album*: Ponteiro para a raiz da arvore.
    titulo_buscado::char: Titulo do album que deseja buscar dentro da arvore.

Return:
    raiz::Arv_23_album*: Ponteiro para o nó buscado caso encontre, caso falhe retorna NULL

*/
Arv_23_album *buscar_no_RB_album(Arv_23_album *raiz,char titulo_buscado[TAM_TITULO])
{
    Arv_23_album *no_buscado = NULL;

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
Remove um nó album de uma arvore de albuns

Args:
    raiz::Arv_23_album: ponteiro para a raiz da arvore
    titulo::char: Titulo do album que será removido

Return:
    raiz::Arv_23_album: Ponteiro para a nova raiz da arvore após a remoção

*/
Arv_23_album *remove_no_album(Arv_23_album *raiz, char titulo_album[TAM_TITULO])
{
    if(compara_string(titulo_album,raiz->album.titulo) < 0)
    {
        if(cor_album(raiz->esquerda)==PRETO && cor_album(raiz->esquerda->esquerda)==PRETO)
            raiz = move2EsqRED_album(raiz);

        raiz->esquerda = remove_no_album(raiz->esquerda,titulo_album);
    }
    else
    {
        Arv_23_album *aux;
        if(cor_album(raiz->esquerda)==VERMELHO)
            raiz = rotacao_direita_album(raiz);

        if(compara_string(titulo_album,raiz->album.titulo)==0 && raiz->direita == NULL)
        {
            aux = raiz;
            raiz = NULL;
            free(aux);
        }
        else
        {
            if(cor_album(raiz->direita)==PRETO && cor_album(raiz->direita->esquerda)==PRETO)
                raiz = move2DirRED_album(raiz);
            
            if(compara_string(titulo_album,raiz->album.titulo)==0)
            {
                aux = procura_menor_album(raiz->direita);
                raiz->album = aux->album;
                raiz->direita = remover_menor_album(raiz->direita);
            }
            else
                remove_no_album(raiz->direita,titulo_album);
        }
        
    }
    if (raiz != NULL)
        raiz = balancear_RB_album(&raiz);
    
    return raiz;
}

/*
Troca a cor da Raiz garantindo que a mesma sempre fique preta

Args:
    raiz::RB_artista*: Raiz que ficará preta caso tenha algum valor

Return:
    None
*/
void troca_cor_raiz_RB_album(Arv_23_album *raiz)
{
    if (raiz != NULL)
    {
        raiz->cor = PRETO;
    }
}

/*
Remove um nó album de uma arvore de albuns respeitando todas as normas da Rubro Negro
Casos de retorno:
    1 - Sucesso
    0 - Falha

Args:
    raiz::Arv_23_album**: Referência do ponteiro para a raiz da arvore
    titulo_album::char: Nome do artista que será removido

Return:
    removi::int: Sinalização baseada no resultado da operação de remoção
*/
int remove_no_album_ARVRB(Arv_23_album **raiz, char titulo_album[TAM_TITULO])
{
    int removi = 0;

    if(*raiz!=NULL)
    {
        Arv_23_album *aux = *raiz;
        *raiz = remove_no_album(aux,titulo_album);

        troca_cor_raiz_RB_album(*raiz);

        removi = 1;
    }

    return removi;
}

/*
Retorna a confirmação sobre o ato de remover um nó
    1 - Pode
    0 - Não

Args:
    no::Arv_23_album*: Referencia do nó album que estamos checando a possibilidade de removelo

Return:
    confirmacao::int: Sinalização de confirmação sobre o ato de remover
*/
int pode_remover_album(Arv_23_album *no)
{
    int confirmacao = 0;

    if(no->album.qtd_musicas == 0)
        confirmacao = 1;
    
    return confirmacao;
}

/*
Remove todos os albuns de uma arvore e suas musicas
*/
void remover_todos_albuns(Arv_23_album **raiz)
{
    if(*raiz != NULL)
    {
        remover_todos_albuns(&(*raiz)->esquerda);
        remover_todos_albuns(&(*raiz)->direita);

        remover_todas_musicas(&(*raiz)->album.musicas);
        free(*raiz);
        
    }
}