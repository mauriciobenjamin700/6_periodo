#include <stdio.h>

int menu_serie()
{
    int opc;
    
    printf("\n----------MENU SERIE---------\n");
    printf("| 1 - Cadastrar \n| 2 - Buscar \n| 3 - Editar\n| 4 - Voltar\n");
    printf("-----------------------------\n");
    printf("\nSua resposta: ");
    
    setbuf(stdin, NULL);
    scanf("%d", &opc);
    printf("\n-----------------------------\n");

    return opc;
}

int menu_temporada()
{
    int opc;
    
    printf("\n--------MENU TEMPORADA-------\n");
    printf("| 1 - Cadastrar \n| 2 - Buscar \n| 3 - Editar\n| 4 - Voltar\n");
    printf("-----------------------------\n");
    printf("\nSua resposta: ");
    
    setbuf(stdin, NULL);
    scanf("%d", &opc);
    printf("\n-----------------------------\n");

    return opc;
}

/*
int menu_participante()
{
    int opc;
    
    printf("\n-------MENU PARTICIPANTE-----\n");
    printf("| 1 - Cadastrar \n| 2 - Buscar \n| 3 - Editar\n| 4 - Voltar\n");
    printf("-----------------------------\n");
    printf("\nSua resposta: ");
    
    setbuf(stdin, NULL);
    scanf("%d", &opc);
    printf("\n-----------------------------\n");

    return opc;
}
*/
int questoes()
{
    int opc;
    
    printf("\n-------MENU IMPRESSAO-----\n");
    printf("| 1 - Imprimir em ordem pelo código da série: o título, o número de temporadas \n| 2 - Imprimir os dados de todas as temporadas de uma série, cujo o usuário informe o código da série. \n| 3 - Imprimir  todos  os  personagens  de  uma  determinada  temporada  de  uma  dada  série,  cujo  o  usuário informe o código da série e o número da temporada\n| 4 - Imprimir  o  nome  de  todos  os  artistas  que  interpretaram  um  determinado  personagem  em  todas  as temporadas de uma dada série, cujo o usuário informe o código da série.\n");
    printf("-----------------------------\n");
    printf("\nSua resposta: ");
    
    setbuf(stdin, NULL);
    scanf("%d", &opc);
    printf("\n-----------------------------\n");

    return opc;

}

int menu()
{
    int opc;

    printf("\n----------MENU GERAL---------\n");
    printf("| 1 - Series \n| 2 - Temporadas \n| 3 - Impressoes\n| 0 - Sair\n");
    printf("-----------------------------\n");
    printf("\nSua resposta: ");
    
    setbuf(stdin, NULL);
    scanf("%d", &opc);
    printf("\n-----------------------------\n");


    if      (opc == 1) opc = 10 + menu_serie();
    else if (opc == 2) opc = 20 + menu_temporada();
    //else if (opc == 3) opc = 30 + menu_participante();
    else if (opc == 3) opc = 30 + questoes();
    else opc = 4;

    return opc;
}

