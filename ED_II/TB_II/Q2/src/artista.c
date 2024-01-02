#include "album.c"
#include "artista.h"

#define NOME 50
#define TIPO 20
#define ESTILO 20

typedef struct Artista
{
    char nome[NOME];
    char tipo[TIPO];
    char estilo[ESTILO];
    int num_albuns;
    Arv_23_album *albuns;

} Artista;

typedef struct Arv_23_artista
{
    int qtd_infos;
    Artista info1;
    Artista info2;
    struct Arv_23_artista *pai;
    struct Arv_23_artista *esquerda;
    struct Arv_23_artista *centro;
    struct Arv_23_artista *direita;

} Arv_23_artista;

/*
Preenche um artista com seus respectivos dados

Args:
    artista::Artista*: Ponteiro para o artista que será preenchido
    nome::char: Nome do Artista
    tipo::char: Tipo do Artista
    estilo::char: Estilo do Artista

Return:
    None
*/
void preencher_artista(Artista *artista, char nome[], char tipo[], char estilo[])
{
    strcpy(artista->nome, nome);
    strcpy(artista->tipo, tipo);
    strcpy(artista->estilo, estilo);
    artista->num_albuns = 0;
    artista->albuns = NULL;
}

/*
Cria um nó para um artista e dependendo do caso retorna:
    Nó do artista quando criado com sucesso
    NULL quando não consegue alocar o nó

Args:
    None

Return:
    no::Arv_23_artista*: Endereço de um nó artista;

*/
Arv_23_artista *cria_no_artista()
{
    Arv_23_artista *no = (Arv_23_artista *)malloc(sizeof(Arv_23_artista));

    if (no)
    {
        no->qtd_infos = 0;
        no->pai = NULL;
        no->esquerda = NULL;
        no->centro = NULL;
        no->direita = NULL;
    }
    else
        no = NULL;

    return no;
}

/*
Verifica se um nó artista é falho ou não
    1 - Caso seja folha
    0 - Caso não seja folha

Args:
    no::Arv_23_artista*: Ponteiro para o nó que será checado

Return:
    sinal::int: Sinalização referente a checagem se é ou não folha
*/
int no_artista_eh_folha(Arv_23_artista *no)
{
    int sinal = 0;
    if (no->direita == NULL && no->centro == NULL && no->esquerda == NULL)
        sinal = 1;

    return sinal;
}

