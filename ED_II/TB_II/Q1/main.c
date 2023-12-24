#include "src/menu.c"
#include "src/sistema.c"


int main(void)
{
    int opc = 1;

    int retorno;
    char titulo[TAM_TITULO];
    int ano;
    float duracao;

    char nome_artista[NOME];
    char tipo_artista[TIPO];
    char estilo_artista[ESTILO];

    Artista novo_artista;
    RB_artista *no_artista;
    RB_artista *arvore_artista;
    RB_album *album;
    Musica musica;
    Lista_musicas *no_musica;


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
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
                mostrar_artista(no_artista->artista);
            else
                printf("\nFALHA AO ENCONTRAR O ARTISTA");

            break;

        case 13:
            break;

        case 21:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",titulo);

                printf("\n\nANO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%d",&ano);

                album = cria_no_album(titulo,ano);

                retorno = (cadastrar_album_artista(no_artista, album));
                
                if(retorno == 1)
                {
                    printf("\nCadastro realizado com sucesso");
                    
                }
            }
            else
                printf("\nFALHA AO ENCONTRAR O ARTISTA");

            break;
        
        case 22:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",titulo);


                album = buscar_album_artista(no_artista,titulo);

                
                
                if(album != NULL)
                    mostrar_no_RB_album(album);
                    
                else
                    printf("\nALBUM NAO ENCONTRADO!");
            }
            else
                printf("\nFALHA AO ENCONTRAR O ARTISTA");

            break;

        case 23:
            break;

        case 31:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",titulo);


                album = buscar_album_artista(no_artista,titulo);

                
                
                if(album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%[^\n]",titulo);

                    printf("\n\nDURACAO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%f",&duracao);

                    preencher_musica(&musica,titulo,duracao);

                    retorno = adiciona_musica_no_album(album,&musica);

                    if (retorno==1)
                        printf("\n\nMUSICA CADASTRADA COM SUCESSO!");
                    
                    else if (retorno == 0)
                        printf("\n\nMUSICA JA ESTAVA CADASTRADA");

                    else
                        printf("\n\nFALHA NO CADASTRADO!");
                        
                }
                    
                else
                    printf("\nALBUM NAO ENCONTRADO!");
            }
            else
                printf("\nFALHA AO ENCONTRAR O ARTISTA");

            break;
        
        case 32:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%s",titulo);


                album = buscar_album_artista(no_artista,titulo);

                
                
                if(album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%[^\n]",titulo);

                    no_musica = buscar_musica_no_album(album,titulo);

                    if (no_musica != NULL)
                        mostrar_no_musica(no_musica);
                    else
                        printf("\n\nMUSICA NAO ENCONTRADA");

                }
                else
                    printf("\n\nALBUM NAO ENCONTRADO");
            }
            else
                printf("\n\nARTISTA NAO ENCONTRADO");

            break;

        case 33:
            break;

        default:
            break;
        }
    }
    

    return 0;
}