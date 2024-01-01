#include "artista.c"

int main(void)
{
    Arv_23_artista *arvore_artistas = NULL;
    Artista artista;
    Arv_23_artista *no;
    char dado[NOME];


    int opc = 1;
    
    while(opc)
    {
        printf("\nPreencha os dados do artista:\n");
        printf("\n\tNOME: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]", dado);

        
        preencher_artista(&artista,dado,dado,dado);


        arvore_artistas =  inserir_artista_arv23(arvore_artistas,artista);


        printf("\n\nARVORE DE ARTISTAS A BAIXO \n");
        mostrar_arv_artistas(arvore_artistas);

        printf("\n\nContinuar: [1][0]\n");
        setbuf(stdin,NULL);
        scanf("%d", &opc);
    }

    opc = 1;
    
    while(opc)
    {
        printf("\nQuem vai remover:\n");
        printf("\n\tNOME: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]", dado);

        
        no = buscar_no_artista(arvore_artistas,dado);

        if(no!=NULL)
        {
            arvore_artistas = remover_artista_arv23(no,dado);
            printf("\nRemovido com sucesso!");
        }
        else
            printf("\nARTISTA NAO CADASTRADO");

        printf("\n\nARVORE DE ARTISTAS A BAIXO \n");
        mostrar_arv_artistas(arvore_artistas);

        printf("\n\nContinuar: [1][0]\n");
        setbuf(stdin,NULL);
        scanf("%d", &opc);
    }

    return 0;
}