#include <stdio.h>
#include "tad.c"

int menu()
{
    int opc;
    printf("\nBEM VINDO A BIBLIOTECA DE SERIES!\n\t1 - Cadastrar Serie\n\t2 - Buscar Serie\n\t3 - Mostrar todas as Series\n\t4 - Encerrar o sistema!\nSua resposta: ");
    scanf("%d", &opc);

    return opc;
}

int main(void)
{
    struct Serie *s;
    int opc = 0;
    iniciarS(&s);

    while (opc!=4)
    {
        opc = menu();
        if(opc==1)
        {
            cadastrarS(&s);
        }       
        else if(opc == 2)
        {
            printf("\nFarei a função de busca ainda");
        }
        else if(opc == 3)
        {
            mostrar_all_S(&s);
        }
        else if(opc == 2)
        {
            liberar_all_S(&s);
            printf("\nSistema encerrado!");
        }
    }
    return 0;
}