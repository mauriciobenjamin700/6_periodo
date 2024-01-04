#include <stdio.h>

int menu_artista()
{
    int opc;

    printf("\n\n----------ARTISTA----------\n");
    printf("| [1] - Cadastrar\n| [2] - Buscar\n| [3] - Remover\n| [4] - Remover Artista com todos os Albuns\n| [0] - Voltar");
    printf("\n\n----------ARTISTA----------\n");
    setbuf(stdin,NULL);
    printf("\nEscolha: ");
    scanf("%d", &opc);

    if(opc < 0 || opc > 4)
        opc = -1;

    return opc;

}

int menu_album()
{
    int opc;

    printf("\n\n----------ALBUM----------\n");
    printf("| [1] - Cadastrar\n| [2] - Buscar\n| [3] - Remover\n| [4] - Remover Album com todas as Musicas\n| [0] - Voltar");
    printf("\n\n----------ALBUM----------\n");
    setbuf(stdin,NULL);
    printf("\nEscolha: ");
    scanf("%d", &opc);

    if(opc < 0 || opc > 4)
        opc = -1;

    return opc;

}

int menu_musica()
{
    int opc;

    printf("\n\n----------MUSICA----------\n");
    printf("| [1] - Cadastrar\n| [2] - Buscar\n| [3] - Remover\n| [0] - Voltar");
    printf("\n\n----------MUSICA----------\n");
    setbuf(stdin,NULL);
    printf("\nEscolha: ");
    scanf("%d", &opc);

    if(opc < 0 || opc > 3)
        opc = -1;

    return opc;

}

int menu()
{
    int opc;

    printf("\n\n----------GERAL----------\n");
    printf("| [1] - Artista\n| [2] - Album\n| [3] - Musica\n| [4] - Visualizar ARV RB ARTISTA\n| [0] - Sair");
    printf("\n\n----------GERAL----------\n");
    setbuf(stdin,NULL);
    printf("\nEscolha: ");
    scanf("%d", &opc);

    if(opc < 0 || opc > 4)
        opc = -1;

    switch (opc)
    {
    case 1:
        opc = 10 + menu_artista();
        break;
    
    case 2:
        opc = 20 + menu_album();
        break;
    
    case 3:
        opc = 30 + menu_musica();
        break;

    default:
        break;
    }

    return opc;

}
