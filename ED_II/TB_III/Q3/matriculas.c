#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MATRICULAS 1000
#define TAM_MATRICULA 6

void gerar(int matriculas[][TAM_MATRICULA])
{
    srand(time(NULL));
    for (int i = 0; i < NUM_MATRICULAS; i++)
    {
        for (int j = 0; j < TAM_MATRICULA; j++)
        {
            matriculas[i][j] = rand() % 10; // Gera um dígito aleatório de 0 a 9
        }
    }
}

void salvarMatriculasEmArquivo(int matriculas[][TAM_MATRICULA])
{
    FILE *arquivo;
    arquivo = fopen("matriculas.txt", "w");

    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_MATRICULAS; i++)
    {
        for (int j = 0; j < TAM_MATRICULA; j++)
        {
            fprintf(arquivo, "%d", matriculas[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
}

int main()
{
    int matriculas[NUM_MATRICULAS][TAM_MATRICULA];

    gerar(matriculas);
    salvarMatriculasEmArquivo(matriculas);

    printf("Matrículas geradas e salvas no arquivo matriculas.txt.\n");

    return 0;
}
