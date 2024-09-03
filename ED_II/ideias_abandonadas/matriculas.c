#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MATRICULAS 1000
#define TAM_MATRICULA 6

int valida_matricula(int matriculas[][TAM_MATRICULA], int novaMatricula[], int indice)
{
    int igual = 0;

    for (int i = 0; i < indice; i++)
    {
        int cont = 0;
        for (int j = 0; j < TAM_MATRICULA; j++)
        {
            if (matriculas[i][j] == novaMatricula[j])
            {
                cont++;
            }
        }
        if (cont == TAM_MATRICULA)
        {
            // Encontrou uma matrícula igual, retorna true
            igual = 1;
        }
    }
    // Não encontrou matrícula igual, retorna false
    return igual;
}



void gerar_matriculas(int matriculas[][TAM_MATRICULA])
{
    srand(time(NULL));

    for (int i = 0; i < NUM_MATRICULAS; i++)
    {
        int novaMatricula[TAM_MATRICULA];

        do
        {
            // Gera uma nova matrícula até encontrar uma única
            for (int j = 0; j < TAM_MATRICULA; j++)
            {
                novaMatricula[j] = rand() % 10;
            }
        } while (valida_matricula(matriculas, novaMatricula, i));

        // Adiciona a nova matrícula ao vetor
        for (int j = 0; j < TAM_MATRICULA; j++)
        {
            matriculas[i][j] = novaMatricula[j];
        }
    }
}

void salva_matricula_arquivo(int matriculas[][TAM_MATRICULA])
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

    gerar_matriculas(matriculas);
    salva_matricula_arquivo(matriculas);

    printf("Matrículas geradas e salvas no arquivo matriculas.txt.\n");

    return 0;
}
