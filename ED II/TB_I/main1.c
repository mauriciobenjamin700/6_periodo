#include <stdio.h>
#include "tad1.c"
#include "menu.c"
#define TITTEL 30

int main(void)
{
    Serie *s;
    int opc = 1;
    
    int id;
    int sinal = 0;
    Serie * serie;
    char titulo[TITTEL];

    if(iniciarS(&s))
    {
        while (opc!=4)
    {
        opc = menu();
        if(opc==11)
        { 
            id = geraId(&s);
            Serie* new;
            printf("\nTitulo da Serie: ");
            setbuf(stdin, NULL);
            scanf("%[^\n]",titulo);

            preencherS(&new, id,titulo);
            sinal = cadastrarS(&s, new);
            if(sinal) 
            {
                printf("\nCadastro realizado com sucesso!\n");
                mostrarS(new);
            }
            else printf("\nFalha no Cadastro");
        }       
        else if(opc == 12)
        {
            printf("\nInforme o código da serie que deseja buscar: ");
            scanf("%d", &id);
            serie =  buscarS(s,id);
            if (serie != NULL)
            {
                printf("\nSerie Encontrada!\n");
                mostrarS(serie);
                printf("\n----------------------------");
            }
            else printf("\nSerie nao encontrada\n");
        }
        else if(opc == 13)  printf("\nFuncinalidade ainda em desenvolvimento");
    
        else if(opc == 21)
        {
            printf("\nID da serie: ");
            setbuf(stdin,NULL);
            scanf("%d", &id);

            serie = buscarS(s,id);
            if (serie != NULL)
            {
                if (cadastrarT(&(s->t))) 
                {
                    printf("\nTemporada Adicionada com sucesso!");
                    serie->numTemp+=1;
                }
                
                else printf("\nFalha ao adicionar temporada");
            }
            else printf ("\nSerie nao encontrada!");
            
        }
        else if (opc == 22)
        {
            printf("\nID da serie: ");
            setbuf(stdin,NULL);
            scanf("%d", &id);

            serie = buscarS(s,id);
            if (serie != NULL)
            {
                mostrar_all_T(serie->t);
            }
            else printf("\nSerie nao encontrada!");
        }

        else if (opc == 23) printf("\nFuncionalidade em Desenvolvimento ainda!");

        else if (opc == 41) mostrar_all_S(&s);
        else if (opc == 42)
        {
            printf("\nID da serie: ");
            setbuf(stdin,NULL);
            scanf("%d", &id);

            serie = buscarS(s,id);
            if (serie != NULL)
            {
                mostrar_all_T(serie->t);
            }
            else printf("\nSerie nao encontrada!");
        }

        else if (opc == 43)
        {
            printf("\nID da serie: ");
            setbuf(stdin,NULL);
            scanf("%d", &id);

            serie = buscarS(s,id);
            if (serie != NULL)
            {
                mostrar_all_T(serie->t);

                printf("\nDeseja ver os personagens de qual temporada: ");
                setbuf(stdin,NULL);
                scanf("%d", &id);

                Temporada *t  = buscarT(serie->t,id);

                if(t != NULL)
                {
                    mostrar_all_P(t->lista);
                }
                else printf("\nTemporada Invalida");
            }
            else printf("\nSerie nao encontrada!");
            
        }
        else if (opc == 44)
        {
            printf("\nID da serie: ");
            setbuf(stdin,NULL);
            scanf("%d", &id);

            serie = buscarS(s,id);
            if (serie != NULL)
            {
                letra_D(serie->t);

            }
            
            else printf("\nSerie nao encontrada!");
        }

        
    }
    printf("\nSistema encerrado!\n");

    liberar_all_S(&s);
    }

    else
    printf("Falha ao alocar memoria!");

    
    return 0;
}