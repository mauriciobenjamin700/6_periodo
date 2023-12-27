#include <stdio.h>
#include "cmp.c"
#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{
    char nome[NOME];
    char tipo[TIPO];
    char estilo[ESTILO];
    int num_albuns;

} Artista;

void ordenar_artistas(Artista *a1, Artista *a2, Artista *a3)
{
    Artista aux;
    //caso o primeiro seja maior que o segundo, e do que o terceiro
    if(compara_string(a1->nome,a2->nome)>0 && compara_string(a1->nome,a3->nome)>0)
    {
        //garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a1;
        *a1 = aux;

        //checagem pra saber quem fica no meio já que a3 guarda o maior
        if(compara_string(a1->nome,a2->nome)>0)
        {

            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    //caso o segundo seja o maior de todos
    else if(compara_string(a2->nome,a1->nome)>0 && compara_string(a2->nome,a3->nome)>0)
    {
        //garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a2;
        *a2 = aux;

        //checagem pra saber quem fica no meio já que a3 guarda o maior
        if(compara_string(a1->nome,a2->nome)>0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }

    }
    //caso o terceiro seja o maior de todos
    else if(compara_string(a3->nome,a1->nome)>0 && compara_string(a3->nome,a2->nome)>0)
    {
        //checagem pra saber quem fica no meio já que a3 guarda o maior
        if(compara_string(a1->nome,a2->nome)>0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }

    }
}

int main()
{
    Artista a1,a2,a3;

    printf("\nPreencha os valores de A1: ");
    setbuf(stdin,NULL);
    scanf("%s", a1.nome);

    printf("\nPreencha os valores de A2: ");
    setbuf(stdin,NULL);
    scanf("%s", a2.nome);

    printf("\nPreencha os valores de A3: ");
    setbuf(stdin,NULL);
    scanf("%s", a3.nome);

    printf("\n\nValores de entrada: %s | %s | %s \n", a1.nome,a2.nome,a3.nome);


    ordenar_artistas(&a1,&a2,&a3);

    printf("\n\nValores de Saida: %s | %s | %s \n", a1.nome,a2.nome,a3.nome);

    return 0;

}