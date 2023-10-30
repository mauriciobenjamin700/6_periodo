#include <stdio.h>
#include "tad.c"

int main(void)
{
    struct Serie *s;
    int opc = 0;
    iniciarS(&s);
    int id_busca;

    printf("%i\n", cadastrarS(&s,geraId(&s)));
    printf("%i\n", cadastrarT(&(s->t),3));
    mostrar_all_T(&(s->t));
    return 0;
}