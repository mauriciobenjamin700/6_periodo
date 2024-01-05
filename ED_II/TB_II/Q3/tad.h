typedef struct Info Info;
typedef struct Memoria Memoria;
typedef struct Quebra Quebra;


Info *criaInfo(int inicio, int fim, int status);
Memoria *criaNo(Info *info, Memoria *NoEsq, Memoria *noCentroEsq);
int ehFolha(Memoria *no);
void adicionaInfo(Memoria **No, Info *info, Memoria *filho);
Quebra quebraNo(Memoria **raiz, Info *info, Memoria *filho);
void inserir45(Memoria **raiz, Memoria *pai, Info **sobe, int inicio, int fim, int status, int *flag);
Memoria *encontrarEspaco(Memoria *raiz, int espacoNecessario);
