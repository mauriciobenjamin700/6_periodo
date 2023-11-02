#include <stdio.h>
#include "tad.c"
#include "menu.c"



int main(void)
{
    struct Serie *s;
    int opc = 1;
    iniciarS(&s);
    int id_busca;
    int id;
    int sinal = 0;
    Serie * serie;

    while (opc!=4)
    {
        opc = menu();
        if(opc==11)
        { 
            id = geraId(&s);
            Serie* new;
            preencherS(&new, id);
            sinal = cadastrarS(&s, new);

            if(sinal) printf("\nCadastro realizado com sucesso!");
            else printf("\nFalha no Cadastro");
        }       
        else if(opc == 12)
        {
            printf("\nInforme o código da serie que deseja buscar: ");
            scanf("%d", &id_busca);
            serie =  buscarS(s,id_busca);
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
                if (cadastrarT(&(s->t))) printf("\nTemporada Adicionada com sucesso!");
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
 
            
        
    }
    printf("\nSistema encerrado!\n");
    liberar_all_S(&s);
    return 0;
}