/*
Troca a posicação de dois artistas com base na ordem alfabetica dos mesmos
o menor sempre ficará em a1, o do meio em a2 e o maior em a3

Args:
    a1::Artista*: Ponteiro para artista que será o menor
    a2::Artista*: Ponteiro para artista que será o do meio
    a3::Artista*: Ponteiro para artista que será o maior

Return:
    None

*/
void ordenar_artistas(Artista *a1, Artista *a2, Artista *a3)
{
    Artista aux;
    // caso o primeiro seja maior que o segundo, e do que o terceiro
    if (compara_string(a1->nome, a2->nome) > 0 && compara_string(a1->nome, a3->nome) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a1;
        *a1 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {

            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o segundo seja o maior de todos
    else if (compara_string(a2->nome, a1->nome) > 0 && compara_string(a2->nome, a3->nome) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a2;
        *a2 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o terceiro seja o maior de todos
    else if (compara_string(a3->nome, a1->nome) > 0 && compara_string(a3->nome, a2->nome) > 0)
    {
        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->nome, a2->nome) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
}

void quebra_no_artista(Arv_23_artista **no, Artista artista, Arv_23_artista *novo_no, Artista *vai_subir, Arv_23_artista *esquerda_novo_no, Arv_23_artista *direita_novo_no)
{

    Artista temp[3];
    temp[0] = (*no)->info1;
    temp[1] = (*no)->info2;
    temp[2] = artista;

    ordenar_artistas(&temp[0], &temp[1], &temp[2]);
    // garantirmos que o maior fique no novo nó e o do meio fique na info2
    (*no)->info1 = temp[0];
    (*no)->info2 = temp[1];

    novo_no->info1 = temp[2];

    (*no)->qtd_infos = 1;
    novo_no->qtd_infos = 1;

    novo_no->esquerda = esquerda_novo_no;
    novo_no->centro = direita_novo_no;

    *vai_subir = (*no)->info2;
}

Arv_23_artista *sobe_artista(Arv_23_artista **pai, Arv_23_artista **raiz, Artista sobe, Arv_23_artista *novo_no)
{
    Arv_23_artista *head = NULL;
    // se não existe um pai (então é a raiz)
    if (((*pai)) == NULL)
    {
        Arv_23_artista *padrasto = cria_no_artista();

        if (padrasto != NULL)
        {
            padrasto->info1 = sobe;
            padrasto->esquerda = *raiz;
            padrasto->centro = novo_no;
            padrasto->qtd_infos = 1;

            (*raiz)->pai = padrasto;
            (*raiz)->direita = NULL;
            novo_no->pai = padrasto;

            head = padrasto; // questionavel
        }
        else
            printf("\nFALHA AO ALOCAR MEMORIA");
    }
    // caso exista um pai
    else
    {
        // checar se tem espaço, se tiver inserir na posição correta
        if ((*pai)->qtd_infos == 1)
        {
            int retorno = compara_string((*pai)->info1.nome, sobe.nome);

            if (retorno < 0)
            {
                (*pai)->info2 = sobe;
                (*pai)->direita = novo_no;
                (*pai)->qtd_infos = 2;

                novo_no->pai = (*pai);

                head = *pai;
            }
            else if (retorno > 0)
            {
                (*pai)->info2 = (*pai)->info1;
                (*pai)->info1 = sobe;
                (*pai)->direita = novo_no;
                (*pai)->qtd_infos = 2;

                novo_no->pai = (*pai);

                head = *pai;
            }
        }
        // caso não tenha espaço, precisa quebrar o nó novamente e repetir o processo
        else if ((*pai)->qtd_infos == 2)
        {
            Arv_23_artista *aux = cria_no_artista();
            Artista sobe_quebra_dupla;
            novo_no->pai = aux;
            quebra_no_artista(&(*pai), sobe, aux, &sobe_quebra_dupla, *raiz, novo_no);
            // teste
            (*pai)->direita = NULL;

            head = sobe_artista(&(*pai)->pai, &(*pai), sobe_quebra_dupla, aux);
        }
    }

    return head;
}
/*
Insere um novo nó artista em uma arvore de artistas e retorna o nó raiz da arvore;


Args:
    raiz::Arv_23_artista*: Referência para a raiz da arvore;
    Artista::Artista: Estrutura artista que será inserida na arvore se possivel

Return:
    aux::Arv_23_artista*: Ponteiro para a raiz da arvore.
*/
Arv_23_artista *inserir_artista_arv23(Arv_23_artista *raiz, Artista artista)
{
    Arv_23_artista *aux = raiz;

    if (aux == NULL)
    {
        aux = cria_no_artista();
        if (aux != NULL)
        {
            (aux)->info1 = artista;
            (aux)->qtd_infos = 1;
        }
    }
    else if (no_artista_eh_folha(aux))
    {
        if ((aux)->qtd_infos == 1)
        {
            int retorno = compara_string((aux)->info1.nome, artista.nome);
            // caso o novo valor seja maior que o valor em info1
            if (retorno < 0)
            {
                (aux)->info2 = artista;
                (aux)->qtd_infos = 2;
            }
            else if (retorno > 0)
            {
                (aux)->info2 = (aux)->info1;
                (aux)->info1 = artista;
                (aux)->qtd_infos = 2;
            }
        }
        // caso sejá folha e tenha 2 infos, precisamos quebrar o nó (mas vamos garantir que a info não seja igual as que ja temos)
        else if ((aux)->qtd_infos == 2)
        {
            if (compara_string(aux->info1.nome, artista.nome) != 0 && compara_string(aux->info2.nome, artista.nome) != 0)
            {
                Arv_23_artista *novo_no = cria_no_artista();
                Artista vai_subir;
                quebra_no_artista(&(raiz), artista, novo_no, &vai_subir, NULL, NULL);
                aux = sobe_artista(&((raiz)->pai), &raiz, vai_subir, novo_no);
            }
        }
    }
    // Caso não seja folha vamos ter que percorrer a arvore para achar uma folha pronta para ser inserida
    else
    {
        int retorno = compara_string((aux)->info1.nome, artista.nome);

        // caso info 1 seja maior que o artista vamos pra esquerda
        if (retorno > 0)
            aux = inserir_artista_arv23(aux->esquerda, artista);

        // caso info 1 seja menor que o artista, precisamos ver existe info2, caso exista vamos comparar com info 2, caso não vamos apenas ir para a direita de info 1 que será nosso centro
        else if (retorno < 0)
        {
            // se a direita for diferente de null, então existe info 2 para compararmos
            if ((aux)->direita != NULL)
            {
                retorno = compara_string(aux->info2.nome, artista.nome);

                // caso info 2 seja menor que o artista, então vamos para a direita
                if (retorno < 0)
                    aux = inserir_artista_arv23(aux->direita, artista);

                // caso info 2 seja maior que o artista, então vamos pro centro
                else if (retorno > 0)
                    aux = inserir_artista_arv23(aux->centro, artista);
            }
            // já que não existe info 2, vamos para o centro
            else
                aux = inserir_artista_arv23(aux->centro, artista);
        }
    }
    // percorre o nó atual até chegar na raiz da arvore
    while (aux->pai != NULL)
    {
        aux = aux->pai;
    }

    return aux;
}

void mostrar_no_artista(Arv_23_artista *no)
{
    if (no != NULL)
    {
        printf("\n\nInfo1: %s", no->info1.nome);
        if (no->qtd_infos == 2)
            printf("\tInfo2: %s", no->info2.nome);
    }
}

void mostrar_arv_artistas(Arv_23_artista *raiz)
{
    if (raiz != NULL)
    {
        mostrar_no_artista(raiz);
        mostrar_arv_artistas(raiz->esquerda);
        mostrar_arv_artistas(raiz->centro);
        mostrar_arv_artistas(raiz->direita);
    }
}

Artista *buscar_artista(Arv_23_artista *raiz, char nome_artista[])
{
    Artista *artista_buscado = NULL;

    if (raiz != NULL)
    {
        int retorno;

        retorno = compara_string(raiz->info1.nome, nome_artista);

        // caso sejam iguais, achamos o artista buscado
        if (retorno == 0)
            artista_buscado = &raiz->info1;

        // caso o primeiro seja menor que o segundo, vamos checar se existe info 2 para comparar
        else if (retorno < 0)
        {
            if (raiz->qtd_infos == 2)
            {

                retorno = compara_string(raiz->info2.nome, nome_artista);

                // pode ser que info2 sejá quem estamos procurando
                if (retorno == 0)
                    artista_buscado = &raiz->info2;

                // caso o primeiro seja menor que o segundo, vamos para a direita do nó atual
                else if (retorno < 0)
                    artista_buscado = buscar_artista(raiz->direita, nome_artista);
            }
            // já que só temos info1 e ela é menor, vamos pro centro
            else
                artista_buscado = buscar_artista(raiz->centro, nome_artista);
        }
        // caso o primeiro sejá maior que o segundo, vamos para a esquerda
        else
            artista_buscado = buscar_artista(raiz->esquerda, nome_artista);
    }

    return artista_buscado;
}

Arv_23_artista *buscar_no_artista(Arv_23_artista *raiz, char nome_artista[])
{
    Arv_23_artista *artista_buscado = NULL;

    if (raiz != NULL)
    {
        int retorno;

        retorno = compara_string(raiz->info1.nome, nome_artista);

        // caso sejam iguais, achamos o artista buscado
        if (retorno == 0)
            artista_buscado = raiz;

        // caso o primeiro seja menor que o segundo, vamos checar se existe info 2 para comparar
        else if (retorno < 0)
        {
            if (raiz->qtd_infos == 2)
            {
                // caso o primeiro seja menor que o segundo, vamos para a direita do nó atual
                retorno = compara_string(raiz->info2.nome, nome_artista);

                if (retorno == 0)
                    artista_buscado = raiz;

                else if (retorno < 0)
                    artista_buscado = buscar_no_artista(raiz->direita, nome_artista);
            }
            // já que só temos info1 e ela é menor, vamos pro centro
            else
                artista_buscado = buscar_no_artista(raiz->centro, nome_artista);
        }
        // caso o primeiro sejá maior que o segundo, vamos para a esquerda
        else
            artista_buscado = buscar_no_artista(raiz->esquerda, nome_artista);
    }

    return artista_buscado;
}

int conta_info_artista(Arv_23_artista *raiz)
{
    int total = 0;

    if (raiz != NULL)
    {
        if (raiz->qtd_infos == 2)
        {
            total += 2;
            total += conta_info_artista(raiz->esquerda);
            total += conta_info_artista(raiz->centro);
            total += conta_info_artista(raiz->direita);
        }
        // caso não tenha 2, então tem uma
        else
        {
            total += 1;
            total += conta_info_artista(raiz->esquerda);
            total += conta_info_artista(raiz->centro);
        }
    }
    return total;
}

Arv_23_artista *buscar_menor_artista(Arv_23_artista *raiz)
{
    Arv_23_artista *menor = raiz;

    if (raiz->esquerda != NULL)
        menor = buscar_menor_artista(raiz->esquerda);

    return menor;
}

Arv_23_artista *buscar_maior_artista(Arv_23_artista *raiz)
{
    Arv_23_artista *maior = raiz;

    if (raiz->direita != NULL)
        maior = buscar_maior_artista(raiz->direita);
    else if (raiz->centro != NULL)
        maior = buscar_menor_artista(raiz->centro);

    return maior;
}

/*
Busca saber se o nó atual é filho da esquerda, centro ou direita de um nó pai
    -1 para esquerda
     0 para centro
     1 para direita
*/
int onde_estou_artista(Arv_23_artista *no)
{
    int sinal;

    if (no == no->pai->esquerda)
        sinal = -1;
    else if (no == no->pai->centro)
        sinal = 0;
    else
        sinal = 1;

    return sinal;
}

Arv_23_artista *remover_artista_arv23(Arv_23_artista *vai_sumir, char nome_artista[])
{
    Arv_23_artista *raiz = vai_sumir;

    if (no_artista_eh_folha(vai_sumir))
    {
        int retorno;

        if (vai_sumir->qtd_infos == 2)
        {
            retorno = compara_string(vai_sumir->info2.nome, nome_artista);

            // caso seja info2, apenas deixamos info2 desativada com o contador de infos
            if (retorno == 0)
                vai_sumir->qtd_infos = 1;

            // se for info1 e temos 2 infos, info1 será sobreposta por info2 e desativamos info2
            else
            {
                vai_sumir->info1 = vai_sumir->info2;
                vai_sumir->qtd_infos = 1;
            }
        }
        // é folha e só tem uma informação, vai dar trabalho
        else
        {
            // ele é a raiz da arvore?   se sim então removemos o nó e nossa arvore fica nula
            if (vai_sumir->pai == NULL)
            {
                Arv_23_artista *aux = vai_sumir;
                vai_sumir = NULL;
                free(aux);
            }
            // se não for a raiz, precisamos checar se o pai tem 3 ou mais informações nos irmãos proximos para pedir ajuda
            else
            {
                int onde_estou = onde_estou_artista(vai_sumir);

                // se estou na esquerda, precisamos olhar pro centro e/ou para direita
                if (onde_estou == -1)
                {
                    int infos_proximas = conta_info_artista(vai_sumir->pai);
                    // se tiver mais de 3 informações nas proximidades, podemos pedir ajuda na remoção
                    if (infos_proximas > 3)
                    {
                        // o centro pode fornecer ajuda?
                        // levando em conta que o pai tem pelomenos uma info1, o centro precisa ter no minimo 2 infos pra fornecer ajuda
                        if (conta_info_artista(vai_sumir->pai->centro) > 1)
                        {
                            // sobe-se o menor do centro para o pai ficando na info1, e a info1 do pai desce para substituir o nó que será removido
                            Arv_23_artista *menor_centro = buscar_menor_artista(vai_sumir->pai->centro);
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            vai_sumir->pai->info1 = menor_centro->info1;
                            raiz = remover_artista_arv23(menor_centro, menor_centro->info1.nome);
                        }
                        // se o centro não pode fornecer ajuda, vamos procurar pela direita
                        // levando em conta que o pai tem 2 informações, vamos realizar o movimento de "onda para reposicionar os valores"
                        else if (conta_info_artista(vai_sumir->pai->direita) > 1)
                        {
                            Arv_23_artista *menor_direita = buscar_menor_artista(vai_sumir->pai->direita);
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            // o movimento de onda consiste em mover o menor valor da direita para info2, descer info 2 do pai para o filho do centro e subir a info1 do filho do centro para o info1 do pai. após esse processo a antiga info1 do pai será enviada como info1 do nó que perderá seu valor
                            vai_sumir->pai->info1 = vai_sumir->pai->centro->info1;
                            vai_sumir->pai->centro->info1 = vai_sumir->pai->info2;
                            vai_sumir->pai->info2 = menor_direita->info1;
                            raiz = remover_artista_arv23(menor_direita, menor_direita->info1.nome);
                        }
                        // se nem o centro e nem a direita podem, vamos precisar juntar
                        else
                        {
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            vai_sumir->pai->info1 = vai_sumir->pai->centro->info1;
                            vai_sumir->pai->centro->info1 = vai_sumir->pai->info2;
                            Arv_23_artista *menor_direita = buscar_menor_artista(vai_sumir->pai->direita);
                            vai_sumir->pai->centro->info2 = menor_direita->info1;
                            free(menor_direita);
                            vai_sumir->pai->direita = NULL;
                            vai_sumir->pai->qtd_infos = 1;
                            vai_sumir->pai->centro->qtd_infos = 2;
                        }
                    }
                    else if (vai_sumir->pai->pai != NULL)
                    {
                        printf("\nPedir help do avo");
                    }
                    // caso não tenha 3 informações nas proximidades, vamos precisar juntar em um unico bloco
                    else
                    {
                        vai_sumir->info1 = vai_sumir->pai->info1;
                        vai_sumir->info2 = vai_sumir->pai->centro->info1;
                        free(vai_sumir->pai->centro);
                        Arv_23_artista *aux = vai_sumir->pai;
                        vai_sumir->pai = NULL;
                        free(aux);
                        vai_sumir->qtd_infos = 2;
                    }
                }
                // se estou no centro, preciso olhar para direita e/ou para esquerda
                else if (onde_estou == 0)
                {
                    int infos_proximas = conta_info_artista(vai_sumir->pai);
                    // se tiver mais de 3 informações nas proximidades, podemos pedir ajuda na remoção
                    if (infos_proximas > 3)
                    {
                        // A direita pode fornecer ajuda?
                        // levando em conta que o pai tem pelomenos uma info1, o centro precisa ter no minimo 2 infos pra fornecer ajuda
                        if (conta_info_artista(vai_sumir->pai->direita) > 1)
                        {
                            // sobe-se o menor da direita para o pai ficando na info2, e a info2 do pai desce para substituir o nó que será removido no centro
                            Arv_23_artista *menor_direita = buscar_menor_artista(vai_sumir->pai->direita);
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            vai_sumir->pai->info2 = menor_direita->info1;
                            raiz = remover_artista_arv23(menor_direita, menor_direita->info1.nome);
                        }
                        // se a direita não pode fornecer ajuda, vamos procurar na esquerda, só que dessa vez será o maior
                        // levando em conta que o pai tem 2 informações, vamos realizar o movimento de "onda para reposicionar os valores"
                        else if (conta_info_artista(vai_sumir->pai->esquerda) > 1)
                        {
                            Arv_23_artista *maior_esquerda = buscar_maior_artista(vai_sumir->pai->esquerda);
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            // o movimento de onda consiste em mover o menor valor da direita para info2, descer info 2 do pai para o filho do centro e subir a info1 do filho do centro para o info1 do pai. após esse processo a antiga info1 do pai será enviada como info1 do nó que perderá seu valor

                            // o maior da esquerda tem info2? se não tiver então pegamos info1 mesmo
                            if (maior_esquerda->qtd_infos == 2)
                            {
                                vai_sumir->pai->info1 = maior_esquerda->info2;
                            }
                            else
                            {
                                vai_sumir->pai->info1 = maior_esquerda->info1;
                                raiz = remover_artista_arv23(maior_esquerda, maior_esquerda->info1.nome);
                            }
                        }
                        // se nem a direita e a esquerda podem, vamos precisar juntar
                        else
                        {
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            vai_sumir->info2 = vai_sumir->pai->direita->info1;
                            vai_sumir->pai->qtd_infos = 1;
                            Arv_23_artista *aux = vai_sumir->pai->direita;
                            vai_sumir->pai->direita = NULL;
                            free(aux);
                            vai_sumir->qtd_infos = 2;
                        }
                    }
                    else if (vai_sumir->pai->pai != NULL)
                    {
                        printf("\nPedir help do avo");
                    }
                    else
                    {
                        raiz = vai_sumir->pai;

                        vai_sumir->pai->info2 = vai_sumir->pai->info1;
                        vai_sumir->pai->info1 = vai_sumir->pai->esquerda->info1;
                        vai_sumir->pai->qtd_infos = 2;
                        Arv_23_artista *aux1, *aux2;
                        aux1 = vai_sumir->pai->esquerda;
                        aux2 = vai_sumir;
                        vai_sumir->pai->esquerda = NULL;
                        vai_sumir->pai->centro = NULL;
                        free(aux1);
                        free(aux2);
                    }
                }
                // se estou na direita, vou olhar para o centro e para a esquerda
                else if (onde_estou == 1)
                {
                    int infos_proximas = conta_info_artista(vai_sumir->pai);
                    // se tiver mais de 3 informações nas proximidades, podemos pedir ajuda na remoção
                    if (infos_proximas > 3)
                    {
                        // o centro pode fornecer ajuda?
                        if (conta_info_artista(vai_sumir->pai->centro) > 1)
                        {
                            // vamos buscar o maior do centro e subir para o pai, e pegar a info2 do pai e descer
                            Arv_23_artista *maior_centro = buscar_maior_artista(vai_sumir->pai->centro);
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            if (maior_centro->qtd_infos == 2)
                            {
                                vai_sumir->pai->info2 = maior_centro->info2;
                                raiz = remover_artista_arv23(maior_centro, maior_centro->info2.nome);
                            }
                            else
                            {
                                vai_sumir->pai->info2 = maior_centro->info1;
                                raiz = remover_artista_arv23(maior_centro, maior_centro->info1.nome);
                            }
                        }
                        // se o centro não pode fornecer ajuda, vamos procurar na esquerda, só que dessa vez será o maior
                        // levando em conta que o pai tem 2 informações, vamos realizar o movimento de "onda para reposicionar os valores"
                        // a onda pegando emprestado da direita não deu pra vizualizar
                        // pensar nisso e desenhar uma solução
                        else if (conta_info_artista(vai_sumir->pai->esquerda) > 1)
                        {
                            Arv_23_artista *maior_esquerda = buscar_maior_artista(vai_sumir->pai->esquerda);
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            // o movimento de onda consiste em mover o menor valor da direita para info2, descer info 2 do pai para o filho do centro e subir a info1 do filho do centro para o info1 do pai. após esse processo a antiga info1 do pai será enviada como info1 do nó que perderá seu valor

                            // o maior da esquerda tem info2? se não tiver então pegamos info1 mesmo
                            if (maior_esquerda->qtd_infos == 2)
                            {
                                vai_sumir->pai->info1 = maior_esquerda->info2;
                            }
                            else
                            {
                                vai_sumir->pai->info1 = maior_esquerda->info1;
                                raiz = remover_artista_arv23(maior_esquerda, maior_esquerda->info1.nome);
                            }
                        }
                        // se nem o centro e a esquerda podem, vamos precisar juntar
                        else
                        {
                            vai_sumir->pai->centro->info2 = vai_sumir->pai->centro->info2;
                            vai_sumir->pai->qtd_infos = 1;
                            Arv_23_artista *aux = vai_sumir;
                            vai_sumir->pai->direita = NULL;
                            raiz = vai_sumir->pai;
                            free(aux);
                        }
                    }
                    else if (vai_sumir->pai->pai != NULL)
                    {
                        printf("\nPedir help do avo");
                    }
                }
            }
        }
    }
    // se não for folha vamos precisar olhar para os filhos e para as infos que vamos remover
    else
    {
        if (vai_sumir->qtd_infos == 2)
        {
            int retorno = compara_string(vai_sumir->info1.nome, nome_artista);

            // caso não seja info1, entãa é info2
            if (retorno < 0)
            {
                //olhamos primeiro pro centro
                if (conta_info_artista(vai_sumir->centro) > 1)
                {
                    Arv_23_artista *maior_centro = buscar_maior_artista(vai_sumir->centro);

                    if (maior_centro->qtd_infos == 2)
                    {
                        vai_sumir->info2 = maior_centro->info2;
                        remover_artista_arv23(maior_centro, maior_centro->info2.nome);
                    }
                    else
                    {
                        vai_sumir->info2 = maior_centro->info1;
                        remover_artista_arv23(maior_centro, maior_centro->info1.nome);
                    }
                }
                // nesse caso vamos a direita da arvore tenter pedir ajuda
                else if (conta_info_artista(vai_sumir->direita) > 1)
                {
                    Arv_23_artista *menor_direita = buscar_menor_artista(vai_sumir->direita);
                    vai_sumir->info2 = menor_direita->info1;
                    remover_artista_arv23(menor_direita, menor_direita->info1.nome);
                }
                
                // se nem a direita e nem o centro podem ajudar, vamos tentar na esquerda fazendo o movimento de onda
                else if (conta_info_artista(vai_sumir->esquerda) > 1)
                {
                    Arv_23_artista *maior_esquerda = buscar_maior_artista(vai_sumir->esquerda);

                    if (maior_esquerda->qtd_infos == 2)
                    {
                        vai_sumir->info2 = vai_sumir->centro->info1;
                        vai_sumir->centro->info1 = vai_sumir->info1;
                        vai_sumir->info1 = maior_esquerda->info2;
                        remover_artista_arv23(maior_esquerda, maior_esquerda->info2.nome);
                    }
                    else
                    {
                        vai_sumir->info2 = vai_sumir->centro->info1;
                        vai_sumir->centro->info1 = vai_sumir->info1;
                        vai_sumir->info1 = maior_esquerda->info1;
                        remover_artista_arv23(maior_esquerda, maior_esquerda->info1.nome);
                    }
                }
                else if (vai_sumir->pai != NULL)
                {
                    printf("\nPedir ajuda aos ancestrais");
                }
                // se nem um dos filhos pode ajudar, vamos precisar quebrar e juntar
                else
                {
                    vai_sumir->qtd_infos = 1;
                    vai_sumir->centro->info2 = vai_sumir->direita->info1;
                    vai_sumir->centro->qtd_infos = 2;
                    Arv_23_artista *aux = vai_sumir->direita;
                    vai_sumir->direita = NULL;
                    free(aux);
                }
            }
            //caso seja info1
            else
            {
                //vamos primeiro ver se o centro pode ajudar
                //olhamos primeiro pro centro
                if (conta_info_artista(vai_sumir->centro) > 1)
                {
                    Arv_23_artista *menor_centro = buscar_menor_artista(vai_sumir->centro);
                    vai_sumir->info1 = menor_centro->info1;
                    remover_artista_arv23(menor_centro, menor_centro->info1.nome);
                }
                //se o centro não puder ajudar, vamos olhar a esquerda
                else if (conta_info_artista(vai_sumir->esquerda) > 1)
                {
                    Arv_23_artista * maior_esquerda = buscar_maior_artista(vai_sumir->esquerda);

                    if(maior_esquerda->qtd_infos == 2)
                    {
                        vai_sumir->info1 = maior_esquerda->info2;
                        remover_artista_arv23(maior_esquerda,maior_esquerda->info2.nome);
                    }
                    else
                    {
                        vai_sumir->info1 = maior_esquerda->info1;
                        remover_artista_arv23(maior_esquerda,maior_esquerda->info1.nome);
                    }
                }
                //se nem o centro e nem a direita podem ajudar, vamos ter que recorrer a onda que vem da direita
                else if (conta_info_artista(vai_sumir->direita) > 1)
                {
                    vai_sumir->info1 = vai_sumir->centro->info1;
                    vai_sumir->centro->info1 = vai_sumir->info2;
                    Arv_23_artista *menor_direita = buscar_menor_artista(vai_sumir->direita);
                    vai_sumir->info2 = menor_direita->info1;
                    remover_artista_arv23(menor_direita,menor_direita->info1.nome);
                }       
                else if (vai_sumir->pai != NULL)
                {
                    printf("\nPedir ajuda aos ancestrais");
                }
                // se nem um dos filhos pode ajudar, vamos precisar quebrar e juntar
                else
                {
                    vai_sumir->qtd_infos = 1;
                    vai_sumir->esquerda->info2 = vai_sumir->centro->info1;
                    vai_sumir->esquerda->qtd_infos = 2;
                    vai_sumir->info1 = vai_sumir->info2;
                    vai_sumir->centro->info1 = vai_sumir->direita->info1;
                    Arv_23_artista *aux = vai_sumir->direita;
                    vai_sumir->direita = NULL;
                    free(aux);
                }     
            }
        }
        //se só tem uma informação
        else
        {
            printf("\nTratar quando só tem uma informação na raiz");
        }
    }

    if (raiz != NULL)
    {
        while (raiz->pai != NULL)
            raiz = raiz->pai;
    }

    return raiz;
}
