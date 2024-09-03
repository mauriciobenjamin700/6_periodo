#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

/*
O número de vertices que o grafo tem
81 vertices por que são 4 discos
*/
#define NUM_VERTICIES 81

typedef struct
{
    int NumVerticies;
    int Pinos;
    int Arestas[3];
} VerticiesInfo;

void FillVerticies(VerticiesInfo VerticiesList[]);
void PrintVector(VerticiesInfo VerticiesList[]);

void FillMatrizAdj(VerticiesInfo VerticiesList[], int matriz[][NUM_VERTICIES]);
void PrintMatriz(int matriz[][NUM_VERTICIES]);
void EncontraCaminhoCurto(int matriz[][NUM_VERTICIES]);

void Dijkstra(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies);
void BellmanFord(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies);

int main()
{
    VerticiesInfo VerticiesList[NUM_VERTICIES];
    int MatrizAdj[NUM_VERTICIES][NUM_VERTICIES];

    FillVerticies(VerticiesList);
    FillMatrizAdj(VerticiesList, MatrizAdj);
    EncontraCaminhoCurto(MatrizAdj);
    //PrintMatriz(MatrizAdj);
    //PrintVector(VerticiesList);
    return 0;
}

void FillVerticies(VerticiesInfo VerticiesList[])
{

    FILE *file = fopen("config_hanoi.csv", "r");


    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo config_hanoi.csv\n");
    }
    else
    {

        int i = 0;

        char line[100];

        while (fgets(line, sizeof(line), file))
        {

            int NumVerticies, Pinos;
            char arestas_str[10];


            sscanf(line, "%d,%d,\"%9[^\"]\"\n", &NumVerticies, &Pinos, arestas_str);


            VerticiesList[i].NumVerticies = NumVerticies;
            VerticiesList[i].Pinos = Pinos;


            char *token = strtok(arestas_str, ",");
            int j = 0;


            while (token != NULL && j < 3)
            {
                VerticiesList[i].Arestas[j] = atoi(token);
                token = strtok(NULL, ",");
                j++;
            }


            while (j < 3)
            {
                VerticiesList[i].Arestas[j] = -1;
                j++;
            }

       
            i++;
        }


        fclose(file);
    }
}

void PrintVector(VerticiesInfo VerticiesList[])
{

    int i;


    for (i = 0; i < NUM_VERTICIES; i++)
    {

        printf("Vertice: %d\nPinos: %d\n", VerticiesList[i].NumVerticies, VerticiesList[i].Pinos);

        printf("Arestas: ");

        int j;

        j = 0;


        while (j < 3 && VerticiesList[i].Arestas[j] != -1)
        {
            printf("%d ", VerticiesList[i].Arestas[j]);
            j++;
        }


        printf("\n\n");
    }
}

void FillMatrizAdj(VerticiesInfo VerticiesList[], int matriz[][NUM_VERTICIES])
{
    int li, col;
    int ContArestas;

    for (li = 0; li < NUM_VERTICIES; li++)
    {
        for (col = 0; col < NUM_VERTICIES; col++)
        {
            ContArestas = 0;

            matriz[li][col] = 0;

            while (VerticiesList[li].Arestas[ContArestas] != -1 && ContArestas < 3)
            {
                if (VerticiesList[li].Arestas[ContArestas] - 1 == col)
                {
                    matriz[li][col] = 1;
                }

                ContArestas++;
            }
        }
    }
}

void PrintMatriz(int matriz[][NUM_VERTICIES])
{
    int i, j;

    for (i = 0; i < NUM_VERTICIES; i++)
    {
        for (j = 0; j < NUM_VERTICIES; j++){
            printf("%d ", matriz[i][j]);
            }
        printf("\n");
    }
}

/*
    Encontra o caminho mais curto em uma matriz de adjacencia, usando Dijkstra e Bellman-Ford
*/
void EncontraCaminhoCurto(int matriz[][NUM_VERTICIES])
{
    int startVerticies = 0;
    int endVerticies = NUM_VERTICIES - 1;

    clock_t startVerticies_time, end_time;
    double time;

    startVerticies_time = clock();
    Dijkstra(matriz, startVerticies, endVerticies);
    end_time = clock();

    time = (double)(end_time - startVerticies_time) / CLOCKS_PER_SEC;

    printf("Tempo gasto - Dijkstra: %lf ms\n", time * 1000);
    printf("\n");

    startVerticies_time = clock();
    BellmanFord(matriz, startVerticies, endVerticies);
    end_time = clock();

    time = (double)(end_time - startVerticies_time) / CLOCKS_PER_SEC;

    printf("Tempo gasto - Bellman: %lf ms\n", time * 1000);
}

/*
A função Dijkstra implementa o algoritmo de Dijkstra para encontrar o caminho mais curto entre
dois vértices em um grafo ponderado representado por uma matriz de adjacência.
*/
void Dijkstra(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies)
{
    int distancias[NUM_VERTICIES];
    int visitados[NUM_VERTICIES], i, count, v;

    for (i = 0; i < NUM_VERTICIES; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    distancias[startVerticies] = 0;

    for (count = 0; count < NUM_VERTICIES - 1; count++)
    {
        int u = -1;

        for (i = 0; i < NUM_VERTICIES; i++)
        {
            if (!visitados[i] && (u == -1 || distancias[i] < distancias[u]))
            {
                u = i;
            }
        }

        visitados[u] = 1;

        for (v = 0; v < NUM_VERTICIES; v++)
        {
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + matriz[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz[u][v];
            }
        }
    }

    printf("Menor caminho de %d para %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}

/*
A função BellmanFord implementa o algoritmo de Bellman-Ford para encontrar o caminho mais curto entre
dois vértices em um grafo ponderado representado por uma matriz de adjacência.
*/
void BellmanFord(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies)
{
    int distancias[NUM_VERTICIES], i, passo, u, v;
    
    for (i = 0; i < NUM_VERTICIES; i++)
    {
        distancias[i] = INT_MAX;
    }

    distancias[startVerticies] = 0;

    for (passo = 0; passo < NUM_VERTICIES - 1; passo++)
    {
        for (u = 0; u < NUM_VERTICIES; u++)
        {
            for (v = 0; v < NUM_VERTICIES; v++)
            {
                if (matriz[u][v] && distancias[u] != INT_MAX &&
                    distancias[u] + matriz[u][v] < distancias[v])
                {
                    distancias[v] = distancias[u] + matriz[u][v];

                }
            }
        }
    }
    
    printf("\nMenor caminho de %d para %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}


