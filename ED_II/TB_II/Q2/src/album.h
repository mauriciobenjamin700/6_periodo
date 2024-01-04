typedef struct Album Album;
typedef struct Arv_23_album Arv_23_album;

void preencher_album(Album *album, char titulo[], int ano);
Arv_23_album *cria_no_album();
int no_album_eh_folha(Arv_23_album *no);
void ordenar_albums(Album *a1, Album *a2, Album *a3);
void quebra_no_album(Arv_23_album **no, Album album, Arv_23_album *novo_no, Album *vai_subir, Arv_23_album *esquerda_novo_no, Arv_23_album *centro_novo_no);
Arv_23_album *sobe_album(Arv_23_album **pai, Arv_23_album **raiz, Album sobe, Arv_23_album *novo_no);
Arv_23_album *inserir_album_arv23(Arv_23_album *raiz, Album album);
void mostrar_no_album(Arv_23_album *no);
void mostrar_arv_albums(Arv_23_album *raiz);
Album *buscar_album(Arv_23_album *raiz, char nome_album[]);
Arv_23_album *buscar_no_album(Arv_23_album *raiz, char nome_album[]);
int conta_info_album(Arv_23_album *raiz);
Arv_23_album *buscar_menor_album(Arv_23_album *raiz);
Arv_23_album *buscar_maior_album(Arv_23_album *raiz);
int onde_estou_album(Arv_23_album *no);
Arv_23_album *remover_album_arv23(Arv_23_album *vai_sumir, char nome_album[]);
void mostrar_album(Album *album);
void mostrar_tudo_album(Arv_23_album *raiz);



