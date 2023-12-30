#include "artista.c"

int main(void)
{
    Arv_23_artista *arvore_artistas = NULL;
    Artista artista;
    char dado[NOME];


    int opc = 1;
    
    while(opc)
    {
        printf("\nPreencha os dados do artista:\n");
        printf("\n\tNOME: ");
        setbuf(stdin,NULL);
        scanf("%[^\n]", dado);

        
        preencher_artista(&artista,dado,dado,dado);


        if (inserir_artista_arv23(&arvore_artistas,artista)==1)
            printf("\n\nINSERIDO COM SUCESSO");
        else
            printf("\n\nALGUMA FALHA ACONTECEU");


        printf("\n\nARVORE DE ARTISTAS A BAIXO \n");
        mostrar_arv_artistas(arvore_artistas);

        printf("\n\nContinuar: [1][0]\n");
        setbuf(stdin,NULL);
        scanf("%d", &opc);
    }

    return 0;
}