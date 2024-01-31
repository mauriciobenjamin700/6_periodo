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

    // Entrada do número de vértices no grafo
    printf("Numero de vertices: ");
    scanf("%d", &numVertex);

    grafo.numVertex = numVertex;

    // Inicialização da matriz de arestas com confiabilidade -1 para todos os pares de vértices
    for (i = 0; i < numVertex; i++)
    {
        for (j = 0; j < numVertex; j++)
        {
            grafo.arestas[i][j].confiabilidade = -1;
        }
    }

    // Entrada do número de arestas no grafo
    printf("Numero de arestas: ");
    scanf("%d", &numArestas);

    // Entrada das informações sobre as arestas, incluindo vértices e confiabilidade
    for (i = 0; i < numArestas; i++)
    {
        int u, v;
        float confiabilidade;

        printf("aresta %d (u v confiabilidade): ", i + 1);
        scanf("%d %d %f", &u, &v, &confiabilidade);

        grafo.arestas[u][v].confiabilidade = confiabilidade;
    }

    int verticeInicial, verticeFinal;

    // Entrada do vértice inicial
    printf("vertice inicial: ");
    scanf("%d", &verticeInicial);

    // Entrada do vértice final
    printf("vertice final: ");
    scanf("%d", &verticeFinal);

    float dist[MAX_VERTEX];
    int verticeAnterior[MAX_VERTEX];

    // Chamada do algoritmo de Dijkstra para calcular o caminho mais curto
    dijkstra(&grafo, verticeInicial, dist, verticeAnterior);

    // Saída condicional dependendo da existência de um caminho confiável
    if (dist[verticeFinal] > -1e8)
    {
        // Impressão do caminho mais confiável e sua confiabilidade associada
        printf("Caminho mais confiavel de %d para %d: ", verticeInicial, verticeFinal);
        imprimirCaminho(verticeAnterior, verticeFinal);
        printf("\n");
        printf("Confiabilidade: %.4f\n", exp(dist[verticeFinal]));
    }
    else
    {
        // Indicação de que não há um caminho confiável
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
    float minimo = INF;  // Inicializa uma variável para armazenar o valor mínimo, inicializado com um valor infinito
    int v, indiceMinimo = -1;  // Variáveis para iterar pelos vértices e armazenar o índice do vértice com a menor distância

    // Itera sobre todos os vértices no grafo
    for (v = 0; v < numVertex; v++)
    {
        // Verifica se o vértice não foi visitado e se a distância associada a ele é menor que o mínimo atual
        if (!visitados[v] && dist[v] >= minimo)
        {
            minimo = dist[v];  // Atualiza o valor mínimo
            indiceMinimo = v;  // Atualiza o índice do vértice com a menor distância
        }
    }

    return indiceMinimo;  // Retorna o índice do vértice com a menor distância
}

/*
Essa função implementa o algoritmo de Dijkstra para encontrar o caminho mais curto em 
um grafo ponderado dirigido com pesos representados pela confiabilidade das arestas. 
*/
void dijkstra(Grafo *grafo, int verticeInicial, float dist[], int verticeAnterior[])
{
    bool visitados[MAX_VERTEX] = {false};
    int i, count, v;

    // Inicialização das distâncias e vértices anteriores
    for (i = 0; i < grafo->numVertex; i++)
    {
        dist[i] = -1e9;  // Inicializa as distâncias com um valor muito pequeno (representando -∞)
        verticeAnterior[i] = -1;  // Inicializa os vértices anteriores como -1
    }

    dist[verticeInicial] = 0;  // A distância do vértice inicial para ele mesmo é 0

    // Iteração principal
    for (count = 0; count < grafo->numVertex - 1; count++)
    {
        // Encontra o vértice com a menor distância não visitado
        int u = verticeComMenorDistancia(dist, visitados, grafo->numVertex);

        visitados[u] = true;  // Marca o vértice como visitado

        // Atualiza as distâncias para todos os vértices adjacentes ao vértice atual
        for (v = 0; v < grafo->numVertex; v++)
        {
            float confiabilidade = grafo->arestas[u][v].confiabilidade;

            // Verifica se o vértice não foi visitado, a confiabilidade é válida e
            // a distância até o vértice atual somada ao logaritmo da confiabilidade
            // é maior que a distância atual do vértice destino
            if (!visitados[v] && confiabilidade >= 0 && dist[u] + log(confiabilidade) > dist[v])
            {
                // Atualiza a distância e o vértice anterior
                dist[v] = dist[u] + log(confiabilidade);
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
    // Verifica se o vértice tem um vértice anterior associado
    if (verticeAnterior[vertice] != -1)
    {
        // Chama recursivamente a função para o vértice anterior
        imprimirCaminho(verticeAnterior, verticeAnterior[vertice]);
        
        // Imprime a seta indicando a direção do caminho
        printf(" -> ");
    }

    // Imprime o número do vértice atual
    printf("%d", vertice);
}
