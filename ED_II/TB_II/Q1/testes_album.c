#include "src/album.c"
# define TAM_TITULO 50


int main(void)
{
    //Album album;
    char titulo[TAM_TITULO];
    int ano;
    int continuar = 1;
    int i=0;
    //Musica musica;

    RB_album *arvore;

    while (continuar)
    {
        printf("\n\n");
        printf("Titulo do Album: ");
        setbuf(stdin,NULL);
        scanf("%s", titulo);

        printf("\nAno do Album: ");
        setbuf(stdin,NULL);
        scanf("%d", &ano);

        printf("\nID: ");
        setbuf(stdin,NULL);
        scanf("%d", &i);

        
        if (insere_no_RB_album(&arvore,cria_no_album(i,titulo,ano)) == -1)
            printf("\nErro ao cadastrar!");
        else printf("\nCadastrei");
        

        printf("\nDeseja Continuar? [1][0]: ");
        setbuf(stdin,NULL);
        scanf("%d", &continuar);

    }
    printf("\n--------------------------------------\n");
    //mostrar_tudo_RB_album(arvore);
    mostrar_album(&((buscar_no_RB_album(arvore,1))->album));
}