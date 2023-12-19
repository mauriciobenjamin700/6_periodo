#include <stdio.h>
#include <ctype.h>

int strcasecmp_custom(const char *s1, const char *s2)
{
    while (*s1 && *s2 && tolower(*s1) == tolower(*s2))
    {
        s1++;
        s2++;
    }
    return tolower(*s1) - tolower(*s2);
}

// inserção
// se a esquerda da rubro negro é preta e a direita é vermelha, faz rotação simples pra esquerda, onde o vermelho fica preto, e o pai fica vermelho
// se o nó e vermelho e a esquerda dele é vermelho, então rotaciona o nó para a direita, a direita fica vermelha
// se a esquerda e a direita do nó é vermelho, troca a cor do nó e dos 2 filhos
