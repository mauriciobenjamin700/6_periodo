#include "artista.c"
/*
Insere uma musica em um album e retorna o resultado da operação
    1 - Sucesso ao adicionar;
    0 - Falha ao adicionar;
   -1 - Musica já estava cadastrada.

Args:
    album::Album*: Referência da estrutura album que irá receber a musica
    musica::Musica: Estrutura Musica que será adicionada ao album

Return:
    inseri::int: Resultado da operação
*/
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

/*
Busca a referência de uma estrutura Musica em um album e retorna o resultado da busca
    NULL - Caso não encontre
    Musica* - Caso encontre

Args:
    album::Album*: Referência de um album que terá uma de suas musicas buscadas
    titulo_musica::char: TItulo da música que estamos buscando

Return:
    musica_buscada::Musica*: Resultado da busca 
*/
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
Retorna a confirmação sobre o ato de remover um album
    1 - Pode
    0 - Não

Args:
    no::Album*: Referencia de uma estrutura album que estamos checando a possibilidade de removelo

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
Retorna a confirmação sobre o ato de remover uma estrutura Artista
    1 - Pode
    0 - Não

Args:
    no::Artista*: Referencia de uma estrutura Artista que estamos checando a possibilidade de removelo

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

/*
Remove um album de um artista e retorna o resultado do processo
    0 - Fracasso
    1 - Sucesso

Args:
    artista::Artista*: Referência de uma estrutura Artista
    titulo_musica::char: Titulo do album que estamos querendo remover

Return:
    sinal::int: Sinalização referente ao resultado da operação 
*/
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


/*
Remove todos os albuns de uma arvore e suas musicas
*/
void remover_todos_albuns(Arv_23_album **raiz)
{
    if(*raiz != NULL)
    {
        remover_todos_albuns(&(*raiz)->esquerda);
        remover_todos_albuns(&(*raiz)->centro);
        remover_todos_albuns(&(*raiz)->direita);
        
        if((*raiz)->qtd_infos == 2)
        {
            remover_todas_musicas(&(*raiz)->info1.musicas);
            remover_todas_musicas(&(*raiz)->info2.musicas);
        }
        else
            remover_todas_musicas(&(*raiz)->info1.musicas);
        
        free(*raiz);
        
    }
}

/*
Remove todos os artistas de uma arvore 2-3
*/
void remover_todos_artistas(Arv_23_artista **raiz)
{
    if(*raiz != NULL)
    {
        remover_todos_artistas(&(*raiz)->esquerda);
        remover_todos_artistas(&(*raiz)->centro);
        remover_todos_artistas(&(*raiz)->direita);

        if((*raiz)->qtd_infos == 2)
        {
            remover_todos_albuns(&(*raiz)->info1.albuns);
            remover_todos_albuns(&(*raiz)->info2.albuns);
        }
        else
            remover_todos_albuns(&(*raiz)->info1.albuns);
        
        free(*raiz);
    }
}