#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "src/sistema.c"

#define TEST_SIZE 300
#define DIGIT 3

int main(void)
{
    clock_t start, end;
    float time;
    int i;
    char str[DIGIT];
    float media = 0;
    char buscar[TEST_SIZE][DIGIT];

    Artista artista;
    RB_artista *no;
    RB_artista *arvore;

    for (i = 0; i < TEST_SIZE; i++)
    {

        sprintf(str, "%d", i);
        //snprintf(str, sizeof(str), "%d", i);
        printf("\nValor: %s", str);
        preencher_artista(&artista, str, str, str); // Ajuste para strings fixas para 'tipo' e 'estilo'
        no = cria_no_artista(artista);
        insere_no_artista_ARVRB(&arvore, no);
    }

    for (i = 0; i < TEST_SIZE; i++)
    {
        start = clock();
        no = busca_no_artista(arvore, buscar[i]);
        end = clock();

        time = (float)(end - start) / CLOCKS_PER_SEC * 1000.0; // tempo decorrido em milissegundos
        media += time;
    }

    media = media / TEST_SIZE;

    printf("\n\nResultado: %f\n\n", media);

    encerrar_sistema(&arvore);
    return 0;
}
