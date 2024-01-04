#define LIVRE 1
#define OCUPADO 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.c"

typedef struct info{
	int inicio;
	int fim;
	int status;
}Info;

typedef struct memoria
{
	Info *info1;
	Info *info2;
	Info *info3;
	Info *info4;

	struct memoria *esquerda;
	struct memoria *esquerda_centro;
	struct memoria *centro;
	struct memoria *direita_centro;
	struct memoria *direita;

	int numKeys;
} Memoria;

Info *criaInfo(int inicio, int fim, int status) {
	printf("%d\n",fim);
	Info *info = (Info*)malloc(sizeof(Info));
	info->inicio = inicio;
	info->fim = fim;
	info->status = status;
	return info;
}

Memoria *criaNo(Info *info, Memoria *NoEsq, Memoria *noCentroEsq) {
	Memoria *no = (Memoria*)malloc(sizeof(Memoria));
	no->info1 = info;
	no->numKeys = 1;
	no->esquerda = NoEsq;
	no->esquerda_centro = noCentroEsq;
	no->centro = NULL;
	no->direita_centro = NULL;
	no->direita = NULL;
	return no;
}

int ehFolha(Memoria *no) {
	int status;
	if (no->esquerda == NULL) status = 1;
	else status = 0;
	return status;
}

