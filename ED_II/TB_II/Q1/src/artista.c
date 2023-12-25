#include "album.c"

#define NOME 50
#define TIPO 40
#define ESTILO 40

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
    int cor_artista;

    Artista artista;
    struct RB_artista *esquerda;
    struct RB_artista *direita;

} RB_artista;

/*
Preenche um artista com seus respectivos dados

Args:
    artista::Artista*: Ponteiro para o artista que será preenchido
    nome::char: Nome do Artista
    tipo::char: Tipo do Artista
    estilo::char: Estilo do Artista

Return:
    None
*/
void preencher_artista(Artista *artista, char nome[NOME], char tipo[TIPO], char estilo[ESTILO])
{
    strcpy(artista->nome, nome);
    strcpy(artista->tipo, tipo);
    strcpy(artista->estilo, estilo);
    artista->num_albuns = 0;
    artista->albuns = NULL;
}

/*
Cria um nó para um artista e dependendo do caso retorna:
    Nó do artista quando criado com sucesso
    NULL quando não consegue alocar o nó
     
Args:
    cor_artista::int: Cor do Nó onde (1 == Vermelho ou 0 == Preto)
    artista::Artista: Struct artista contendo seus repectivos dados

Return:
    no::RB_artista*: Endereço de um nó RB artista;

*/
RB_artista *cria_no_artista(int cor_artista, Artista artista)
{
    RB_artista *no = (RB_artista *)malloc(sizeof(RB_artista));

    if (no)
    {
        no->cor_artista = cor_artista;
        no->artista = artista;
        no->esquerda = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

/*
Troca a cor_artista de um nó e de seus filhos, onde for vermelho fica preto e onde for preto fica vermelho

Args:
    no::RB_artista: No que será modificado

Return:
    None
*/
void trocar_cor(RB_artista *no)
{
    if (no != NULL)
    {
        no->cor_artista = !no->cor_artista;

        if (no->direita != NULL)
            no->direita->cor_artista = !no->direita->cor_artista;

        if (no->esquerda != NULL)
            no->esquerda->cor_artista = !no->esquerda->cor_artista;
    }
}

/*
Troca a cor da Raiz garantindo que a mesma sempre fique preta

Args:
    raiz::RB_artista*: Raiz que ficará preta caso tenha algum valor

Return:
    None
*/
void troca_cor_raiz_RB_artista(RB_artista *raiz)
{
    if (raiz != NULL)
    {
        raiz->cor_artista = PRETO;
    }
}

/*
Retorna a cor do nó artista. Caso seja NULL retorna 0

Args:
    no::RB_artista*: Ponteiro para o nó que iremos acessar para conseguir sua cor
*/
int cor_artista(RB_artista *no)
{
    int color = 0;
    if (no != NULL)
    {
        color = no->cor_artista;
    }

    return color;
}

/*
Realiza a rotação para a direita de um nó e retorna o novo nó central após a rotação

Args:
    raiz::RB_artista*: Ponteiro para o nó que será rotacionado

Return:
    aux::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
RB_artista *rotacao_direita_artista(RB_artista *raiz)
{
    RB_artista *aux = raiz->esquerda;
    raiz->esquerda = aux->direita;
    aux->direita = raiz;
    aux->cor_artista = raiz->cor_artista;
    raiz->cor_artista = VERMELHO;
    return aux;
}
/*
Realiza a rotação para a esquerda de um nó e retorna o novo nó central após a rotação

Args:
    raiz::RB_artista*: Ponteiro para o nó que será rotacionado

Return:
    aux::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
RB_artista *rotacao_esquerda_artista(RB_artista *raiz)
{
    RB_artista *aux = raiz->direita;
    raiz->direita = aux->esquerda;
    aux->esquerda = raiz;
    aux->cor_artista = raiz->cor_artista;
    raiz->cor_artista = VERMELHO;
    return aux;
}

/*
Realiza a rotação para a esquerda de um nó e retorna o novo nó central após a rotação

Args:
    no::RB_artista*: Ponteiro para o nó que será rotacionado

Return:
    no::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
RB_artista *move2EsqRED_artista(RB_artista *no)
{
    trocar_cor(no);
    if (cor_artista(no->direita->esquerda) == VERMELHO)
    {
        no->direita = rotacao_direita_artista(no->direita);
        no = rotacao_esquerda_artista(no);
        trocar_cor(no);
    }
    return no;
}

/*
Realiza a rotação para a direita de um nó e retorna o novo nó central após a rotação

Args:
    no::RB_artista*: Ponteiro para o nó que será rotacionado

Return:
    no::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
RB_artista *move2DirRED_artista(RB_artista *no)
{
    trocar_cor(no);
    if (cor_artista(no->esquerda->esquerda) == VERMELHO)
    {
        no = rotacao_direita_artista(no);
        trocar_cor(no);
    }
    return no;
}


/*
Realiza o balanceamento de um nó e retorna o nó final após o balanceamento

Args:
    no::RB_artista*: Ponteiro para o nó que será balanceado

Return:
    no::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
RB_artista *balancear_RB_artista(RB_artista *no)
{
    if (cor_artista(no->direita) == VERMELHO)
    {
        no = rotacao_esquerda_artista(no);
    }

    if (no->esquerda != NULL)
    {
        if (cor_artista(no->direita) == VERMELHO && cor_artista(no->esquerda->esquerda) == VERMELHO)
            no = rotacao_direita_artista(no);
               
    }

    if (cor_artista(no->esquerda) == VERMELHO && cor_artista(no->direita) == VERMELHO)
    {
        trocar_cor(no);
    }

    return no;
}


/*
Realiza a remoção do menor nó RB_artista de uma arvore

Args:
    no::RB_artista*: Ponteiro para o nó que terá seu menor filho removido

Return:
    aux::RB_artista*: Ponteiro para o novo nó que será a raiz
*/
RB_artista * remover_menor_artista(RB_artista *no)
{
    RB_artista *aux = NULL;

    if(no->esquerda==NULL)
        free(no);

    else
    {
        if(cor_artista(no->esquerda)==PRETO && cor_artista(no->esquerda->esquerda)==PRETO)
            no = move2EsqRED_artista(no);

        no->esquerda = remover_menor_artista(no->esquerda);
        aux = balancear_RB_artista(no);
    }

    return aux;
}

/*
Retorna o menor nó de uma arvore 

Args:
    no::RB_artista*: Ponteiro para o nó que terá seu menor filho procurado

Return:
    aux1::RB_artista*: Ponteiro para o menor nó
*/
RB_artista *procura_menor_artista(RB_artista *no)
{
    RB_artista * aux1 = no;
    RB_artista * aux2 = no->esquerda;

    while (aux2 != NULL)
    {
        aux1 = aux2;
        aux2 = aux2->esquerda;
    }

    return aux1;
}

/*
Insere um novo nó artista em uma arvore de artistas

Args:
    raiz::RB_artista**: Referência do Ponteiro que guarda a raiz da arvore
    novo_no::RB_artista**: Ponteiro para o novo nó que será inserido na arvore

Return:
    None
*/

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


/*
Mostra todos os dados de um Artista na tela

Args:
    artista::Artista: Estrutura artista que terá seus dados exibidos na tela

Return:
    None

*/
void mostrar_artista(Artista artista)
{
    printf("\n--------DADOS DO ARTISTA-------\n");
    printf("\nNOME: %s\nTIPO: %s\nESTILO: %s\nTOTAL DE ALBUNS: %d\n ",artista.nome,artista.tipo,artista.estilo,artista.num_albuns);

    mostrar_tudo_RB_album((artista.albuns));
    printf("\n------------------------------");
}

/*
Remove um nó artista de uma arvore de artistas

Args:
    raiz::RB_artista: ponteiro para a raiz da arvore
    nome_artista::char: Nome do artista que será removido

Return:
    raiz::RB_artista: Ponteiro para a nova raiz da arvore após a remoção

*/
RB_artista *remove_no_artista(RB_artista *raiz, char nome_artista[NOME])
{
    if(compara_string(nome_artista,raiz->artista.nome) < 0)
    {
        if(cor_artista(raiz->esquerda)==PRETO && cor_artista(raiz->esquerda->esquerda)==PRETO)
            raiz = move2EsqRED_artista(raiz);

        raiz->esquerda = remove_no_artista(raiz->esquerda,nome_artista);
    }
    else
    {
        RB_artista *aux;
        if(cor_artista(raiz->esquerda)==VERMELHO)
            raiz = rotacao_direita_artista(raiz);

        if(compara_string(nome_artista,raiz->artista.nome)==0 && raiz->direita == NULL)
        {
            aux = raiz;
            raiz = NULL;
            free(aux);
        }
        else
        {
            if(cor_artista(raiz->direita)==PRETO && cor_artista(raiz->direita->esquerda)==PRETO)
                raiz = move2DirRED_artista(raiz);
            
            if(compara_string(nome_artista,raiz->artista.nome)==0)
            {
                aux = procura_menor_artista(raiz->direita);
                raiz->artista = aux->artista;
                raiz->direita = remover_menor_artista(raiz->direita);
            }
            else
                remove_no_artista(raiz->direita,nome_artista);
        }
        
    }
    if (raiz != NULL)
        raiz = balancear_RB_artista(raiz);
    
    return raiz;
}

/*
Remove um nó artista de uma arvore de artistas respeitando todas as normas da Rubro Negro
Casos de retorno:
    1 - Sucesso
    0 - Falha

Args:
    raiz::RB_artista: Referência do ponteiro para a raiz da arvore
    nome_artista::char: Nome do artista que será removido

Return:
    removi::int: Sinalização baseada no resultado da operação de remoção
*/
int remove_no_artista_ARVRB(RB_artista **raiz, char nome_artista[NOME])
{
    int removi = 0;

    if(busca_no_artista(*raiz,nome_artista)!=NULL)
    {
        RB_artista *aux = *raiz;
        *raiz = remove_no_artista(aux,nome_artista);

        troca_cor_raiz_RB_artista(*raiz);

        removi = 1;
    }

    return removi;
}