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

    Artista artista;
    RB_artista *no_artista;
    RB_artista *arvore_artista;
    RB_album *no_album;
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

            preencher_artista(&artista,nome_artista,tipo_artista,estilo_artista);
            no_artista =  cria_no_artista(VERMELHO,artista);

            if (no_artista != NULL)
            {
                retorno = insere_no_artista(&arvore_artista,no_artista);
                
                if(retorno==1)
                    printf("\nCADASTRO REALIZADO COM SUCESSO!");
                
                else
                    printf("\nJÁ ESTAVA CADASTRADO!");
            }
            else
                printf("\nSISTEMA SEM MEMORIA");
            

            break;
        
        case 12:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
                mostrar_artista(no_artista->artista);
            else
                printf("\nARTISTA NAO ENCONTRADO");


            break;

        case 13:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
                if(pode_remover_artista(no_artista))
                {
                    if (remove_no_artista_ARVRB(&arvore_artista,titulo))
                        printf("\nREMOVIDO COM SUCESSO");
                    else
                        printf("\nFALHA AO REMOVER");
                }
                else
                    printf("\nPRIMEIRO DEVE REMOVER OS ALBUNS PARA DEPOIS REMOVER O ARTISTA");
                
                
            else
                printf("\nARTISTA NAO ENCONTRADO");
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

                no_album = cria_no_album(titulo,ano);

                retorno = (cadastrar_album_artista(no_artista, no_album));
                
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

                no_album = buscar_album_artista(no_artista,titulo);
                
                if(no_album != NULL)
                    mostrar_no_RB_album(no_album);
                    
                else
                    printf("\nALBUM NAO ENCONTRADO!");
            }
            else
                printf("\nARTISTA NAO ENCONTRADO");

            break;

        case 23:
        printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%[^\n]",titulo);

                no_album = buscar_album_artista(no_artista,titulo);

                if(no_album != NULL)
                {
                    if(pode_remover_album(no_album))
                   {
                        //bug aqui free(): double free detected in tcache 2 Abortado (imagem do núcleo gravada)
                        retorno = remover_album_artista(no_artista,titulo);
                        if(retorno == 1)
                            printf("\nALBUM REMOVIDO COM SUCESSO");
                    
                        else
                            printf("\nALBUM NAO ENCONTRADO!");
                    }
                    else
                        printf("\nPARA REMOVER O ALBUM, PRIMEIRO REMOVA AS MUSICAS");
                }
                else
                    printf("\nALBUM NAO ENCONTRADO!");
            }
            else
                printf("\nARTISTA NAO ENCONTRADO");

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


                no_album = buscar_album_artista(no_artista,titulo);

                
                
                if(no_album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%[^\n]",titulo);

                    printf("\n\nDURACAO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%f",&duracao);

                    preencher_musica(&musica,titulo,duracao);

                    retorno = adiciona_musica_no_album(no_album,&musica);

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

                no_album = buscar_album_artista(no_artista,titulo);

                if(no_album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%[^\n]",titulo);

                    no_musica = buscar_musica_no_album(no_album,titulo);

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
        printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin,NULL);
            scanf("%[^\n]",titulo);

            no_artista = busca_no_artista(arvore_artista,titulo);

            if(no_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin,NULL);
                scanf("%s",titulo);

                no_album = buscar_album_artista(no_artista,titulo);

                if(no_album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin,NULL);
                    scanf("%[^\n]",titulo);

                    retorno = remover_musica_album(&(no_album->album),titulo);


                    if (retorno)
                        printf("\nMUSICA REMOVIDA COM SUCESSO!");

                    else
                        printf("\nFALHA AO REMOVER");

                }
                else
                    printf("\n\nALBUM NAO ENCONTRADO");
            }
            else
                printf("\n\nARTISTA NAO ENCONTRADO");

            break;

        default:
            break;
        }
    }
    

    return 0;
}