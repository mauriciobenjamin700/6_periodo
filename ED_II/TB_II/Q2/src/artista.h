typedef struct Artista Artista;
typedef struct Arv_23_artista Arv_23_artista;
void preencher_artista(Artista *artista, char nome[], char tipo[], char estilo[]); 
Arv_23_artista *cria_no_artista();
int no_artista_eh_folha(Arv_23_artista *no);
void ordenar_artistas(Artista *a1, Artista *a2, Artista *a3);
void quebra_no_artista(Arv_23_artista **no, Artista artista, Arv_23_artista *novo_no, Artista *vai_subir, Arv_23_artista *esquerda_novo_no, Arv_23_artista *centro_novo_no);
Arv_23_artista *sobe_artista(Arv_23_artista **pai, Arv_23_artista **raiz, Artista sobe, Arv_23_artista *novo_no);
Arv_23_artista *inserir_artista_arv23(Arv_23_artista *raiz, Artista artista);
void mostrar_no_artista(Arv_23_artista *no);
void mostrar_arv_artistas(Arv_23_artista *raiz);
Artista *buscar_artista(Arv_23_artista *raiz, char nome_artista[]);
Arv_23_artista *buscar_no_artista(Arv_23_artista *raiz, char nome_artista[]);
int conta_info_artista(Arv_23_artista *raiz);
Arv_23_artista *buscar_menor_artista(Arv_23_artista *raiz);
Arv_23_artista *buscar_maior_artista(Arv_23_artista *raiz);
int onde_estou_artista(Arv_23_artista *no);
Arv_23_artista *remover_artista_arv23(Arv_23_artista *vai_sumir, char nome_artista[]);

