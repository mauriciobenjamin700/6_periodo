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

//Acessa o CSV com os dados e coloca no grafo de forma correta preenchendo todas as linhas do grafo (matriz)
void FillVerticies(VerticiesInfo VerticiesList[]);

void PrintVector(VerticiesInfo VerticiesList[]);

void FillMatrizAdj(VerticiesInfo VerticiesList[], int matriz[][NUM_VERTICIES]);
void PrintMatriz(int matriz[][NUM_VERTICIES]);
void EncontraCaminhoCurto(int matriz[][NUM_VERTICIES]);

void Dijkstra(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies);
void BellmanFord(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies);

int main()
{
    //cada vertice é uma linha do CSV (logo é uma possibilidade do grafo)
    VerticiesInfo VerticiesList[NUM_VERTICIES];
    int MatrizAdj[NUM_VERTICIES][NUM_VERTICIES];

    FillVerticies(VerticiesList);
    FillMatrizAdj(VerticiesList, MatrizAdj);
    EncontraCaminhoCurto(MatrizAdj);
    // PrintMatriz(MatrizAdj);
    // PrintVector(VerticiesList);
    return 0;
}

/*

*/
void FillVerticies(VerticiesInfo VerticiesList[])
{
    // Abre o arquivo "config_hanoi.csv" para leitura
    FILE *file = fopen("config_hanoi.csv", "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo config_hanoi.csv\n");
    }
    else
    {
        // Inicializa um contador i para percorrer a lista de vértices
        int i = 0;

        // Declara uma string chamada line para armazenar cada linha do arquivo
        char line[100];

        // Loop enquanto houver linhas para ler no arquivo
        while (fgets(line, sizeof(line), file))
        {
            // Declara variáveis para armazenar informações de cada linha
            int NumVerticies, Pinos;
            char arestas_str[10];

            // Usa sscanf para extrair valores da linha formatada como CSV
            sscanf(line, "%d,%d,\"%9[^\"]\"\n", &NumVerticies, &Pinos, arestas_str);

            // Preenche a estrutura VerticiesInfo com as informações extraídas
            VerticiesList[i].NumVerticies = NumVerticies;
            VerticiesList[i].Pinos = Pinos;

            // Usa strtok para dividir a string de arestas em tokens usando ","
            char *token = strtok(arestas_str, ",");
            int j = 0;

            // Preenche o array de arestas na estrutura VerticiesInfo
            while (token != NULL && j < 3)
            {
                VerticiesList[i].Arestas[j] = atoi(token);
                token = strtok(NULL, ",");
                j++;
            }

            // Preenche o restante do array de arestas com -1 se necessário
            while (j < 3)
            {
                VerticiesList[i].Arestas[j] = -1;
                j++;
            }

            // Incrementa o contador i para avançar para a próxima estrutura na lista
            i++;
        }

        // Fecha o arquivo após a leitura
        fclose(file);
    }
}

void PrintVector(VerticiesInfo VerticiesList[])
{

    int i;

    // Loop através de cada elemento na lista de vértices
    for (i = 0; i < NUM_VERTICIES; i++)
    {
        // Imprime informações sobre o vértice (Número de vértices e Pinos) (cada linha da matriz)
        printf("Vertice: %d\nPinos: %d\n", VerticiesList[i].NumVerticies, VerticiesList[i].Pinos);

        // Imprime informações sobre as arestas
        printf("Arestas: ");

        int j;

        // Inicializa a variável de controle do loop interno
        j = 0;

        // Loop para imprimir as arestas (até 3 arestas ou até encontrar -1)
        while (j < 3 && VerticiesList[i].Arestas[j] != -1)
        {
            printf("%d ", VerticiesList[i].Arestas[j]);
            j++;
        }

        // Imprime uma nova linha para formatar a saída
        printf("\n\n");
    }
}

