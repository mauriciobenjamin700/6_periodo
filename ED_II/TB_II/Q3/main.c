#include "tad.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para usar a função rand()
#define BLOCO 100

int main() {
    Memoria *arvore = NULL; // Inicialize arvore como NULL
    int inicio, fim, status;
    int flag = 0;
    char opc;
    srand(time(NULL)); // Inicializa a semente para gerar números aleatórios
    
    do{
    printf("Indique o inicio e o fim do primeiro bloco de memoria(1 a %d).\n",BLOCO);
    printf("Inicio:");
    scanf("%d",&inicio);
    printf("Fim:");
    scanf("%d",&fim);
    }while (inicio < 1 || fim > BLOCO);

    do {
        printf("O bloco esta livre ou ocupado? L - Livre O - Ocupado\n");
        scanf(" %c", &opc);
        switch (opc) {
            case 'L':
                status = LIVRE;
                break;
            case 'O':
                status = OCUPADO;
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (status != LIVRE && status != OCUPADO);

    inserir45(&arvore,NULL,NULL,inicio,fim,status,&flag);
    inicio = fim+1;
    while (fim != BLOCO) {
        printf("Informe o valor de fim para o proximo bloco (de %d ate %d): ",inicio, BLOCO);
        scanf("%d", &fim);

        if (fim >= 1 && fim <= BLOCO) {
            status = rand() % 2;
            flag = 0;
            inserir45(&arvore, NULL, NULL, inicio, fim, status, &flag);
            inicio = fim+1;
        } else {
            printf("Valor de fim inválido. Informe um valor entre 1 e %d.\n", BLOCO);
        }
    }

    return 0;
}