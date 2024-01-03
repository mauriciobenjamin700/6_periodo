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
            album->qtd_musicas+=1;
        }
            
    }

    return inseri;
}

/*
Insere um album em um artista e retorna o resultado
    0 - Caso o album já estivesse cadastrado
    1 - Caso inseriu com sucesso 

Args:
    artista::Artista*: Referência para o artista que receberá um novo album;
    Album::Album: Estrutura album que será inserida na arvore se possivel

Return:
    inseri::int: Sinalização referente ao resultado da operação
*/
int inserir_album_artista(Artista *artista, Album album)
{
    int inseri = 0;
    if (buscar_album(artista->albuns,album.titulo) == NULL)
    {
        artista->albuns =  inserir_album_arv23(artista->albuns,album);
        inseri = 1;
        artista->num_albuns +=1;
    }

    return inseri;
}

Musica * buscar_musica_album(Album *album, char titulo_musica[])
{
    return buscar_musica(album->musicas,titulo_musica);
}


/*
Busca uma estrutura Album dentro de um artista e retorna sua referência sendo ela:
    NULL - Caso não encontre
    Album* - Caso encontre

Args:
    artista::Artista*: Referência do artista que guarda os albums
    nome_album::char: Nome do album que estamos buscando

Return:
    album_buscado::Album*: Resultado da busca

*/
Album * buscar_album_artista(Artista *artista, char titulo_album[])
{
    return buscar_album(artista->albuns,titulo_album);
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
int pode_remover_album(Album *no)
{
    int confirmacao = 0;

    if(no->qtd_musicas == 0)
        confirmacao = 1;
    
    return confirmacao;
}

/*
Retorna a confirmação sobre o ato de remover um nó
    1 - Pode
    0 - Não

Args:
    no::RB_artista*: Referencia do nó artista que estamos checando a possibilidade de removelo

Return:
    confirmacao::int: Sinalização de confirmação sobre o ato de remover
*/
int pode_remover_artista(Artista *no)
{
    int confirmacao = 0;

    if(no->num_albuns == 0)
        confirmacao = 1;

    return confirmacao;
}

/*
Remove uma música de um album de musicas e sinaliza o resultado da remoção:
    0 - Fracasso
    1 - Sucesso

Args:
    album::Album*: Referência de um album
    titulo_musica::char: Titulo da musica que estamos querendo remover

Return:
    sinal::int: Sinalização referente ao resultado da operação 
*/
int remover_musica_album(Album *album, char titulo_musica[])
{
    int sinal = remover_musica(&album->musicas,titulo_musica);
    if(sinal)
        album->qtd_musicas -=1;
    return sinal;
}

int remover_album_artista(Artista *artista,char titulo_album[])
{
    int sinal = 0;

    Arv_23_album *no_buscado =  buscar_no_album(artista->albuns,titulo_album);

    if(no_buscado != NULL)
    {
        artista->albuns = remover_album_arv23(no_buscado,titulo_album);
        artista->num_albuns -=1;
    }

    return sinal;
}