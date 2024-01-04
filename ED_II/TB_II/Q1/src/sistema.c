#include "artista.c"



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

/*
Remove todos os albuns de uma arvore e suas musicas
*/
void remover_todos_albuns(RB_album **raiz)
{
    if(*raiz != NULL)
    {
        remover_todos_albuns(&(*raiz)->esquerda);
        remover_todos_albuns(&(*raiz)->direita);

        remover_todas_musicas(&(*raiz)->album.musicas);
        free(*raiz);
        
    }
}


/*
Remove todos os artistas de uma arvore
*/
void remover_todos_artistas(RB_artista **raiz)
{
    if(*raiz != NULL)
    {
        remover_todos_artistas(&(*raiz)->esquerda);
        remover_todos_artistas(&(*raiz)->direita);

        remover_todos_albuns(&(*raiz)->artista.albuns);
        free(*raiz);
        
    }
}

//Esta função remove todas as musicas,albuns e artistas do sistema visando liberar toda a memória usada para encerrar o sistema
void encerrar_sistema(RB_artista **arvore)
{
    if(*arvore != NULL)
    {
        remover_todos_artistas(&(*arvore));
    }
}

