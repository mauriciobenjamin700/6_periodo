#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_VERTEX 100
#define INF -1e9

typedef struct
{
    int vertice;
    float confiabilidade;
} Aresta;

typedef struct
{
    Aresta arestas[MAX_VERTEX][MAX_VERTEX];
    int numVertex;
} Grafo;

int verticeComMenorDistancia(float dist[], bool visitados[], int numVertex);
void dijkstra(Grafo *grafo, int verticeInicial, float dist[], int verticeAnterior[]);
void imprimirCaminho(int verticeAnterior[], int vertice);

int main()
{
    Grafo grafo;
    int numVertex, numArestas, i, j;


    printf("Numero de vertices: ");
    scanf("%d", &numVertex);

    grafo.numVertex = numVertex;


    for (i = 0; i < numVertex; i++)
    {
        for (j = 0; j < numVertex; j++)
        {
            grafo.arestas[i][j].confiabilidade = -1;
        }
    }


    printf("Numero de arestas: ");
    scanf("%d", &numArestas);

    for (i = 0; i < numArestas; i++)
    {
        int u, v;
        float confiabilidade;

        printf("aresta %d (u v confiabilidade): ", i + 1);
        scanf("%d %d %f", &u, &v, &confiabilidade);

        grafo.arestas[u][v].confiabilidade = confiabilidade;
    }

    int verticeInicial, verticeFinal;


    printf("vertice inicial: ");
    scanf("%d", &verticeInicial);

    printf("vertice final: ");
    scanf("%d", &verticeFinal);

    float dist[MAX_VERTEX];
    int verticeAnterior[MAX_VERTEX];

    dijkstra(&grafo, verticeInicial, dist, verticeAnterior);

    if (dist[verticeFinal] > -1e8)
    {

        printf("Caminho mais confiavel de %d para %d: ", verticeInicial, verticeFinal);
        imprimirCaminho(verticeAnterior, verticeFinal);
        printf("\n");
        printf("Confiabilidade: %.4f\n", exp(dist[verticeFinal]));
    }
    else
    {

        printf("Nenhum caminho confiavel de %d para %d.\n", verticeInicial, verticeFinal);
    }

    return 0;
}
/*
Essa função em C procura por um vértice não visitado com a menor 
distância (ou valor associado) em um conjunto de vértices. 
*/
int verticeComMenorDistancia(float dist[], bool visitados[], int numVertex)
{
    float minimo = INF;  
    int v, indiceMinimo = -1;  

    
    for (v = 0; v < numVertex; v++)
    {

        if (!visitados[v] && dist[v] >= minimo)
        {
            minimo = dist[v]; 
            indiceMinimo = v; 
        }
    }
    return indiceMinimo; 
}

/*
Essa função implementa o algoritmo de Dijkstra para encontrar o caminho mais curto em 
um grafo ponderado dirigido com pesos representados pela confiabilidade das arestas. 
*/
void dijkstra(Grafo *grafo, int verticeInicial, float dist[], int verticeAnterior[])
{
    bool visitados[MAX_VERTEX] = {false};
    int i, count, v;

    
    for (i = 0; i < grafo->numVertex; i++)
    {
        dist[i] = -1e9;  
        verticeAnterior[i] = -1;  
    }

    dist[verticeInicial] = 0;  

    for (count = 0; count < grafo->numVertex - 1; count++)
    {
   
        int u = verticeComMenorDistancia(dist, visitados, grafo->numVertex);

        visitados[u] = true;  


        for (v = 0; v < grafo->numVertex; v++)
        {
            float confiabilidade = grafo->arestas[u][v].confiabilidade;


            if (!visitados[v] && confiabilidade >= 0 && dist[u] + log(confiabilidade) > dist[v])
            {

                dist[v] = dist[u] + log(confiabilidade);
                printf("%f\n",log(confiabilidade));
                verticeAnterior[v] = u;
            }
        }
    }
}

/*
Essa função é usada para imprimir o caminho de um vértice específico 
até o vértice inicial em um grafo, com base nas informações armazenadas no array verticeAnterior[]
*/
void imprimirCaminho(int verticeAnterior[], int vertice)
{
 
    if (verticeAnterior[vertice] != -1)
    {

        imprimirCaminho(verticeAnterior, verticeAnterior[vertice]);
        

        printf(" -> ");
    }


    printf("%d", vertice);
}
