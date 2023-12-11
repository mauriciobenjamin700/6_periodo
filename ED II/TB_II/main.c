#include "src/musica.c"
//#include "src/album.c"
//#include "src/artista.c"


int main(void)
{
    char busca[] = {'b'};
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

    if (buscar_musica(lista,busca))
    {
        printf("\nAchei");
    }
    else
        printf("\nFalhei");
    

    return 0;
}
