#include <stdio.h>
#include "src/menu.c"

int main(void)
{

    int opc = 1;


    while (opc != 0)
    {
        opc = menu();

        switch (opc)
        {
        case -1 :
            printf("\n\nFALHA NA RESPOSTA !!!");
            break;
        
        case 0:
            printf("\n\nSISTEMA ENCERRRANDO...");    
            break;

        case 11:
            break;
        
        case 12:
            break;

        case 13:
            break;

        case 21:
            break;
        
        case 22:
            break;

        case 23:
            break;

        case 31:
            break;
        
        case 32:
            break;

        case 33:
            break;

        default:
            break;
        }
    }
    

    return 0;
}