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

        
        insere_no_RB_album(&arvore,i,titulo,ano);
        

        printf("\nDeseja Continuar? [1][0]: ");
        setbuf(stdin,NULL);
        scanf("%d", &continuar);

    }
    mostrar_tudo_RB_album(arvore);    
}