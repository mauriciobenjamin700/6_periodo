#include <stdio.h>

// Recursividade com Pendencia
void func(int num,int vetor[],int divisor,int *idx)
{
    //Validando se o número é valido (maior que 0) e o divisor é valido (divisor menor que o número) 
    if(num > 0 && divisor < num)
    {
        //validando se o divisor consegue dividir adequadamente o número
        if(num % divisor == 0)
        {
            //Adicionando ao vetor os números divisóres válidos
            vetor[*idx] = divisor;
            //incrementando o indice quando um valor for adicionado
            (*idx) ++;
        }
        //ativando a recursão enquanto existir um dívisor válido
        func(num,vetor,divisor+1,idx);
    }
}


int main(void)
{
    int num = 25;
    int divisor = 1;
    int vetor[100];
    int idx = 0;
    int i;

    func(num,vetor,divisor,&idx);

    printf("Os divisores de %d sao: ", num);

    for(i=0;i<idx;i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}