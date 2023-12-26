#include "artista.c"

/*
Cadastra um album em um artista e retorna o resultado do processo
    1 - Sucesso
    0 - Falha
   -1 - Já estava cadastrado

Args:
    artista::RB_artista*: Refência do nó que contem o artista que receberá um novo album
    album::RB_album*: Referência para o album que será adicionando ao artista

Return:
    cadastrei::int: Sinalização referente ao resultado da operação
*/
int cadastrar_album_artista(RB_artista *artista, RB_album *album)
{
    int cadastrei = 0;

    if (artista != NULL)
    {
        cadastrei = insere_no_RB_album(&(artista->artista.albuns),album);

        if (cadastrei==1)
            artista->artista.num_albuns++;
        
    }

    return cadastrei;

}

/*
Busca um album dentro de um artista, podendo retornar a referência daquele album em caso de encontrar ou NULL caso falhe

Args:
    artista::RB_artista*: Referência do nó que contem o artista que iremos acessar buscando o album.
    titulo_album::char: Titulo do album que estaremos buscando.

Return:
    no_album_buscado::RB_album*: Referência do album buscado
*/
RB_album * buscar_album_artista(RB_artista *artista, char titulo_album[TAM_TITULO])
{
    RB_album *no_album_buscado = NULL;

    if (artista != NULL)   
        no_album_buscado = buscar_no_RB_album(artista->artista.albuns,titulo_album);


    return no_album_buscado;

}

/*
Remove um nó album de uma arvore de albuns respeitando todas as normas da Rubro Negro e decrementa a quantidade de albuns do artista
Casos de retorno:
    1 - Sucesso
    0 - Falha

Args:
    artista::RB_artista*: Referência do artista que terá um album removido
    titulo_album::char: Nome do artista que será removido

Return:
    removi::int: Sinalização baseada no resultado da operação de remoção
*/
int remover_album_artista(RB_artista *artista, char titulo_album[TAM_TITULO])
{
    int removi =  remove_no_album_ARVRB(&(artista->artista.albuns),titulo_album);
    if(removi==1)
        artista->artista.num_albuns --;

    return removi;
}



/* A ideia era buscar dentre todos os artistas qual tinha o album que eu quero, mas faltou ideias de como implementar
RB_album * buscar_album_arv_artista(RB_artista *arvore, char titulo_album[TAM_TITULO])
{
    RB_album *no_album_buscado = NULL;

    if (arvore != NULL) 
    {
        no_album_buscado = buscar_album_artista(arvore,titulo_album);
        if (no_album_buscado==NULL)
        {
            no_album_buscado = buscar_album_arv_artista(arvore->esquerda,titulo_album);
            no_album_buscado = buscar_album_arv_artista(arvore->direita,titulo_album);
        }
    }  
    return no_album_buscado;
    }

*/      

/*
Retorna a confirmação sobre o ato de remover um nó
    1 - Pode
    0 - Não

Args:
    no::RB_artista*: Referencia do nó artista que estamos checando a possibilidade de removelo

Return:
    confirmacao::int: Sinalização de confirmação sobre o ato de remover
*/
int pode_remover_artista(RB_artista *no)
{
    int confirmacao = 0;

    if(no->artista.num_albuns == 0)
        confirmacao = 1;

    return confirmacao;
}

/*
Retorna a confirmação sobre o ato de remover um nó
    1 - Pode
    0 - Não

Args:
    no::RB_album*: Referencia do nó album que estamos checando a possibilidade de removelo

Return:
    confirmacao::int: Sinalização de confirmação sobre o ato de remover
*/
int pode_remover_album(RB_album *no)
{
    int confirmacao = 0;

    if(no->album.qtd_musicas == 0)
        confirmacao = 1;
    
    return confirmacao;
}

void mostrar_no_artista(RB_artista * artista)
{
    printf("\n\n------------------------\n");
    printf("\n\tCor: %d\n\tNome: %s",artista->cor_artista,artista->artista.nome);
    printf("\n\n------------------------\n");
}

void mostrar_todos_nos_artista_ordenado(RB_artista *artista)
{
    if (artista!=NULL)
    {
        mostrar_todos_nos_artista_ordenado(artista->esquerda);
        mostrar_no_artista(artista);
        mostrar_todos_nos_artista_ordenado(artista->direita);
    }
    
}



//Esta função remove todas as musicas,albuns e artistas do sistema visando liberar toda a memória usada!
void encerrar_sistema(RB_artista **arvore)
{
    if(*arvore != NULL)
    {
        encerrar_sistema(&((*arvore)->esquerda));
        encerrar_sistema(&((*arvore)->direita));
    }
}
