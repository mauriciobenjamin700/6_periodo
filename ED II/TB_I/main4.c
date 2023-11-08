#include <stdio.h>
#include <time.h>
#include "tad_avl.c"

#define DATA_SIZE 10000
#define TEST_SIZE 1
int main(void)
{
    clock_t start, end;
    float time;
    //float results[TEST_SIZE];
    int i;
    int id;
    char titulo[30];
    int sinal;
    float media = 0;

    Serie *s;

    if(iniciarS(&s))
    {
        for(i=0;i<DATA_SIZE;i++)
        {
            id = geraId(&s);
            Serie* new;
            snprintf(titulo, sizeof(titulo), "%d", i);
            preencherS(&new, id,titulo);
            sinal = cadastrarS(&s, new);

        }
        
        for(i=0;i<TEST_SIZE;i++)
    {
        start = clock();

        mostrar_all_S(&s);

        end = clock();

        time = (float)(end - start) / CLOCKS_PER_SEC * 1000.0; // tempo decorrido em milissegundos
        //media += time;
        media+=time;

        //results[i] = time;
    }
    }
    
/*
    for(i=0;i<TEST_SIZE;i++)
    {
        printf("\n%f", results[i]);
    }
*/
    //media = media / DATA_SIZE;

    printf("\nTotal: %.2f", media);
    printf("\n\nMedia: %.2f", media / DATA_SIZE);   

    printf("\n\n%d",sinal);
    return 0;
}
