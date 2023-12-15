typedef struct Musica Musica;
typedef struct Lista_musicas Lista_musicas;

void preencher_musica(Musica *musica, char titulo[], float minutos);
Lista_musicas *iniciar_no_lista();
int adicionar_musica_ordenada(Lista_musicas **raiz, Musica *musica);
void mostar_musica(Musica *musica);
void mostar_todas_musicas(Lista_musicas *no);
int contar_musicas(Lista_musicas *raiz);
Musica* buscar_musica(Lista_musicas *raiz, char titulo[]);
int remover_musica(Lista_musicas **raiz, char titulo[]);
void remover_todas_musicas(Lista_musicas **raiz);
