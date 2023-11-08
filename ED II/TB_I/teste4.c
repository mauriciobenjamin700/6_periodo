#include <stdio.h>
#include <time.h>
#include "tad_avl.c"

//Tempos de Inserção na arvore AVL

#define DATA_SIZE 10000
#define TEST_SIZE 1
int main(void)
{
    clock_t start, end;
    float time;
    // float results[TEST_SIZE];

    int i;
    int id;
    char titulo[30];
    int sinal;
    float media = 0;

    Serie *s;

    if (iniciarS(&s))
    {
        for (i = 0; i < DATA_SIZE; i++)
        {
            start = clock();

            id = geraId(&s);
            Serie *new;
            snprintf(titulo, sizeof(titulo), "%d", i);
            preencherS(&new, id, titulo);
            sinal = cadastrarS(&s, new);

            end = clock();

            time = (float)(end - start) / CLOCKS_PER_SEC * 1000.0; // tempo decorrido em milissegundos
            media += time;
        }
    }
    /*
        for(i=0;i<TEST_SIZE;i++)
        {
            printf("\n%f", results[i]);
        }
    */

    printf("\nTotal: %.2f", media);
    printf("\n\nMedia: %.2f", media / DATA_SIZE);

    printf("\n\n%d", sinal);
    return 0;
}
