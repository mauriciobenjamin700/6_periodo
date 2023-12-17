#include <stdio.h>
#include "src/menu.c"
#include "src/artista.c"

#define TAM_TITULO 50

int main(void)
{
    int opc = 1;

    int retorno;

    int id;
    char titulo[TAM_TITULO];
    int ano;

    RB_album *novo_album;

    RB_album *arvoreRB;

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
            printf("\n\nID DO ALBUM: ");
            setbuf(stdin,NULL);
            scanf("%d",&id);

            printf("\n\nTITULO DO ALBUM: ");
            setbuf(stdin,NULL);
            scanf("%s",titulo);

            printf("\n\nANO DO ALBUM: ");
            setbuf(stdin,NULL);
            scanf("%d",&ano);

            novo_album = cria_no_album(id,titulo,ano);

            retorno = insere_no_RB_album(&arvoreRB,novo_album);
            
            retornos(retorno);

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