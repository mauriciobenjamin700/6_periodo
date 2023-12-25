#include "artista.c"



int cadastrar_album_artista(RB_artista *artista, RB_album *Album)
{
    int sinal = 0;

    if (artista != NULL)
    {
        sinal = insere_no_RB_album(&(artista->artista.albuns),Album);

        if (sinal==1)
            artista->artista.num_albuns++;
        
    }

    return sinal;

}

RB_album * buscar_album_artista(RB_artista *artista, char titulo_album[TAM_TITULO])
{
    RB_album *no_album_buscado = NULL;

    if (artista != NULL)   
        no_album_buscado = buscar_no_RB_album(artista->artista.albuns,titulo_album);


    return no_album_buscado;

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

int pode_remover_artista(RB_artista *no)
{
    int confirmacao = 0;

    if(no->artista.num_albuns == 0)
        confirmacao = 1;

    return confirmacao;
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
