#include <stdio.h>
#include "tad.c"

int main(void)
{
    struct Serie *s;
    int sinal;

    iniciarS(&s);

    sinal = cadastrarS(&s);
    sinal = cadastrarS(&s);

    printf("\nSinal: %d", sinal);

    mostrar_all_S(&s);

    free(s); 
    printf("\nliberei\n");

    return 0;
}