typedef struct Participante;
typedef struct Temporada;
typedef struct Serie;

//Métodos para Serie
void iniciarS(Serie** s);
void preencherS(Serie **s, int id);
void mostrarS (Serie *s);
int cadastrarS(Serie **s, Serie *novo);
int validarS(Serie *s, int id);
Serie* buscarS(Serie *s, int id);
int geraId(Serie **s);
void mostrar_all_S(Serie **s);

void liberar_all_P(Participante **p);
void liberar_all_T(Temporada **t);
void liberar_all_S(Serie **s);

// Métodos para Temporada e Participantes
void cadastran_atores(Participante **l, int n_atores);
void preencherT(Temporada **t);
int cadastrarT(Temporada **t);
void mostrarT(Temporada *t);
Temporada *buscarT(Temporada *t, int id);
void mostrar_all_T(Temporada *t);
void mostrarP(Participante *p);
void mostrar_all_P(Participante *p);
void letra_D(Temporada *t);
void OrdenaAtores(Participante *head);
int comparaNomes(const char *name1, const char *name2);
void troca(Participante *a, Participante *b);
