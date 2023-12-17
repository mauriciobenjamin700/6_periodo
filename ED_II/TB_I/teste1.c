#include <stdio.h>
#include <time.h>
#include "tad.c"

//Tempos de busca na arvore binária de busca

#define DATA_SIZE 1000
#define TEST_SIZE 1000
int main(void)
{
    clock_t start, end;
    float time;
    //float results[TEST_SIZE];
    float total = 0;
    int i;
    int id;
    char titulo[30];
    int sinal;
    //float media = 0;

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
        
    
    start = clock();

    mostrar_all_S(&s);

    end = clock();

    time = (float)(end - start) / CLOCKS_PER_SEC * 1000.0; // tempo decorrido em milissegundos
    //media += time;
    total+=time;

        //results[i] = time;
    
    }
    
/*
    for(i=0;i<TEST_SIZE;i++)
    {
        printf("\n%f", results[i]);
    }
*/
    //media = media / DATA_SIZE;

    printf("\n\nMedia: %.2f",total);    

    printf("\n\n%d",sinal);
    return 0;
}
