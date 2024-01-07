#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode
{
    struct TrieNode *children[26]; 
    int isEndOfWord;  

} TrieNode;


struct TrieNode *createNode()
{   int i;
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;

    for (i = 0; i < 26; i++){
        node->children[i] = NULL;
    }
    return node;
}

void insereTrie(struct TrieNode **root, const char *word, int i, int tam)
{
    int index;
    index = word[i] - 'a';

    if (i < tam - 1)
    {
        if ((*root)->children[index] == NULL)
            (*root)->children[index] = createNode();

        insereTrie(&((*root)->children[index]), word, ++i, tam);
    }
    else
    {
        if ((*root)->children[index] == NULL)
            (*root)->children[index] = createNode();

        ((*root)->children[index])->isEndOfWord = 1;
    }
}
void buscarVarios(struct TrieNode *root, const char **word, int quantWords, int *words);
int buscar(struct TrieNode *root, const char *word)
{
    struct TrieNode *currentNode = root;
    int achou = 0, tam, i, index;

    tam = strlen(word);

    for (i = 0; (i < tam && !achou); i++)
    {
        index = word[i] - 'a';

        if (currentNode->children[index] != NULL)
        {
            if ((currentNode->children[index])->isEndOfWord == 1 && i == tam - 1)
                achou = 1;
            else
                currentNode = currentNode->children[index];
        }
    }
    return achou;
}

int main()
{
    TrieNode * root;
    int i;

    root = createNode();
    // Inserindo algumas palavras na Trie
    insereTrie(&root, "apple",0,strlen("apple"));
    insereTrie(&root, "banana",0,strlen("banana"));
    insereTrie(&root, "app",0, strlen("app"));
    
    printf("Insercoes concluidas.\n");
    int words[] = {0,0};
    const char* palavras[] = {"apple", "banana"};
    buscarVarios(root,palavras,2,words);
    
    for(i = 0; i < 2;i++){
        if(words[i] == 1){
            printf("Palavra %d está cadastrada",i);
        }
    }

    getchar();

    return 0;
    
}

void buscarVarios(struct TrieNode *root, const char **word, int quantWords, int *words)
{
	struct TrieNode *currentNode = root;
	int achou = 0, tam, i, index;

	tam = strlen(*word);

	for (i = 0; (i < tam && !achou); i++)
	{
		index = (*word)[i] - 'a';

		if (currentNode->children[index] != NULL)
		{
			if ((currentNode->children[index])->isEndOfWord == 1 && i == tam - 1)
				achou = 1;
			else
				currentNode = currentNode->children[index];
		}
	}

	words[0] = achou;
	if (quantWords > 1)
	{
		buscarVarios(root,word+1,quantWords-1,words+1);
	}

}