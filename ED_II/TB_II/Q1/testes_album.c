#include "src/album.c"
# define TAM_TITULO 50


int main(void)
{
    Album album;
    char titulo[TAM_TITULO];
    int ano;
    int continuar = 1;
    Musica musica;

    while (continuar)
    {
        printf("\n\n");
        printf("Titulo do Album: ");
        setbuf(stdin,NULL);
        scanf("%s", titulo);

        printf("Ano do Album: ");
        setbuf(stdin,NULL);
        scanf("%d", &ano);


        preencher_album(&album,titulo,ano);

        printf("Titulo da Musica: ");
        setbuf(stdin,NULL);
        scanf("%s", titulo);
        
        preencher_musica(&musica,titulo,1);

        adiciona_musica_album(&album,&musica);

        printf("Titulo da Musica: ");
        setbuf(stdin,NULL);
        scanf("%s", titulo);
        
        preencher_musica(&musica,titulo,1);

        adiciona_musica_album(&album,&musica);

        mostrar_album(&album);

        printf("\nDeseja Continuar? [1][0]: ");
        setbuf(stdin,NULL);
        scanf("%d", &continuar);

    }
    
}