#include "artista.c"

int inserir_musica_album(Album *album,Musica musica)
{
    int inseri = 0;

    if(album->musicas == NULL)
    {
        album->musicas = iniciar_no_lista();

        if(album->musicas != NULL)
        {
            inseri = adicionar_musica_ordenada(&(album->musicas),&musica);
        }
    }

    return inseri;
}

int inserir_album_artista(Arv_23_artista **raiz,Artista *artista, Album album)
{
    *raiz =  inserir_album_arv23(artista->albuns,album);
}
