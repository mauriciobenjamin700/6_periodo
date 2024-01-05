#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "tad.h"

#define LIVRE 1
#define OCUPADO 0

typedef struct Info
{
    int inicio;
    int fim;
    int status;
} Info;

typedef struct Memoria
{
    Info *info1;
    Info *info2;
    Info *info3;
    Info *info4;

    struct Memoria *esquerda;
    struct Memoria *esquerda_centro;
    struct Memoria *centro;
    struct Memoria *direita_centro;
    struct Memoria *direita;

    int numKeys;

} Memoria;


typedef struct Quebra
{
    Memoria *maior_no;
    Info *sobe;
}Quebra;

/*
    A função cria um informação com os dados recebidos.

    Args: 
        int inicio, fim, status

    return:
        Info info 

*/
Info *criaInfo(int inicio, int fim, int status)
{
    Info *info = (Info *)malloc(sizeof(Info)); // Correção na alocação de memória
    if (info != NULL)
    {
        info->inicio = inicio;
        info->fim = fim;
        info->status = status;
    }
    return info;
}


/*
    A função cria um nó da arvore.

    Args: 
        Info info
        Memoria NoEsq, noCentroEsq

    return:
        Memoria no 

*/
Memoria *criaNo(Info *info, Memoria *NoEsq, Memoria *noCentroEsq)
{
    Memoria *no = (Memoria *)malloc(sizeof(Memoria));
    no->info1 = info;
    no->numKeys = 1;
    no->esquerda = NoEsq;
    no->esquerda_centro = noCentroEsq;
    no->centro = NULL;
    no->direita_centro = NULL;
    no->direita = NULL;
    return no;
}

/*
    A função verifica se o no recebido é folha
    Caso seja folha retorna 1 caso contrario retorna 0.

    Args: 
        Memoria no

    return:
        int status 

*/
int ehFolha(Memoria *no)
{
    int status;
    if (no->esquerda == NULL)
        status = 1;
    else
        status = 0;
    return status;
}

/*
    A função adicionaInfo insere a uma informação na arvore
    Em caso da informação ser do mesmo status que sua anterior as informações se unem
    e o fim da informação anterior vai receber o fim da nova informação.

    Args: 
        Memoria No, filho
        Info info

    return:
        none 

*/
void adicionaInfo(Memoria **No, Info *info, Memoria *filho)
{
    if ((*No)->numKeys == 1)
    {
        if (info->status == (*No)->info1->status)
        {
            (*No)->info1->fim = info->fim;
        }
        else if (info->inicio > (*No)->info1->inicio)
        {
            (*No)->info2 = info;
            (*No)->centro = filho;
            (*No)->numKeys = 2;
        }
        else
        {
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;
            (*No)->centro = (*No)->esquerda_centro;
            (*No)->esquerda_centro = filho;
            (*No)->numKeys = 2;
        }
    }
    else if ((*No)->numKeys == 2)
    {
        if (info->status == (*No)->info2->status)
        {
            (*No)->info2->fim = info->fim;
        }
        else if (info->inicio > (*No)->info2->inicio)
        {
            (*No)->info3 = info;
            (*No)->direita_centro = filho;
            (*No)->numKeys = 3;
        }
        else if (info->inicio > (*No)->info1->inicio && info->inicio < (*No)->info2->inicio)
        {
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = info;
            (*No)->direita_centro = (*No)->centro;
            (*No)->centro = filho;
            (*No)->numKeys = 3;
        }
        else
        {
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;
            (*No)->direita_centro = (*No)->centro;
            (*No)->centro = (*No)->esquerda_centro;
            (*No)->esquerda_centro = filho;
            (*No)->numKeys = 3;
        }
    }
    else
    {
        if (info->status == (*No)->info3->status)
        {
            (*No)->info3->fim = info->fim;
        }
        else if (info->inicio > (*No)->info3->inicio)
        {
            (*No)->info4 = info;
            (*No)->direita = filho;
            (*No)->numKeys = 4;
        }
        else if (info->inicio > (*No)->info2->inicio && info->inicio < (*No)->info3->inicio)
        {
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = info;
            (*No)->direita = (*No)->direita_centro;
            (*No)->direita_centro = filho;
            (*No)->numKeys = 4;
        }
        else if (info->inicio > (*No)->info1->inicio && info->inicio < (*No)->info2->inicio)
        {
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = info;
            (*No)->direita = (*No)->direita_centro;
            (*No)->direita_centro = (*No)->centro;
            (*No)->centro = filho;
            (*No)->numKeys = 4;
        }
        else
        {
            (*No)->info4 = (*No)->info3;
            (*No)->info3 = (*No)->info2;
            (*No)->info2 = (*No)->info1;
            (*No)->info1 = info;
            (*No)->direita = (*No)->direita_centro;
            (*No)->direita_centro = (*No)->centro;
            (*No)->centro = (*No)->esquerda_centro;
            (*No)->esquerda_centro = filho;
            (*No)->numKeys = 4;
        }
    }
}


