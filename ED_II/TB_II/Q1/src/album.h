#ifndef ALBUM_H_INCLUDED
#define ALBUM_H_INCLUDED

#include "musica.h"

typedef struct Album Album;
typedef struct RB_album RB_album;

void preencher_album(Album *album, char titulo[], int ano);
int adiciona_musica_no_album(RB_album *album, Musica *musica);
Lista_musicas * buscar_musica_no_album(RB_album *album,char titulo[]);
int remover_musica_album(Album *album, char titulo[]);
void mostrar_album(Album *album);
int cor_album(RB_album *raiz);
void troca_cor_album(RB_album *raiz);
RB_album *rotacao_direita_album(RB_album *raiz);
RB_album *rotacao_esquerda_album(RB_album *raiz);
RB_album *balancear_RB_album(RB_album **raiz);
RB_album *move2EsqRED_album(RB_album *no);
RB_album *move2DirRED_album(RB_album *no);
RB_album * remover_menor_album(RB_album *no);
RB_album *procura_menor_album(RB_album *no);
RB_album *cria_no_album(char titulo[], int ano);
int insere_no_RB_album(RB_album **raiz, RB_album *novo);
void mostrar_no_RB_album(RB_album *no);
void mostrar_tudo_RB_album(RB_album *raiz);
RB_album *buscar_no_RB_album(RB_album *raiz,char titulo_buscado[]);
RB_album *remove_no_album(RB_album *raiz, char titulo_album[]);
void troca_cor_raiz_RB_album(RB_album *raiz);
int remove_no_album_ARVRB(RB_album **raiz, char titulo_album[]);
int pode_remover_album(RB_album *no);
void remover_todos_albuns(RB_album **raiz);


#endif 