#include <stdio.h>

void altera1(int **p, int *a)
{
    **p = *a;
    *a = *a + 100;
}

void altera2(int **p, int *b)
{
    *p = b;
    *b = *b + 50;
}

int main()
{
    int x,y,z, *px, *py, *pz;

    x = 10;
    y = x + 20;

    px = &x;
    py = &y;

    z = *py + 50;

    pz = &z;

    printf("x = %d, End. x = %p, px = %p\n",x,&x,px);
    printf("y = %d, End. y = %p, py = %p\n",y,&y,py);
    printf("z = %d, End. z = %p, pz = %p\n",z,&z,pz);

    altera1(&px, &y);

    printf("\n\nx = %d, End. x = %p, px = %p\n",x,&x,px);
    printf("y = %d, End. y = %p, py = %p\n",y,&y,py);
    printf("z = %d, End. z = %p, pz = %p\n",z,&z,pz);

    altera2(&pz,&x);

    printf("\n\nx = %d, End. x = %p, px = %p\n",x,&x,px);
    printf("y = %d, End. y = %p, py = %p\n",y,&y,py);
    printf("z = %d, End. z = %p, pz = %p\n",z,&z,pz);

    return 0;
}

/*

Saida:

    x = 10, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 30, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0fc


    x = 30, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 130, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0fc


    x = 80, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 130, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0f4


a) Qual a diferença entre px e x?
    R: X é uma variavel que guarda um valor inteiro, já PX é uma váriavel que 
    guarda o endereço de uma váriavel inteira.

b) qual a diferença entre px, py e pz?
    R: Ambas são ponteiros, entretanto apontam para endereços diferentes.

c) Quais são os valores impressos pelos primeiros três prints?
    R:
    x = 10, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 30, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0fc

d) O que muda em relação a primeira sequencia de prints para a segunda:
    Primeira:
    x = 10, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 30, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0fc
    Segunda:
    x = 30, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 130, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0fc

    R:O conteúdo de x é atualzado pelo de y e y é somado com 100 para se tornar 130.

e) Quais os valores impressos pela terceira sequência de printfs?
    x = 80, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 130, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0f4

f) O que muda da segunda sequência para a terceira sequência de printf?
    Segunda sequência:
    x = 30, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 130, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0fc

    Terceira Sequência:
    x = 80, End. x = 0x7ffcd31fe0f4, px = 0x7ffcd31fe0f4
    y = 130, End. y = 0x7ffcd31fe0f8, py = 0x7ffcd31fe0f8
    z = 80, End. z = 0x7ffcd31fe0fc, pz = 0x7ffcd31fe0f4

    o valor de X é atualizado para 80 e o ponteiro pz passa a apontar para o endereço de x.

g) Explique a diferença entre altera1 e altera2.
    Em altera1 modificamos apenas o conteúdo das váriaveis:
        Usando PX podemos alterar o valor de X de 10 para 30
        e acrescentamos 100 ao valor de de y o tornando 130.
    Já em altera2 modificamos o endereço das váriaveis
        O ponteiro que apontava para Z passou a apontar para x
        o valor de x foi somado com 50 o tornando 80.
*/