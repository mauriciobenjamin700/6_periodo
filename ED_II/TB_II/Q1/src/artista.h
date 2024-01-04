#ifndef ARTISTA_H_INCLUDED
#define ARTISTA_H_INCLUDED
#include "album.h"

typedef struct Artista Artista;
typedef struct RB_artista RB_artista;

void preencher_artista(Artista *artista, char nome[], char tipo[], char estilo[]);
RB_artista *cria_no_artista(Artista artista);
void trocar_cor_artista(RB_artista *no);
void troca_cor_raiz_RB_artista(RB_artista *raiz);
int cor_artista(RB_artista *no);
RB_artista *rotacao_direita_artista(RB_artista *raiz);
RB_artista *rotacao_esquerda_artista(RB_artista *raiz);
RB_artista *move2EsqRED_artista(RB_artista *no);
RB_artista *move2DirRED_artista(RB_artista *no);
RB_artista *balancear_RB_artista(RB_artista *no);
RB_artista * remover_menor_artista(RB_artista *no);
RB_artista *procura_menor_artista(RB_artista *no);
int insere_no_artista(RB_artista **raiz, RB_artista *novo_no);
int insere_no_artista_ARVRB(RB_artista **raiz, RB_artista *novo_nov);
RB_artista *busca_no_artista(RB_artista *raiz, char nome_artista[]);
void mostrar_artista(Artista artista);
RB_artista *remove_no_artista(RB_artista *raiz, char nome_artista[]);
int remove_no_artista_ARVRB(RB_artista **raiz, char nome_artista[]);
int cadastrar_album_artista(RB_artista *artista, RB_album *album);
RB_album * buscar_album_artista(RB_artista *artista, char titulo_album[]);
int remover_album_artista(RB_artista *artista, char titulo_album[]);
void mostrar_no_artista(RB_artista * artista);
void mostrar_todos_nos_artista_ordenado(RB_artista *artista);



#endif // ARTISTA_H_INCLUDED