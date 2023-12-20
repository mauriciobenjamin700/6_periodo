#include "src/menu.c"
#include "src/artista.c"


int main(void)
{
    int opc = 1;

    int retorno;

    char titulo[TAM_TITULO];
    int ano;

    char nome_artista[NOME];
    char tipo_artista[TIPO];
    char estilo_artista[ESTILO];



    Artista novo_artista;
    RB_artista *no_artista;
    RB_artista *arvore_artista;

    RB_album *novo_album;
    RB_album *arvore_album;

    while (opc != 0)
    {
        opc = menu();

        switch (opc)
        {
        case -1 :
            printf("\n\nFALHA NA RESPOSTA !!!");
            break;
        
        case 0:
            printf("\n\nSISTEMA ENCERRRANDO...\n\n");    
            break;

        case 11:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",nome_artista);

            printf("\n\nTIPO DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",tipo_artista);

            printf("\n\nESTILO DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",estilo_artista);

            preencher_artista(&novo_artista,nome_artista,tipo_artista,estilo_artista);
            no_artista =  cria_no_artista(VERMELHO,novo_artista);

            if (no_artista != NULL)
            {
                insere_no_artista(&arvore_artista,no_artista);
                printf("\nCadastrado com sucesso");
            }
                else
                printf("\n\nSem memoria para criar o novo Artista!!!");
            

            break;
        
        case 12:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%s",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\nArtista encontrado!");
                mostrar_artista(no_artista->artista);
            }
            else
                printf("\nFALHA AO ENCONTRAR O ARTISTA");

            break;

        case 13:
            break;

        case 21:

            printf("\n\nTITULO DO ALBUM: ");
            setbuf(stdin,NULL);
            scanf("%s",titulo);

            printf("\n\nANO DO ALBUM: ");
            setbuf(stdin,NULL);
            scanf("%d",&ano);

            novo_album = cria_no_album(titulo,ano);

            retorno = insere_no_RB_album(&arvore_album,novo_album);
            
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