void adicionaNo(Memoria **No, Info *info, Memoria *filho) {
	if ((*No)->numKeys == 1) {
		if(info->status == (*No)->info1->status) {
			(*No)->info1->fim = info->fim;
		}
		else if (info->inicio > (*No)->info1->inicio) {
			(*No)->info2 = info;
			(*No)->centro = filho;
			(*No)->numKeys = 2;
		} else {
			(*No)->info2 = (*No)->info1;
			(*No)->info1 = info;
			(*No)->centro = (*No)->esquerda_centro;
			(*No)->esquerda_centro = filho;
			(*No)->numKeys = 2;
		}
	} else if ((*No)->numKeys == 2) {
		if(info->status == (*No)->info2->status) {
			(*No)->info2->fim = info->fim;
		}
		else if (info->inicio > (*No)->info2->inicio) {
			(*No)->info3 = info;
			(*No)->direita_centro = filho;
			(*No)->numKeys = 3;
		} else if (info->inicio > (*No)->info1->inicio && info->inicio < (*No)->info2->inicio) {
			(*No)->info3 = (*No)->info2;
			(*No)->info2 = info;
			(*No)->direita_centro = (*No)->centro;
			(*No)->centro = filho;
			(*No)->numKeys = 3;
		} else {
			(*No)->info3 = (*No)->info2;
			(*No)->info2 = (*No)->info1;
			(*No)->info1 = info;
			(*No)->direita_centro = (*No)->centro;
			(*No)->centro = (*No)->esquerda_centro;
			(*No)->esquerda_centro = filho;
			(*No)->numKeys = 3;
		}
	} else {
		if(info->status == (*No)->info3->status) {
				(*No)->info3->fim = info->fim;
			}
		else if (info->inicio > (*No)->info3->inicio) {
			(*No)->info4 = info;
			(*No)->direita = filho;
			(*No)->numKeys = 4;
		} else if (info->inicio > (*No)->info2->inicio && info->inicio < (*No)->info3->inicio) {
			(*No)->info4 = (*No)->info3;
			(*No)->info3 = info;
			(*No)->direita = (*No)->direita_centro;
			(*No)->direita_centro = filho;
			(*No)->numKeys = 4;
		} else if (info->inicio > (*No)->info1->inicio && info->inicio < (*No)->info2->inicio) {
			(*No)->info4 = (*No)->info3;
			(*No)->info3 = (*No)->info2;
			(*No)->info2 = info;
			(*No)->direita = (*No)->direita_centro;
			(*No)->direita_centro = (*No)->centro;
			(*No)->centro = filho;
			(*No)->numKeys = 4;
		} else {
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

Memoria *quebraNo(Memoria **raiz, Info *info, Info **sobe, Memoria *filho) {
	Memoria *maiorNo;

	if (info->inicio > (*raiz)->info4->inicio && (*raiz)->info4 != NULL) {
		*sobe = criaInfo((*raiz)->info3->inicio, (*raiz)->info3->fim, (*raiz)->info3->status);
		maiorNo = criaNo((*raiz)->info4, (*raiz)->direita_centro, (*raiz)->direita);
		maiorNo->info2 = info;
		maiorNo->centro = filho;
		maiorNo->numKeys = 2;
	} else if (info->inicio > (*raiz)->info3->inicio) {
		*sobe = (*raiz)->info3;
		maiorNo = criaNo(info, (*raiz)->direita_centro, filho);
		maiorNo->info2 = (*raiz)->info4;
		maiorNo->centro = (*raiz)->direita;
		maiorNo->numKeys = 2;
	} else if (info->inicio > (*raiz)->info2->inicio) {
		*sobe = info;
		maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->direita_centro);
		maiorNo->info2 = (*raiz)->info4;
		maiorNo->centro = (*raiz)->direita;
		maiorNo->numKeys = 2;
	} else if (info->inicio > (*raiz)->info1->inicio) {
		*sobe = (*raiz)->info2;
		maiorNo = criaNo((*raiz)->info3, (*raiz)->centro, (*raiz)->direita_centro);
		maiorNo->info2 = (*raiz)->info4;
		maiorNo->centro = (*raiz)->direita;
		maiorNo->numKeys = 2;
		(*raiz)->info2 = info;
		(*raiz)->centro = filho;
	} else {
		*sobe = (*raiz)->info2;
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

	return maiorNo;
}

void inserir45(Memoria **raiz, Memoria *pai, Info **sobe, int inicio, int fim, int status, int *flag, Memoria **maiorNO) {
	if (*raiz == NULL) {
		*raiz = criaNo(criaInfo(inicio, fim, status), NULL, NULL);
		*flag = 1; // informa que foi inserido
	} else {
		if (ehFolha(*raiz)) {
			*flag = 1; // informa que foi inserido
			if ((*raiz)->numKeys < 4) {
				adicionaNo(raiz, criaInfo(inicio, fim, status), NULL);
			} else {
				*maiorNO = quebraNo(raiz, criaInfo(inicio, fim, status), sobe, NULL);

				if (!pai) {
					*raiz = criaNo(*sobe, *raiz, *maiorNO);
					*maiorNO = NULL;
				} else {
					printf("Estoy loco\n");
				}
			}
		} else {
			if (inicio < (*raiz)->info1->inicio)
				inserir45(&(*raiz)->esquerda, *raiz, sobe, inicio, fim, status, flag, maiorNO);
			else if ((*raiz)->numKeys == 1 || ((*raiz)->numKeys <= 2 && inicio < (*raiz)->info2->inicio))
				inserir45(&((*raiz)->esquerda_centro), *raiz, sobe, inicio, fim, status, flag, maiorNO);
			else if (((*raiz)->numKeys == 2) || ((*raiz)->numKeys <= 2 && inicio < (*raiz)->info3->inicio))
				inserir45(&((*raiz)->centro), *raiz, sobe, inicio, fim, status, flag, maiorNO);
			else
				inserir45(&((*raiz)->direita), *raiz, sobe, inicio, fim, status, flag, maiorNO);

			if (*maiorNO) {
				if ((*raiz)->numKeys < 2) {
					adicionaNo(raiz, *sobe, *maiorNO);
					*maiorNO = NULL;
				} else {
					*maiorNO = quebraNo(raiz, *sobe, sobe, *maiorNO);

					if (pai == NULL) {
						*raiz = criaNo(*sobe, *raiz, *maiorNO);
						*maiorNO = NULL;
					}
				}
			}
		}
	}
}


