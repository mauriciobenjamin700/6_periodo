#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista;
typedef struct RB_artista;
Artista *criar_Artista();
void preencher_artista(Artista *artista,char nome[NOME], char tipo[TIPO], char estilo[ESTILO], int num_albuns, int id);
RB_artista * cria_no_artista(int cor,Artista artista);
void trocar_cor(RB_artista *no);
void trocar_cor_raiz(RB_artista *no);
int cor(RB_artista *no);
RB_artista* rotacao_direita_artista(RB_artista *raiz);
RB_artista* rotacao_esquerda_artista(RB_artista *raiz);
RB_artista *move2EsqRED(RB_artista *no);
RB_artista *move2DirRED(RB_artista *no);
RB_artista *balancear_RB_artista(RB_artista *no);
RB_artista *insere_no_artista(RB_artista *raiz, RB_artista *novo_no);