void FillMatrizAdj(VerticiesInfo VerticiesList[], int matriz[][NUM_VERTICIES])
{
    // Declaração de variáveis de controle do loop
    int li, col;
    int ContArestas;

    // Loop para percorrer cada linha da matriz (cada aresta)
    for (li = 0; li < NUM_VERTICIES; li++)
    {
        // Loop para percorrer cada coluna da matriz (cada vértice)
        for (col = 0; col < NUM_VERTICIES; col++)
        {
            // Inicializa o contador de arestas
            ContArestas = 0;

            // Inicializa a célula da matriz como 0 (sem aresta)
            matriz[li][col] = 0;

            // Loop para verificar as arestas conectadas ao vértice
            while (VerticiesList[li].Arestas[ContArestas] != -1 && ContArestas < 3)
            {
                // Verifica se a aresta liga o vértice atual (li) ao vértice na coluna atual (col)
                if (VerticiesList[li].Arestas[ContArestas] - 1 == col)
                {
                    // Se sim, atualiza a célula da matriz para 1 (indicando a presença da aresta)
                    matriz[li][col] = 1;
                }

                // Incrementa o contador de arestas
                ContArestas++;
            }
        }
    }
}

// percorre cada linha e cada coluna da matriz para imprimir seu conteúdo formatadamente
void PrintMatriz(int matriz[][NUM_VERTICIES])
{
    int i, j;

    for (i = 0; i < NUM_VERTICIES; i++)
    {
        for (j = 0; j < NUM_VERTICIES; j++)
            printf("%d ", matriz[i][j]);

                printf("\n");
    }
}

/*
    Encontra o caminho mais curto em uma matriz de adjacencia, usando Dijkstra e Bellman-Ford
*/
void EncontraCaminhoCurto(int matriz[][NUM_VERTICIES])
{
    // Define o vértice de início como 0 e o vértice de destino como NUM_VERTICIES - 1
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

    // Inicia a contagem do tempo para o algoritmo de Bellman-Ford
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
    // Arrays para armazenar distâncias mínimas e status de visitação dos vértices
    int distancias[NUM_VERTICIES];
    int visitados[NUM_VERTICIES], i, count, v;

    // Inicializa as distâncias como infinito e marca todos os vértices como não visitados
    for (i = 0; i < NUM_VERTICIES; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
    }

    // Define a distância do vértice de início como 0
    distancias[startVerticies] = 0;

    // Loop principal para encontrar o caminho mais curto
    for (count = 0; count < NUM_VERTICIES - 1; count++)
    {
        // Encontra o vértice com a menor distância não visitado
        int u = -1;

        for (i = 0; i < NUM_VERTICIES; i++)
        {
            if (!visitados[i] && (u == -1 || distancias[i] < distancias[u]))
            {
                u = i;
            }
        }

        // Marca o vértice encontrado como visitado
        visitados[u] = 1;

        // Atualiza as distâncias dos vértices adjacentes ao vértice atual
        for (v = 0; v < NUM_VERTICIES; v++)
        {
            if (!visitados[v] && matriz[u][v] && distancias[u] != INT_MAX &&
                distancias[u] + matriz[u][v] < distancias[v])
            {
                distancias[v] = distancias[u] + matriz[u][v];
            }
        }
    }

    // Imprime a menor distância do vértice de início ao vértice de destino
    printf("Menor caminho de %d para %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}

/*
A função BellmanFord implementa o algoritmo de Bellman-Ford para encontrar o caminho mais curto entre
dois vértices em um grafo ponderado representado por uma matriz de adjacência.
*/
void BellmanFord(int matriz[][NUM_VERTICIES], int startVerticies, int endVerticies)
{
    // Array para armazenar distâncias mínimas
    int distancias[NUM_VERTICIES], i, passo, u, v;

    // Inicializa as distâncias como infinito
    for (i = 0; i < NUM_VERTICIES; i++)
    {
        distancias[i] = INT_MAX;
    }

    // Define a distância do vértice de início como 0
    distancias[startVerticies] = 0;

    // Loop principal para relaxamento de arestas
    for (passo = 0; passo < NUM_VERTICIES - 1; passo++)
    {
        // Loop para percorrer todas as arestas do grafo
        for (u = 0; u < NUM_VERTICIES; u++)
        {
            for (v = 0; v < NUM_VERTICIES; v++)
            {
                // Relaxa a aresta se uma distância menor for encontrada
                if (matriz[u][v] && distancias[u] != INT_MAX &&
                    distancias[u] + matriz[u][v] < distancias[v])
                {
                    distancias[v] = distancias[u] + matriz[u][v];
                }
            }
        }
    }

    // Imprime a menor distância do vértice de início ao vértice de destino
    printf("Menor caminho de %d para %d: %d\n", startVerticies, endVerticies, distancias[endVerticies]);
}
