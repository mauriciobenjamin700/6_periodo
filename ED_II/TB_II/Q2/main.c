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
    Artista *ponteiro_artista;

    Arv_23_artista *arvore_artista;
    Arv_23_artista *no_artista;

    Album album;
    Album *ponteiro_album;

    Musica musica;
    Musica *ponteiro_musica;

    while (opc != 0)
    {
        opc = menu();

        switch (opc)
        {
        case -1:
            printf("\n\nFALHA NA RESPOSTA !!!");
            break;

        case 0:
            printf("\n\nSISTEMA ENCERRRANDO...\n\n");
            break;

        case 4:
            //mostrar_todos_nos_artista_ordenado(arvore_artista);
            break;

        case 11:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", nome_artista);

            printf("\n\nTIPO DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", tipo_artista);

            printf("\n\nESTILO DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", estilo_artista);

            preencher_artista(&artista, nome_artista, tipo_artista, estilo_artista);

            if (buscar_artista(arvore_artista, nome_artista) == NULL)
            {
                arvore_artista = inserir_artista_arv23(arvore_artista, artista);
                printf("\nCADASTRO REALIZADO COM SUCESSO!");
            }
            else
                printf("\nJÁ ESTAVA CADASTRADO!");

            break;

        case 12:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
                mostrar_artista(ponteiro_artista);
            else
                printf("\nARTISTA NAO ENCONTRADO");

            break;

        case 13:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            no_artista = buscar_no_artista(arvore_artista, titulo);

            if (no_artista != NULL)
                if (pode_remover_artista(ponteiro_artista))
                {
                    arvore_artista = remover_artista_arv23(no_artista, titulo);
                    printf("\nREMOVIDO COM SUCESSO");
                }
                else
                    printf("\nPRIMEIRO DEVE REMOVER OS ALBUNS PARA DEPOIS REMOVER O ARTISTA");

            else
                printf("\nARTISTA NAO ENCONTRADO");
            break;

        case 21:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", titulo);

                printf("\n\nANO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%d", &ano);

                preencher_album(&album, titulo, ano);

                retorno = inserir_album_artista(ponteiro_artista, album);

                if (retorno == 1)
                    printf("\nCADASTRO REALIZADO COM SUCESSO");
                else
                    printf("\nJA EXISTE UM ALBUM COM ESSE TITULO CADASTRADO");
            }
            else
                printf("\nARTISTA NAO ENCONTRADO");

            break;

        case 22:

            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", titulo);

                ponteiro_album = buscar_album_artista(ponteiro_artista, titulo);

                if (ponteiro_album != NULL)
                    mostrar_album(ponteiro_album);

                else
                    printf("\nALBUM NAO ENCONTRADO!");
            }
            else
                printf("\nARTISTA NAO ENCONTRADO");

            break;

        case 23:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", titulo);

                ponteiro_album = buscar_album_artista(ponteiro_artista, titulo);

                if (ponteiro_album != NULL)
                {
                    if (pode_remover_album(ponteiro_album))
                    {
                        remover_album_artista(ponteiro_artista,titulo);
                        printf("\nALBUM REMOVIDO COM SUCESSO");
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
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", titulo);

                ponteiro_album = buscar_album_artista(ponteiro_artista, titulo);

                if (ponteiro_album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", titulo);

                    printf("\n\nDURACAO DA MUSICA: ");
                    setbuf(stdin, NULL);
                    scanf("%f", &duracao);

                    preencher_musica(&musica, titulo, duracao);

                    retorno = inserir_musica_album(ponteiro_album,musica);

                    if (retorno == 1)
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
                printf("\nARTISTA NAO ENCONTRADO");

            break;

        case 32:
            printf("\n\nNOME DO ARTISTA: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]", titulo);

                ponteiro_album = buscar_album_artista(ponteiro_artista, titulo);

                if (ponteiro_album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", titulo);

                    ponteiro_musica = buscar_musica_album(ponteiro_album, titulo);

                    if (ponteiro_musica != NULL)
                        mostrar_musica(ponteiro_musica);
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
            setbuf(stdin, NULL);
            scanf("%[^\n]", titulo);

            ponteiro_artista = buscar_artista(arvore_artista, titulo);

            if (ponteiro_artista != NULL)
            {
                printf("\n\nTITULO DO ALBUM: ");
                setbuf(stdin, NULL);
                scanf("%s", titulo);

                ponteiro_album = buscar_album_artista(ponteiro_artista, titulo);

                if (ponteiro_album != NULL)
                {
                    printf("\n\nTITULO DA MUSICA: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]", titulo);

                    retorno = remover_musica_album(ponteiro_album,titulo);

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
            printf("\nOPCAO INVALIDA!!!");
            break;
        }
    }
    return 0;
}