typedef struct info Info;
typedef struct memoria Memoria;


Info *criaInfo(int inicio, int fim, char status);
Memoria *criaNo(Info *info, Memoria *NoEsq, Memoria *noCentroEsq);
int ehFolha(Memoria *no);
void adicionaNo(Memoria **No, Info *info, Memoria *filho);
Memoria *quebraNo(Memoria **raiz, Info *info, Info **sobe, Memoria *filho);
Memoria *inserir45(Memoria **raiz, Memoria *pai, Info **sobe, int inicio, int fim, char status, int *flag);