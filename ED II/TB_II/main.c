#include "src/musica.c"
//#include "src/album.c"
//#include "src/artista.c"
# define TAM_TITULO 50


int main(void)
{
    char busca[TAM_TITULO];
    Lista_musicas *lista = iniciar_no_lista();
    Musica *musica;
    char titulo[30];
    float duracao;

    int sinal = 1;

    while (sinal)
    {
        musica = criar_musica();
        printf("\n\nCadastre uma musica");
        printf("\nNome da musica: ");
        setbuf(stdin,NULL);
        scanf("%s",titulo);
        printf("\nDuracao: ");
        setbuf(stdin,NULL);
        scanf("%f",&duracao);
        preencher_musica(musica,titulo,duracao);
        
        if (adicionar_musica_ordenada(&lista,musica))
            printf("\n\nCadastrei com sucesso!");
        else
            printf("\nFalhei");
            
        
        printf("\n\nDeseja continuar? [1][0]\n");
        setbuf(stdin,NULL);
        scanf("%d",&sinal);
        
    }
    
    mostar_todas_musicas(lista);

    printf("\n\nDeseja remover qual musica: ");
    setbuf(stdin,NULL);
    scanf("%s", busca);

    if (remover_musica(&lista,busca))
    {
        printf("\nRemovi");
    }
    else
        printf("\nFalhei");
    
    mostar_todas_musicas(lista);
    printf("\n\nTotal de musicas: %d", contar_musicas(lista));

    remover_todas_musicas(&lista);

    mostar_todas_musicas(lista);

    printf("\n\nTotal de musicas: %d\n", contar_musicas(lista));

    return 0;
}