/*
    A função é chamada quando todas as informações do nó foram preenchidas
    ela verifica quais as maiores informações e as unem em um novo nó
    e pega os dados da informação mediana retornando uma estrutura 
    que armazena esses dois dados
    Args: 
        Memoria raiz, filho
        Info info

    return:
        Quebra quebrou 

*/
Quebra quebraNo(Memoria **raiz, Info *info, Memoria *filho)
{
    Memoria *maiorNo;
    Info *sobe = NULL;
    Quebra quebrou;

    if (info->inicio > (*raiz)->info4->inicio && (*raiz)->info4 != NULL)
    {
        sobe = criaInfo((*raiz)->info3->inicio, (*raiz)->info3->fim, (*raiz)->info3->status);
        maiorNo = criaNo((*raiz)->info4, (*raiz)->direita_centro, (*raiz)->direita);
        maiorNo->info2 = info;
        maiorNo->centro = filho;
        maiorNo->numKeys = 2;
    }
    else if (info->inicio > (*raiz)->info3->inicio)
    {
        sobe = (*raiz)->info3;
        maiorNo = criaNo(info, (*raiz)->direita_centro, filho);
        maiorNo->info2 = (*raiz)->info4;
        maiorNo->centro = (*raiz)->direita;
        maiorNo->numKeys = 2;
    }
    else if (info->inicio > (*raiz)->info2->inicio)
    {
        sobe = info;
        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->direita_centro);
        maiorNo->info2 = (*raiz)->info4;
        maiorNo->centro = (*raiz)->direita;
        maiorNo->numKeys = 2;
    }
    else if (info->inicio > (*raiz)->info1->inicio)
    {
        sobe = (*raiz)->info2;
        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->direita_centro);
        maiorNo->info2 = (*raiz)->info4;
        maiorNo->centro = (*raiz)->direita;
        maiorNo->numKeys = 2;
        (*raiz)->info2 = info;
        (*raiz)->centro = filho;
    }
    else
    {
        sobe = (*raiz)->info2;
        maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->direita_centro);
        maiorNo->info2 = (*raiz)->info4;
        maiorNo->centro = (*raiz)->direita;
        maiorNo->numKeys = 2;
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->centro = (*raiz)->esquerda_centro;
        (*raiz)->info1 = info;
        (*raiz)->esquerda_centro = filho;
    }

    (*raiz)->numKeys = 2;
    (*raiz)->direita_centro = NULL;
    (*raiz)->direita = NULL;

    (*raiz)->info3 = NULL;
    (*raiz)->info4 = NULL;

    quebrou.maior_no = maiorNo;
    quebrou.sobe = sobe;

    return quebrou;
}

