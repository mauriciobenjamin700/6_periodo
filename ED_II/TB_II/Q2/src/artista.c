#include "album.c"
#include "artista.h"

#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{
    char nome[NOME];
    char tipo[TIPO];
    char estilo[ESTILO];
    int num_albuns;
    Arv_23_album *albuns;

} Artista;

typedef struct Arv_23_artista
{
    int qtd_infos;
    Artista info1;
    Artista info2;
    struct Arv_23_artista *pai;
    struct Arv_23_artista *esquerda;
    struct Arv_23_artista *centro;
    struct Arv_23_artista *direita;

} Arv_23_artista;

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
    None

Return:
    no::Arv_23_artista*: Endereço de um nó artista;

*/
Arv_23_artista *cria_no_artista()
{
    Arv_23_artista *no = (Arv_23_artista *)malloc(sizeof(Arv_23_artista));

    if (no)
    {
        no->qtd_infos = 0;
        no->pai = NULL;
        no->esquerda = NULL;
        no->centro = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

/*
Verifica se um nó artista é falho ou não
    1 - Caso seja folha
    0 - Caso não seja folha

Args:
    no::Arv_23_artista*: Ponteiro para o nó que será checado

Return:
    sinal::int: Sinalização referente a checagem se é ou não folha
*/
int no_artista_eh_folha(Arv_23_artista *no)
{
    int sinal = 0;
    if (no->direita == NULL && no->centro == NULL && no->esquerda == NULL)
        sinal = 1;

    return sinal;
}

/*
Troca a posicação de dois artistas com base na ordem alfabetica dos mesmos
o menor sempre ficará em a1, o do meio em a2 e o maior em a3

Args:
    a1::Artista*: Ponteiro para artista que será o menor
    a2::Artista*: Ponteiro para artista que será o do meio
    a3::Artista*: Ponteiro para artista que será o maior

Return:
    None

*/
void ordenar_artistas(Artista *a1, Artista *a2, Artista *a3)
{
    Artista aux;
    // caso o primeiro seja maior que o segundo, e do que o terceiro
    if (compara_string(a1->nome, a2->nome) > 0 && compara_string(a1->nome, a3->nome) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a1;
        *a1 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {

            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o segundo seja o maior de todos
    else if (compara_string(a2->nome, a1->nome) > 0 && compara_string(a2->nome, a3->nome) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a2;
        *a2 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o terceiro seja o maior de todos
    else if (compara_string(a3->nome, a1->nome) > 0 && compara_string(a3->nome, a2->nome) > 0)
    {
        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
}

/*Dica do GPT
void quebra_no_artista(Arv_23_artista **raiz, Artista artista)
    {
    if ((*raiz)->qtd_infos == 2)
    {
        // Criando um novo nó para acomodar a terceira informação
        Arv_23_artista *novo_no = cria_no_artista();

        if (novo_no != NULL)
        {
            Artista temp[3];
            temp[0] = (*raiz)->info1;
            temp[1] = (*raiz)->info2;
            temp[2] = artista;

            ordenar_artistas(&temp[0], &temp[1], &temp[2]);

            // Atribuindo as informações aos nós
            (*raiz)->info1 = temp[0];
            (*raiz)->info2 = temp[1];
            novo_no->info1 = temp[2];

            // Dividindo os filhos (se existirem)
            novo_no->esquerda = (*raiz)->esquerda;
            novo_no->centro = (*raiz)->direita;

            (*raiz)->esquerda = NULL;
            (*raiz)->direita = NULL;

            (*raiz)->qtd_infos = 1;
            novo_no->qtd_infos = 1;

            // Se o nó for raiz, redefinir a raiz
            if ((*raiz) == (*raiz)->direita)
            {
                Arv_23_artista *nova_raiz = cria_no_artista();
                nova_raiz->info1 = temp[1];
                nova_raiz->esquerda = (*raiz);
                nova_raiz->centro = novo_no;
                (*raiz) = nova_raiz;
            }
            else
            {
                // Promovendo o elemento do meio para o nó pai
                artista = temp[1];
                (*raiz)->info1 = temp[0];
                (*raiz)->info2 = temp[1];
                (*raiz)->qtd_infos = 1;

                // Recursão para inserir no nó pai
                if (compara_string(artista.nome, (*raiz)->info1.nome) < 0)
                    inserir_artista_arv23(&(*raiz)->esquerda, artista);
                else
                    inserir_artista_arv23(&(*raiz)->centro, artista);
            }
        }
    }
}
*/

/*Sobe um nó para tentar inserir no pai*/
void sobe_no_artista_pai(Arv_23_artista **raiz, Artista sobiu, Arv_23_artista *esquerda, Arv_23_artista *direita)
{
    //se não existe um pai (o no anterior já era a raiz)
    if((*raiz) == NULL)
    {
        Arv_23_artista *pai = cria_no_artista();

        if(pai != NULL)
        {
            pai->info1 = sobiu;
            pai->esquerda = esquerda;
            pai->centro = direita;
            (*raiz) = pai;
        }
    }
    //caso exista um pai
    else
    {
        //checar se tem espaço, se tiver inserir na posição correta
        if((*raiz)->qtd_infos == 1)
        {
            int retorno = compara_string((*raiz)->info1.nome,sobiu.nome);
            
            if (retorno < 0)
            {
                (*raiz)->info2 = sobiu;
                (*raiz)->centro = esquerda;
                (*raiz)->direita = direita;
                (*raiz)->qtd_infos = 2;
            }
            else if (retorno > 0)
            {
                (*raiz)->info2 = (*raiz)->info1;
                (*raiz)->info1 = sobiu;
                (*raiz)->centro = esquerda;
                (*raiz)->direita = direita;
                (*raiz)->qtd_infos = 2;               
            }
        }
        //caso não tenha espaço, precisa quebrar o nó novamente e repetir o processo
        else
        {
            printf("\nImplementar o quebra nó aqui");
        }
    }
    
}


void quebra_no_artista(Arv_23_artista **raiz, Artista artista)
{

    if ((*raiz)->qtd_infos == 2)
    {
        Arv_23_artista *novo_no = cria_no_artista();

        if (novo_no != NULL)
        {
            Artista temp[3];
            temp[0] = (*raiz)->info1;
            temp[1] = (*raiz)->info2;
            temp[2] = artista;

            ordenar_artistas(&temp[0], &temp[1], &temp[2]);
            //garantirmos que o maior fique no novo nó e o do meio fique na info2
            (*raiz)->info1 = temp[0];
            (*raiz)->info2 = temp[1];
            novo_no->info1 = temp[2];

            (*raiz)->qtd_infos = 1;
            sobe_no_artista_pai(&(*raiz)->pai, (*raiz)->info2,(*raiz),novo_no);
        }
    }

}

/*
Insere um novo nó artista em uma arvore de artistas
    1 - Sucesso
    0 - Já cadastrado
   -1 - Falha ao alocar memoria para a inserção

Args:
    raiz::Arv_23_artista**: Referência do Ponteiro que guarda a raiz da arvore
    novo_no::Arv_23_artista**: Ponteiro para o novo nó que será inserido na arvore

Return:
    inseri::int: Sinalização sobre o resultado da inserção
*/
int inserir_artista_arv23(Arv_23_artista **raiz, Artista artista)
{
    int inseri = 0;
    if (*raiz == NULL)
    {
        *raiz = cria_no_artista();
        if (*raiz != NULL)
        {
            (*raiz)->info1 = artista;
            (*raiz)->qtd_infos = 1;
            inseri = 1;
        }
        else
            inseri = -1;
    }
    else if (no_artista_eh_folha(*raiz))
    {
        if ((*raiz)->qtd_infos == 0)
        {
            (*raiz)->info1 = artista;
            (*raiz)->qtd_infos = 1;
            inseri = 1;
        }

        else if ((*raiz)->qtd_infos == 1)
        {
            int retorno = compara_string((*raiz)->info1.nome, artista.nome);
            if (retorno < 0)
            {
                (*raiz)->info2 = artista;
                (*raiz)->qtd_infos = 2;
                inseri = 1;
            }
            else if (retorno > 0)
            {
                (*raiz)->info2 = (*raiz)->info1;
                (*raiz)->info1 = artista;
                (*raiz)->qtd_infos = 2;
                inseri = 1;
            }
        }

        // caso sejá folha e tenha 2 infos, precisamos quebrar o nó
        else if ((*raiz)->qtd_infos == 2)
        {
            printf("\nCriar função de quebra nó");
        }
    }
    // Caso não seja folha vamos ter que percorrer a arvore para achar uma folha pronta para ser inserida
    else
    {
        int retorno = compara_string((*raiz)->info1.nome, artista.nome);

        // caso info 1 seja maior que o artista vamos pra esquerda
        if (retorno > 0)
            inseri = inserir_artista_arv23(&(*raiz)->esquerda, artista);

        // caso info 1 seja menor que o artista, precisamos ver existe info2, caso exista vamos comparar com info 2, caso não vamos apenas ir para a direita de info 1 que será nosso centro
        else if (retorno < 0)
        {
            // se a direita for diferente de null, então existe info 2 para compararmos
            if ((*raiz)->direita != NULL)
            {
                retorno = compara_string((*raiz)->info2.nome, artista.nome);

                // caso info 2 seja menor que o artista, então vamos para a direita
                if (retorno < 0)
                    inseri = inserir_artista_arv23(&(*raiz)->direita, artista);

                // caso info 2 seja maior que o artista, então vamos pro centro
                else if (retorno > 0)
                    inseri = inserir_artista_arv23(&(*raiz)->centro, artista);
            }
            // já que não existe info 2, vamos para o centro
            else
                inseri = inserir_artista_arv23(&(*raiz)->centro, artista);
        }
    }

    return inseri;
}



/*
Busca um nó artista dentro da arvore com base no nome do artista


Args:
    raiz::Arv_23_artista*: Ponteiro para a raiz da arvore de artistas
    nome_artista::char: Nome do artista que estamos buscando

Return:
    artista_buscado::Arv_23_artista*: Referência do artista buscado

Arv_23_artista *busca_no_artista(Arv_23_artista *raiz, char nome_artista[NOME])
{
    Arv_23_artista *artista_buscado = NULL;

    if (raiz != NULL)
    {
        if (compara_string(nome_artista, raiz->artista.nome) == 0)
            artista_buscado = raiz;

        else if (compara_string(nome_artista, raiz->artista.nome) < 0)
            artista_buscado = busca_no_artista(raiz->esquerda, nome_artista);

        else
            artista_buscado = busca_no_artista(raiz->direita, nome_artista);
    }

    return artista_buscado;
}

/*
Mostra todos os dados de um Artista na tela

Args:
    artista::Artista: Estrutura artista que terá seus dados exibidos na tela

Return:
    None


void mostrar_artista(Artista artista)
{
    printf("\n--------DADOS DO ARTISTA-------\n");
    printf("\nNOME: %s\nTIPO: %s\nESTILO: %s\nTOTAL DE ALBUNS: %d\n ", artista.nome, artista.tipo, artista.estilo, artista.num_albuns);

    mostrar_tudo_RB_album((artista.albuns));
    printf("\n------------------------------");
}

/*
Remove um nó artista de uma arvore de artistas

Args:
    raiz::Arv_23_artista: ponteiro para a raiz da arvore
    nome_artista::char: Nome do artista que será removido

Return:
    raiz::Arv_23_artista: Ponteiro para a nova raiz da arvore após a remoção


Arv_23_artista *remove_no_artista(Arv_23_artista *raiz, char nome_artista[NOME])
{
    if (compara_string(nome_artista, raiz->artista.nome) < 0)
    {
        if (cor_artista(raiz->esquerda) == PRETO && cor_artista(raiz->esquerda->esquerda) == PRETO)
            raiz = move2EsqRED_artista(raiz);

        raiz->esquerda = remove_no_artista(raiz->esquerda, nome_artista);
    }
    else
    {
        Arv_23_artista *aux;
        if (cor_artista(raiz->esquerda) == VERMELHO)
            raiz = rotacao_direita_artista(raiz);

        if (compara_string(nome_artista, raiz->artista.nome) == 0 && raiz->direita == NULL)
        {
            aux = raiz;
            raiz = NULL;
            free(aux);
        }
        else
        {
            if (cor_artista(raiz->direita) == PRETO && cor_artista(raiz->direita->esquerda) == PRETO)
                raiz = move2DirRED_artista(raiz);

            if (compara_string(nome_artista, raiz->artista.nome) == 0)
            {
                aux = procura_menor_artista(raiz->direita);
                raiz->artista = aux->artista;
                raiz->direita = remover_menor_artista(raiz->direita);
            }
            else
                remove_no_artista(raiz->direita, nome_artista);
        }
    }
    if (raiz != NULL)
        raiz = balancear_RB_artista(raiz);

    return raiz;
}


Remove um nó artista de uma arvore de artistas respeitando todas as normas da Rubro Negro
Casos de retorno:
    1 - Sucesso
    0 - Falha

Args:
    raiz::Arv_23_artista: Referência do ponteiro para a raiz da arvore
    nome_artista::char: Nome do artista que será removido

Return:
    removi::int: Sinalização baseada no resultado da operação de remoção

int remove_no_artista_ARVRB(Arv_23_artista **raiz, char nome_artista[NOME])
{
    int removi = 0;

    if (busca_no_artista(*raiz, nome_artista) != NULL)
    {
        Arv_23_artista *aux = *raiz;
        *raiz = remove_no_artista(aux, nome_artista);

        troca_cor_raiz_RB_artista(*raiz);

        removi = 1;
    }

    return removi;
}

/*
Cadastra um album em um artista e retorna o resultado do processo
    1 - Sucesso
    0 - Falha
   -1 - Já estava cadastrado

Args:
    artista::Arv_23_artista*: Refência do nó que contem o artista que receberá um novo album
    album::Arv_23_album*: Referência para o album que será adicionando ao artista

Return:
    cadastrei::int: Sinalização referente ao resultado da operação

int cadastrar_album_artista(Arv_23_artista *artista, Arv_23_album *album)
{
    int cadastrei = 0;

    if (artista != NULL)
    {
        cadastrei = insere_no_RB_album(&(artista->artista.albuns), album);

        if (cadastrei == 1)
            artista->artista.num_albuns++;
    }

    return cadastrei;
}

/*
Busca um album dentro de um artista, podendo retornar a referência daquele album em caso de encontrar ou NULL caso falhe

Args:
    artista::Arv_23_artista*: Referência do nó que contem o artista que iremos acessar buscando o album.
    titulo_album::char: Titulo do album que estaremos buscando.

Return:
    no_album_buscado::Arv_23_album*: Referência do album buscado

Arv_23_album *buscar_album_artista(Arv_23_artista *artista, char titulo_album[TAM_TITULO])
{
    Arv_23_album *no_album_buscado = NULL;

    if (artista != NULL)
        no_album_buscado = buscar_no_RB_album(artista->artista.albuns, titulo_album);

    return no_album_buscado;
}

/*
Remove um nó album de uma arvore de albuns respeitando todas as normas da Rubro Negro e decrementa a quantidade de albuns do artista
Casos de retorno:
    1 - Sucesso
    0 - Falha

Args:
    artista::Arv_23_artista*: Referência do artista que terá um album removido
    titulo_album::char: Nome do artista que será removido

Return:
    removi::int: Sinalização baseada no resultado da operação de remoção

int remover_album_artista(Arv_23_artista *artista, char titulo_album[TAM_TITULO])
{
    int removi = remove_no_album_ARVRB(&(artista->artista.albuns), titulo_album);
    if (removi == 1)
        artista->artista.num_albuns--;

    return removi;
}

/*
Retorna a confirmação sobre o ato de remover um nó
    1 - Pode
    0 - Não

Args:
    no::Arv_23_artista*: Referencia do nó artista que estamos checando a possibilidade de removelo

Return:
    confirmacao::int: Sinalização de confirmação sobre o ato de remover

int pode_remover_artista(Arv_23_artista *no)
{
    int confirmacao = 0;

    if (no->artista.num_albuns == 0)
        confirmacao = 1;

    return confirmacao;
}

/*
Função para visualizar se o nó está na cor certa

void mostrar_no_artista(Arv_23_artista *artista)
{
    printf("\n\n------------------------\n");
    printf("\n\tCor: %d\n\tNome: %s", artista->cor_artista, artista->artista.nome);
    printf("\n\n------------------------\n");
}

/*
Função para percorrer a arvore e ver se as cores dos nós estão seguindo as normas vistas em sala de aula

void mostrar_todos_nos_artista_ordenado(Arv_23_artista *artista)
{
    if (artista != NULL)
    {
        mostrar_todos_nos_artista_ordenado(artista->esquerda);
        mostrar_no_artista(artista);
        mostrar_todos_nos_artista_ordenado(artista->direita);
    }
}

/*
Remove todos os artistas de uma arvore

void remover_todos_artistas(Arv_23_artista **raiz)
{
    if (*raiz != NULL)
    {
        remover_todos_artistas(&(*raiz)->esquerda);
        remover_todos_artistas(&(*raiz)->direita);

        remover_todos_albuns(&(*raiz)->artista.albuns);
        free(*raiz);
    }
}
*/