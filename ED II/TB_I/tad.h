typedef struct Participante;
typedef struct Temporada;
typedef struct Serie;

//Inicia a arvore de Series
int iniciarS(Serie* s);

//preenche um nó serie com suas inforamções
void preencherS(Serie  **s);

void mostarS(Serie s);

//Cadastra um participante
void cadastrarP();
//Cadastra uma temporada
void cadastrarT();
//Cadastra uma serie
int cadastrarS();

/*
(a)Imprimir em ordem pelo código da série: o título, o número de temporadas
*/
void imprimirA(); 

/*
(b)Imprimir os dados de todas as temporadas de uma série, cujo o usuário informe o código da série
*/
void imprimirB();
/*
(c)Imprimir  todos  os  personagens  de  uma  determinada  temporada  de  uma  dada  série,  cujo  o  usuário informe o código da série e o número da temporada.
*/
void imprimirC();

/*
(d)Imprimir  o  nome  de  todos  os  artistas  que  interpretaram  um  determinado  personagem  em  todas  as temporadas de uma dada série, cujo o usuário informe o código da série
*/
void imprimirD();