/*
    A função inserir45 é responsável por inserir novos elementos 
    na árvore e realizar o balanceamento da árvore conforme necessário.

    Args: 
        Memoria raiz, pai
        Info info
        int inicio, fim, status, flag
        
    return:
        none

*/
void inserir45(Memoria **raiz, Memoria *pai, Info **sobe, int inicio, int fim, int status, int *flag)
{
    if (*raiz == NULL)
    {
        Info *nova_info = criaInfo(inicio, fim, status);
        *raiz = criaNo(nova_info, NULL, NULL);
        *flag = 1; // informa que foi inserido
    }
    else
    {
        if (ehFolha(*raiz))
        {
            *flag = 1; // informa que foi inserido
            if ((*raiz)->numKeys < 4)
            {
                Info *nova_info = criaInfo(inicio, fim, status);
                adicionaInfo(raiz, nova_info, NULL);
            }
            else
            {
                Info *nova_info = criaInfo(inicio, fim, status);
                Quebra resultado = quebraNo(raiz, nova_info, NULL);

                if (!pai)
                {
                    *raiz = criaNo(resultado.sobe, *raiz, resultado.maior_no);
                }
                else
                {   
                    if(pai->numKeys < 4){
                        adicionaInfo(&pai, resultado.sobe, resultado.maior_no);
                    }
                    else{
                        resultado = quebraNo(&pai, resultado.sobe, resultado.maior_no);
                        pai = criaNo(resultado.sobe, pai, resultado.maior_no);
                    }
                }
            }
        }
        else
        {
            if (inicio < (*raiz)->info1->inicio)
                inserir45(&(*raiz)->esquerda, *raiz, sobe, inicio, fim, status, flag);

            else if ((*raiz)->numKeys == 1 || ((*raiz)->numKeys <= 2 && inicio < (*raiz)->info2->inicio))
                inserir45(&((*raiz)->esquerda_centro), *raiz, sobe, inicio, fim, status, flag);

            else if (((*raiz)->numKeys == 2) || ((*raiz)->numKeys <= 2 && inicio < (*raiz)->info3->inicio))
                inserir45(&((*raiz)->centro), *raiz, sobe, inicio, fim, status, flag);

            else
                inserir45(&((*raiz)->direita), *raiz, sobe, inicio, fim, status, flag);

                
            }
        }
    }


    Memoria *encontrarEspacoRecursivo(Memoria *raiz, int espacoNecessario) {
    Memoria *encontrado = NULL;
    if (raiz != NULL) {
        if (ehFolha(raiz)) {
            // Verifica espaço disponível e se o status é LIVRE apenas em folhas
            int espacoDisponivel1 = raiz->info1->fim - raiz->info1->inicio;
            int espacoDisponivel2 = (raiz->numKeys >= 2) ? raiz->info2->fim - raiz->info2->inicio : 0;
            int espacoDisponivel3 = (raiz->numKeys >= 3) ? raiz->info3->fim - raiz->info3->inicio : 0;
            int espacoDisponivel4 = (raiz->numKeys == 4) ? raiz->info4->fim - raiz->info4->inicio : 0;

            if (raiz->info1->status == LIVRE && espacoDisponivel1 >= espacoNecessario) {
                encontrado = raiz;
            } else if (raiz->numKeys >= 2 && raiz->info2->status == LIVRE && espacoDisponivel2 >= espacoNecessario) {
                encontrado = raiz;
            } else if (raiz->numKeys >= 3 && raiz->info3->status == LIVRE && espacoDisponivel3 >= espacoNecessario) {
                encontrado = raiz;
            } else if (raiz->numKeys == 4 && raiz->info4->status == LIVRE && espacoDisponivel4 >= espacoNecessario) {
                encontrado = raiz;
            }
        }
        else{
            encontrado = encontrarEspacoRecursivo(raiz->esquerda);
            if(raiz->esquerda != NULL){
                encontrarEspacoRecursivo(raiz->esquerda);
            }
        }
    }
    
}

Memoria *encontrarEspaco(Memoria *raiz, int espacoNecessario) {
    return encontrarEspacoRecursivo(raiz, espacoNecessario);
}
