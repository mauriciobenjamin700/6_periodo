typedef struct Artista Artista;
typedef struct Arv_23_artista Arv_23_artista;
void preencher_artista(Artista *artista, char nome[], char tipo[], char estilo[]); 
Arv_23_artista *cria_no_artista();
int no_artista_eh_folha(Arv_23_artista *no);
void ordenar_artistas(Artista *a1, Artista *a2, Artista *a3);
Arv_23_artista *sobe_no_artista_pai(Arv_23_artista **pai, Artista sobiu, Arv_23_artista *esquerda, Arv_23_artista *direita);
//Arv_23_artista * quebra_no_artista(Arv_23_artista *raiz, Artista artista);
int inserir_artista_arv23(Arv_23_artista **raiz, Artista artista);
