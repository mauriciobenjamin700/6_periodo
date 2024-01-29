#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Estrutura para armazenar pares chave-valor
struct KeyValue
{
    char key[50];
    int value;
    struct KeyValue *next;
};

// Estrutura da tabela hash
struct HashTable
{
    struct KeyValue *table[TABLE_SIZE];
};

// Função de hash simples (pode ser melhorada para casos reais)
int hashFunction(const char *key)
{
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

// Inicializa a tabela hash
struct HashTable *initializeHashTable()
{
    struct HashTable *hashTable = (struct HashTable *)malloc(sizeof(struct HashTable));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Insere um par chave-valor na tabela hash
void insert(struct HashTable *hashTable, const char *key, int value)
{
    int index = hashFunction(key);

    // Cria um novo par chave-valor
    struct KeyValue *newPair = (struct KeyValue *)malloc(sizeof(struct KeyValue));
    strcpy(newPair->key, key);
    newPair->value = value;

    // Verifica se a posição na tabela está vazia
    if (hashTable->table[index] == NULL)
    {
        hashTable->table[index] = newPair;
    }
    else
    {
        // Lida com colisões utilizando encadeamento
        newPair->next = hashTable->table[index];
        hashTable->table[index] = newPair;
    }
}

// Busca um valor na tabela hash a partir da chave
int search(struct HashTable *hashTable, const char *key)
{
    int index = hashFunction(key);
    struct KeyValue *current = hashTable->table[index];

    // Percorre a lista encadeada na posição da tabela
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }

    // Retorna um valor padrão se a chave não for encontrada
    return -1;
}

int main()
{
    struct HashTable *hashTable = initializeHashTable();

    // Exemplo de inserção
    insert(hashTable, "um", 1);
    insert(hashTable, "dois", 2);
    insert(hashTable, "três", 3);

    // Exemplo de busca
    printf("Valor para chave 'dois': %d\n", search(hashTable, "dois"));
    printf("Valor para chave 'quatro': %d\n", search(hashTable, "quatro"));

    return 0;
}
