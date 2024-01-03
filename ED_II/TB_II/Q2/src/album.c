#include <stdio.h>
#include <string.h>
#include "musica.c"

#define TAM_TITULO 50
#define VERMELHO 1
#define PRETO 0

typedef struct Album
{
    char titulo[TAM_TITULO];
    int ano;
    int qtd_musicas;
    Lista_musicas *musicas;

} Album;

typedef struct Arv_23_album
{
    int qtd_infos;
    Album info1;
    Album info2;
    struct Arv_23_album *pai;
    struct Arv_23_album *esquerda;
    struct Arv_23_album *centro;
    struct Arv_23_album *direita;

} Arv_23_album;


/*
Preenche um album com seus respectivos dados

Args:
    album::Album*: Referência para o album que será preenchido
    titulo::char: Titulo do Album
    ano::int: Ano de publicação do album

Return:
    None
*/
void preencher_album(Album *album, char titulo[], int ano)
{
    strcpy(album->titulo, titulo);
    album->ano = ano;
    album->qtd_musicas = 0;
    album->musicas = NULL;
}

/*
Cria um nó para um album e dependendo do caso retorna:
    Nó do album quando criado com sucesso
    NULL quando não consegue alocar o nó

Args:
    None

Return:
    no::Arv_23_album*: Endereço de um nó album;

*/
Arv_23_album *cria_no_album()
{
    Arv_23_album *no = (Arv_23_album *)malloc(sizeof(Arv_23_album));

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
Verifica se um nó album é falho ou não
    1 - Caso seja folha
    0 - Caso não seja folha

Args:
    no::Arv_23_album*: Ponteiro para o nó que será checado

Return:
    sinal::int: Sinalização referente a checagem se é ou não folha
*/
int no_album_eh_folha(Arv_23_album *no)
{
    int sinal = 0;
    if (no->direita == NULL && no->centro == NULL && no->esquerda == NULL)
        sinal = 1;

    return sinal;
}

/*
Troca a posicação de dois albums com base na ordem alfabetica dos mesmos
o menor sempre ficará em a1, o do meio em a2 e o maior em a3

Args:
    a1::Album*: Ponteiro para album que será o menor
    a2::Album*: Ponteiro para album que será o do meio
    a3::Album*: Ponteiro para album que será o maior

Return:
    None

*/
void ordenar_albums(Album *a1, Album *a2, Album *a3)
{
    Album aux;
    // caso o primeiro seja maior que o segundo, e do que o terceiro
    if (compara_string(a1->titulo, a2->titulo) > 0 && compara_string(a1->titulo, a3->titulo) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a1;
        *a1 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->titulo, a2->titulo) > 0)
        {

            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o segundo seja o maior de todos
    else if (compara_string(a2->titulo, a1->titulo) > 0 && compara_string(a2->titulo, a3->titulo) > 0)
    {
        // garantir que a3 guarde o maior
        aux = *a3;
        *a3 = *a2;
        *a2 = aux;

        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->titulo, a2->titulo) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
    // caso o terceiro seja o maior de todos
    else if (compara_string(a3->titulo, a1->titulo) > 0 && compara_string(a3->titulo, a2->titulo) > 0)
    {
        // checagem pra saber quem fica no meio já que a3 guarda o maior
        if (compara_string(a1->titulo, a2->titulo) > 0)
        {
            aux = *a2;
            *a2 = *a1;
            *a1 = aux;
        }
    }
}

/*
Quebra um nó que tem 2 informações e recebeu mais uma, de forma a que a menor informação fique no nó, a informação do meio suba para o nó pai e a maior informação será alocada em outro nó

Args:
    no::Arv_23_album**: Referência do ponteiro que guarda o nó que será quebrado
    album::Album: Estrutura do tipo Album que deveria ter sido inserida caso tivesse espaço
    novo_no::Arv_23_album*: Novo nó da arvore que será destinado a guardar a maior informação resultante da quebra nó
    vai_subir::Album*: Referência para a estrutura Album que irá subir para o nó pai
    esquerda_novo_no::Arv_23_album*: Endereço do nó que será a esquerda do novo nó
    centro_novo_no::Arv_23_album*: Endereço do nó que será o centro do novo nó

Return:
    None
*/
void quebra_no_album(Arv_23_album **no, Album album, Arv_23_album *novo_no, Album *vai_subir, Arv_23_album *esquerda_novo_no, Arv_23_album *centro_novo_no)
{

    Album temp[3];
    temp[0] = (*no)->info1;
    temp[1] = (*no)->info2;
    temp[2] = album;

    ordenar_albums(&temp[0], &temp[1], &temp[2]);
    // garantirmos que o maior fique no novo nó e o do meio fique na info2
    (*no)->info1 = temp[0];
    (*no)->info2 = temp[1];

    novo_no->info1 = temp[2];

    (*no)->qtd_infos = 1;
    novo_no->qtd_infos = 1;

    novo_no->esquerda = esquerda_novo_no;
    novo_no->centro = centro_novo_no;

    *vai_subir = (*no)->info2;
}

/*
Após realizar a quebra do nó, o dado do meio deve subir para o nó pai, entretanto nem sempre isso é possivel já que existem 3 casos comuns para esse problema
    1 - Não existir um pai
        a - Significa que nó que estamos é a raiz da arvore, então precisamos criar um novo nó, para que seja a raiza da arvore e a antiga raiz e o nó alocado se tornem filhos dele
    2 - Existir um pai com uma informação
        a - Então apenas subimos a informação para ele, adicionando na posição correta e a direita desse pai se torna o novo nó
    3 - Existir um pai com duas informações
        a - Nesse caso devemos quebrar o nó pai e continuar escalando a arvore até que consigamos encontrar espaço ou a raiz da arvore seja mudada

Args:
    pai::Arv_23_album**: Referência do ponteiro que guarda o nó pai
    raiz::Arv_23_album**: Referência do ponteiro que guarda o nó que sofreu a quebra nó
    sobe::Album: Estrutura do tipo Album que acabou subindo devido a quebra nó
    novo_no::Arv_23_album*: Novo nó da arvore que será destinado a guardar a maior informação resultante da quebra nó

Return:
    head::Arv_23_album*: Referência do nó raiz da árvore

*/
Arv_23_album *sobe_album(Arv_23_album **pai, Arv_23_album **raiz, Album sobe, Arv_23_album *novo_no)
{
    Arv_23_album *head = NULL;
    // se não existe um pai (então é a raiz)
    if (((*pai)) == NULL)
    {
        Arv_23_album *padrasto = cria_no_album();

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
            int retorno = compara_string((*pai)->info1.titulo, sobe.titulo);

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
            Arv_23_album *aux = cria_no_album();
            Album sobe_quebra_dupla;
            novo_no->pai = aux;
            quebra_no_album(&(*pai), sobe, aux, &sobe_quebra_dupla, *raiz, novo_no);
            (*pai)->direita = NULL;

            head = sobe_album(&(*pai)->pai, &(*pai), sobe_quebra_dupla, aux);
        }
    }

    return head;
}

/*
Insere um novo nó album em uma arvore de albums e retorna o nó raiz da arvore;

Args:
    raiz::Arv_23_album*: Referência para a raiz da arvore;
    Album::Album: Estrutura album que será inserida na arvore se possivel

Return:
    aux::Arv_23_album*: Referência para a raiz da arvore.
*/
Arv_23_album *inserir_album_arv23(Arv_23_album *raiz, Album album)
{
    Arv_23_album *aux = raiz;
    
    //se a raiz da árvore é nula, então não existe arvore, basta criar um nó e definilo como raiz
    if (aux == NULL)
    {
        aux = cria_no_album();
        if (aux != NULL)
        {
            (aux)->info1 = album;
            (aux)->qtd_infos = 1;
        }
    }
    else if (no_album_eh_folha(aux))
    {
        if ((aux)->qtd_infos == 1)
        {
            int retorno = compara_string((aux)->info1.titulo, album.titulo);
            // caso o novo valor seja maior que o valor em info1
            if (retorno < 0)
            {
                (aux)->info2 = album;
                (aux)->qtd_infos = 2;
            }
            else if (retorno > 0)
            {
                (aux)->info2 = (aux)->info1;
                (aux)->info1 = album;
                (aux)->qtd_infos = 2;
            }
        }
        // caso sejá folha e tenha 2 infos, precisamos quebrar o nó (mas vamos garantir que a info não seja igual as que ja temos)
        else if ((aux)->qtd_infos == 2)
        {
            if (compara_string(aux->info1.titulo, album.titulo) != 0 && compara_string(aux->info2.titulo, album.titulo) != 0)
            {
                Arv_23_album *novo_no = cria_no_album();
                Album vai_subir;
                quebra_no_album(&(raiz), album, novo_no, &vai_subir, NULL, NULL);
                aux = sobe_album(&((raiz)->pai), &raiz, vai_subir, novo_no);
            }
        }
    }
    // Caso não seja folha vamos ter que percorrer a arvore para achar uma folha pronta para ser inserida
    else
    {
        int retorno = compara_string((aux)->info1.titulo, album.titulo);

        // caso info 1 seja maior que o album vamos pra esquerda
        if (retorno > 0)
            aux = inserir_album_arv23(aux->esquerda, album);

        // caso info 1 seja menor que o album, precisamos ver existe info2, caso exista vamos comparar com info 2, caso não vamos apenas ir para a direita de info 1 que será nosso centro
        else if (retorno < 0)
        {
            // se a direita for diferente de null, então existe info 2 para compararmos
            if ((aux)->direita != NULL)
            {
                retorno = compara_string(aux->info2.titulo, album.titulo);

                // caso info 2 seja menor que o album, então vamos para a direita
                if (retorno < 0)
                    aux = inserir_album_arv23(aux->direita, album);

                // caso info 2 seja maior que o album, então vamos pro centro
                else if (retorno > 0)
                    aux = inserir_album_arv23(aux->centro, album);
            }
            // já que não existe info 2, vamos para o centro
            else
                aux = inserir_album_arv23(aux->centro, album);
        }
    }
    // percorre o nó atual até chegar na raiz da arvore
    while (aux->pai != NULL)
    {
        aux = aux->pai;
    }

    return aux;
}

//Visualiza o nó album 
void mostrar_no_album(Arv_23_album *no)
{
    if (no != NULL)
    {
        printf("\n\nInfo1: %s", no->info1.titulo);
        if (no->qtd_infos == 2)
            printf("\tInfo2: %s", no->info2.titulo);
    }
}

/*
Função usada para visualizar a estrutura da arvore album e checar se a mesma segue os padrões da arvore 2-3
*/
void mostrar_arv_albums(Arv_23_album *raiz)
{
    if (raiz != NULL)
    {
        mostrar_no_album(raiz);
        mostrar_arv_albums(raiz->esquerda);
        mostrar_arv_albums(raiz->centro);
        mostrar_arv_albums(raiz->direita);
    }
}

/*
Busca uma estrutura Album dentro de uma árvore 2-3 de albums e retorna:
    NULL - Caso não encontre
    Album* - Caso encontre

Args:
    raiz::Arv_23_album*: Referência da raiz que guarda os albums
    nome_album::char: Nome do album que estamos buscando

Return:
    album_buscado::Album*: Resultado da busca

*/
Album *buscar_album(Arv_23_album *raiz, char nome_album[])
{
    Album *album_buscado = NULL;

    if (raiz != NULL)
    {
        int retorno;

        retorno = compara_string(raiz->info1.titulo, nome_album);

        // caso sejam iguais, achamos o album buscado
        if (retorno == 0)
            album_buscado = &raiz->info1;

        // caso o primeiro seja menor que o segundo, vamos checar se existe info 2 para comparar
        else if (retorno < 0)
        {
            if (raiz->qtd_infos == 2)
            {

                retorno = compara_string(raiz->info2.titulo, nome_album);

                // pode ser que info2 sejá quem estamos procurando
                if (retorno == 0)
                    album_buscado = &raiz->info2;

                // caso o primeiro seja menor que o segundo, vamos para a direita do nó atual
                else if (retorno < 0)
                    album_buscado = buscar_album(raiz->direita, nome_album);
            }
            // já que só temos info1 e ela é menor, vamos pro centro
            else
                album_buscado = buscar_album(raiz->centro, nome_album);
        }
        // caso o primeiro sejá maior que o segundo, vamos para a esquerda
        else
            album_buscado = buscar_album(raiz->esquerda, nome_album);
    }

    return album_buscado;
}

/*
Busca uma nó album dentro de uma árvore 2-3 de albums e retorna:
    NULL - Caso não encontre
    Arv_23_album* - Caso encontre

Args:
    raiz::Arv_23_album*: Referência da raiz que guarda os albums
    nome_album::char: Nome do album que estamos buscando

Return:
    album_buscado::Arv_23_album*: Resultado da busca

*/
Arv_23_album *buscar_no_album(Arv_23_album *raiz, char nome_album[])
{
    Arv_23_album *album_buscado = NULL;

    if (raiz != NULL)
    {
        int retorno;

        retorno = compara_string(raiz->info1.titulo, nome_album);

        // caso sejam iguais, achamos o album buscado
        if (retorno == 0)
            album_buscado = raiz;

        // caso o primeiro seja menor que o segundo, vamos checar se existe info 2 para comparar
        else if (retorno < 0)
        {
            if (raiz->qtd_infos == 2)
            {
                // caso o primeiro seja menor que o segundo, vamos para a direita do nó atual
                retorno = compara_string(raiz->info2.titulo, nome_album);

                if (retorno == 0)
                    album_buscado = raiz;

                else if (retorno < 0)
                    album_buscado = buscar_no_album(raiz->direita, nome_album);
                else
                    album_buscado = buscar_no_album(raiz->centro, nome_album);
            }
            // já que só temos info1 e ela é menor, vamos pro centro
            else
                album_buscado = buscar_no_album(raiz->centro, nome_album);
        }
        // caso o primeiro sejá maior que o segundo, vamos para a esquerda
        else
            album_buscado = buscar_no_album(raiz->esquerda, nome_album);
    }

    return album_buscado;
}

/*
Conta a quantidade de informações proximas a um nó, sendo elas seus valores, o de seus descendentes

Args:
    raiz::Arv_23_album*: Nó que será acessado para realizar a contagem das informações

Return:
    total::int: total de informações encontradas
*/
int conta_info_album(Arv_23_album *raiz)
{
    int total = 0;

    if (raiz != NULL)
    {
        if (raiz->qtd_infos == 2)
        {
            total += 2;
            total += conta_info_album(raiz->esquerda);
            total += conta_info_album(raiz->centro);
            total += conta_info_album(raiz->direita);
        }
        // caso não tenha 2, então tem uma
        else
        {
            total += 1;
            total += conta_info_album(raiz->esquerda);
            total += conta_info_album(raiz->centro);
        }
    }
    return total;
}

/*
Busca o nó que contem a menor informação dentro da árvore

Args:
    raiz::Arv_23_album*: Ponto de partida para realizar a busca

Return:
    menor::Arv_23_album*: Menor nó encontrado

*/
Arv_23_album *buscar_menor_album(Arv_23_album *raiz)
{
    Arv_23_album *menor = raiz;

    if (raiz->esquerda != NULL)
        menor = buscar_menor_album(raiz->esquerda);

    return menor;
}

/*
Busca o nó que contem a maior informação dentro da árvore

Args:
    raiz::Arv_23_album*: Ponto de partida para realizar a busca

Return:
    maior::Arv_23_album*: maior nó encontrado
    
*/
Arv_23_album *buscar_maior_album(Arv_23_album *raiz)
{
    Arv_23_album *maior = raiz;

    if (raiz->direita != NULL)
        maior = buscar_maior_album(raiz->direita);
    else if (raiz->centro != NULL)
        maior = buscar_menor_album(raiz->centro);

    return maior;
}

/*
Busca saber se o nó atual é filho da esquerda, centro ou direita de um nó pai
    -1 para esquerda
     0 para centro
     1 para direita

Args:
    no::Arv_23_album*: Ponto de partida da consulta

Return:
    sinal::int: Sinalização referente a localização
*/
int onde_estou_album(Arv_23_album *no)
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

/*
Remove um Album de um nó passado de uma árvore

Args:
    vai_sumir::Arv_23_album*: Referência do nó que terá um album removido
    nome_album::char: Nome do album que será removido

Return:
    raiz::Arv_23_album*: Referência da raiz da arvore resultante da remoção do valor passado
*/
Arv_23_album *remover_album_arv23(Arv_23_album *vai_sumir, char nome_album[])
{
    Arv_23_album *raiz = vai_sumir;

    if (no_album_eh_folha(vai_sumir))
    {
        int retorno;

        if (vai_sumir->qtd_infos == 2)
        {
            retorno = compara_string(vai_sumir->info2.titulo, nome_album);

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
                raiz = NULL;
                free(vai_sumir);
            }
            // se não for a raiz, precisamos checar se o pai tem 3 ou mais informações nos irmãos proximos para pedir ajuda
            else
            {
                int onde_estou = onde_estou_album(vai_sumir);

                // se estou na esquerda, precisamos olhar pro centro e/ou para direita
                if (onde_estou == -1)
                {
                    int infos_proximas = conta_info_album(vai_sumir->pai);
                    // se tiver mais de 3 informações nas proximidades, podemos pedir ajuda na remoção
                    if (infos_proximas > 3)
                    {
                        // o centro pode fornecer ajuda?
                        // levando em conta que o pai tem pelomenos uma info1, o centro precisa ter no minimo 2 infos pra fornecer ajuda
                        if (conta_info_album(vai_sumir->pai->centro) > 1)
                        {
                            // sobe-se o menor do centro para o pai ficando na info1, e a info1 do pai desce para substituir o nó que será removido
                            Arv_23_album *menor_centro = buscar_menor_album(vai_sumir->pai->centro);
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            vai_sumir->pai->info1 = menor_centro->info1;
                            raiz = remover_album_arv23(menor_centro, menor_centro->info1.titulo);
                        }
                        // se o centro não pode fornecer ajuda, vamos procurar pela direita
                        // levando em conta que o pai tem 2 informações, vamos realizar o movimento de "onda para reposicionar os valores"
                        else if (conta_info_album(vai_sumir->pai->direita) > 1)
                        {
                            Arv_23_album *menor_direita = buscar_menor_album(vai_sumir->pai->direita);
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            // o movimento de onda consiste em mover o menor valor da direita para info2, descer info 2 do pai para o filho do centro e subir a info1 do filho do centro para o info1 do pai. após esse processo a antiga info1 do pai será enviada como info1 do nó que perderá seu valor
                            vai_sumir->pai->info1 = vai_sumir->pai->centro->info1;
                            vai_sumir->pai->centro->info1 = vai_sumir->pai->info2;
                            vai_sumir->pai->info2 = menor_direita->info1;
                            raiz = remover_album_arv23(menor_direita, menor_direita->info1.titulo);
                        }
                        // se nem o centro e nem a direita podem, vamos precisar juntar
                        else
                        {
                            vai_sumir->info1 = vai_sumir->pai->info1;
                            vai_sumir->pai->info1 = vai_sumir->pai->centro->info1;
                            vai_sumir->pai->centro->info1 = vai_sumir->pai->info2;
                            Arv_23_album *menor_direita = buscar_menor_album(vai_sumir->pai->direita);
                            vai_sumir->pai->centro->info2 = menor_direita->info1;
                            free(menor_direita);
                            vai_sumir->pai->direita = NULL;
                            vai_sumir->pai->qtd_infos = 1;
                            vai_sumir->pai->centro->qtd_infos = 2;
                        }
                    }
                    else if (vai_sumir->pai->pai != NULL)
                    {
                        printf("\nPedir help ds ancestrais");
                    }
                    // caso não tenha 3 informações nas proximidades, vamos precisar juntar em um unico bloco
                    else
                    {
                        vai_sumir->info1 = vai_sumir->pai->info1;
                        vai_sumir->info2 = vai_sumir->pai->centro->info1;
                        free(vai_sumir->pai->centro);
                        Arv_23_album *aux = vai_sumir->pai;
                        vai_sumir->pai = NULL;
                        free(aux);
                        vai_sumir->qtd_infos = 2;
                    }
                }
                // se estou no centro, preciso olhar para direita e/ou para esquerda
                else if (onde_estou == 0)
                {
                    int infos_proximas = conta_info_album(vai_sumir->pai);
                    // se tiver mais de 3 informações nas proximidades, podemos pedir ajuda na remoção
                    if (infos_proximas > 3)
                    {
                        // A direita pode fornecer ajuda?
                        // levando em conta que o pai tem pelomenos uma info1, o centro precisa ter no minimo 2 infos pra fornecer ajuda
                        if (conta_info_album(vai_sumir->pai->direita) > 1)
                        {
                            // sobe-se o menor da direita para o pai ficando na info2, e a info2 do pai desce para substituir o nó que será removido no centro
                            Arv_23_album *menor_direita = buscar_menor_album(vai_sumir->pai->direita);
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            vai_sumir->pai->info2 = menor_direita->info1;
                            raiz = remover_album_arv23(menor_direita, menor_direita->info1.titulo);
                        }
                        // se a direita não pode fornecer ajuda, vamos procurar na esquerda, só que dessa vez será o maior
                        // levando em conta que o pai tem 2 informações, vamos realizar o movimento de "onda para reposicionar os valores"
                        else if (conta_info_album(vai_sumir->pai->esquerda) > 1)
                        {
                            Arv_23_album *maior_esquerda = buscar_maior_album(vai_sumir->pai->esquerda);
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
                                raiz = remover_album_arv23(maior_esquerda, maior_esquerda->info1.titulo);
                            }
                        }
                        // se nem a direita e a esquerda podem, vamos precisar juntar
                        else
                        {
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            vai_sumir->info2 = vai_sumir->pai->direita->info1;
                            vai_sumir->pai->qtd_infos = 1;
                            Arv_23_album *aux = vai_sumir->pai->direita;
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
                        Arv_23_album *aux1, *aux2;
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
                    int infos_proximas = conta_info_album(vai_sumir->pai);
                    // se tiver mais de 3 informações nas proximidades, podemos pedir ajuda na remoção
                    if (infos_proximas > 3)
                    {
                        // o centro pode fornecer ajuda?
                        if (conta_info_album(vai_sumir->pai->centro) > 1)
                        {
                            // vamos buscar o maior do centro e subir para o pai, e pegar a info2 do pai e descer
                            Arv_23_album *maior_centro = buscar_maior_album(vai_sumir->pai->centro);
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            if (maior_centro->qtd_infos == 2)
                            {
                                vai_sumir->pai->info2 = maior_centro->info2;
                                raiz = remover_album_arv23(maior_centro, maior_centro->info2.titulo);
                            }
                            else
                            {
                                vai_sumir->pai->info2 = maior_centro->info1;
                                raiz = remover_album_arv23(maior_centro, maior_centro->info1.titulo);
                            }
                        }
                        // se o centro não pode fornecer ajuda, vamos procurar na esquerda, só que dessa vez será o maior
                        // levando em conta que o pai tem 2 informações, vamos realizar o movimento de "onda para reposicionar os valores"
                        //a onda pegando emprestado da direita não deu pra vizualizar 
                        //pensar nisso e desenhar uma solução
                        else if (conta_info_album(vai_sumir->pai->esquerda) > 1)
                        {
                            Arv_23_album *maior_esquerda = buscar_maior_album(vai_sumir->pai->esquerda);
                            
                            vai_sumir->info1 = vai_sumir->pai->info2;
                            vai_sumir->pai->info2 = vai_sumir->pai->centro->info1;
                            vai_sumir->pai->centro->info1 = vai_sumir->pai->info1;

                            // o movimento de onda consiste em mover o menor valor da direita para info2, descer info 2 do pai para o filho do centro e subir a info1 do filho do centro para o info1 do pai. após esse processo a antiga info1 do pai será enviada como info1 do nó que perderá seu valor

                            // o maior da esquerda tem info2? se não tiver então pegamos info1 mesmo
                            if (maior_esquerda->qtd_infos == 2)
                            {
                                vai_sumir->pai->info1 = maior_esquerda->info2;
                                raiz = remover_album_arv23(maior_esquerda, maior_esquerda->info2.titulo);
                            }
                            else
                            {
                                vai_sumir->pai->info1 = maior_esquerda->info1;
                                raiz = remover_album_arv23(maior_esquerda, maior_esquerda->info1.titulo);
                            }
                        }
                        // se nem o centro e a esquerda podem, vamos precisar juntar
                        else
                        {
                            //adaptar aqui
                            vai_sumir->pai->centro->info2 = vai_sumir->pai->info2;
                            vai_sumir->pai->qtd_infos = 1;
                            Arv_23_album *aux = vai_sumir;
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
            int retorno = compara_string(vai_sumir->info1.titulo, nome_album);

            // caso não seja info1, entãa é info2
            if (retorno < 0)
            {
                //olhamos primeiro pro centro
                if (conta_info_album(vai_sumir->centro) > 1)
                {
                    Arv_23_album *maior_centro = buscar_maior_album(vai_sumir->centro);

                    if (maior_centro->qtd_infos == 2)
                    {
                        vai_sumir->info2 = maior_centro->info2;
                        remover_album_arv23(maior_centro, maior_centro->info2.titulo);
                    }
                    else
                    {
                        vai_sumir->info2 = maior_centro->info1;
                        remover_album_arv23(maior_centro, maior_centro->info1.titulo);
                    }
                }
                // nesse caso vamos a direita da arvore tenter pedir ajuda
                else if (conta_info_album(vai_sumir->direita) > 1)
                {
                    Arv_23_album *menor_direita = buscar_menor_album(vai_sumir->direita);
                    vai_sumir->info2 = menor_direita->info1;
                    remover_album_arv23(menor_direita, menor_direita->info1.titulo);
                }
                
                // se nem a direita e nem o centro podem ajudar, vamos tentar na esquerda fazendo o movimento de onda
                else if (conta_info_album(vai_sumir->esquerda) > 1)
                {
                    Arv_23_album *maior_esquerda = buscar_maior_album(vai_sumir->esquerda);

                    if (maior_esquerda->qtd_infos == 2)
                    {
                        vai_sumir->info2 = vai_sumir->centro->info1;
                        vai_sumir->centro->info1 = vai_sumir->info1;
                        vai_sumir->info1 = maior_esquerda->info2;
                        remover_album_arv23(maior_esquerda, maior_esquerda->info2.titulo);
                    }
                    else
                    {
                        vai_sumir->info2 = vai_sumir->centro->info1;
                        vai_sumir->centro->info1 = vai_sumir->info1;
                        vai_sumir->info1 = maior_esquerda->info1;
                        remover_album_arv23(maior_esquerda, maior_esquerda->info1.titulo);
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
                    Arv_23_album *aux = vai_sumir->direita;
                    vai_sumir->direita = NULL;
                    free(aux);
                }
            }
            //caso seja info1
            else
            {
                //vamos primeiro ver se o centro pode ajudar
                //olhamos primeiro pro centro
                if (conta_info_album(vai_sumir->centro) > 1)
                {
                    Arv_23_album *menor_centro = buscar_menor_album(vai_sumir->centro);
                    vai_sumir->info1 = menor_centro->info1;
                    remover_album_arv23(menor_centro, menor_centro->info1.titulo);
                }
                //se o centro não puder ajudar, vamos olhar a esquerda
                else if (conta_info_album(vai_sumir->esquerda) > 1)
                {
                    Arv_23_album * maior_esquerda = buscar_maior_album(vai_sumir->esquerda);

                    if(maior_esquerda->qtd_infos == 2)
                    {
                        vai_sumir->info1 = maior_esquerda->info2;
                        remover_album_arv23(maior_esquerda,maior_esquerda->info2.titulo);
                    }
                    else
                    {
                        vai_sumir->info1 = maior_esquerda->info1;
                        remover_album_arv23(maior_esquerda,maior_esquerda->info1.titulo);
                    }
                }
                //se nem o centro e nem a direita podem ajudar, vamos ter que recorrer a onda que vem da direita
                else if (conta_info_album(vai_sumir->direita) > 1)
                {
                    vai_sumir->info1 = vai_sumir->centro->info1;
                    vai_sumir->centro->info1 = vai_sumir->info2;
                    Arv_23_album *menor_direita = buscar_menor_album(vai_sumir->direita);
                    vai_sumir->info2 = menor_direita->info1;
                    remover_album_arv23(menor_direita,menor_direita->info1.titulo);
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
                    Arv_23_album *aux = vai_sumir->direita;
                    vai_sumir->direita = NULL;
                    free(aux);
                }     
            }
        }
        //se só tem uma informação então não tem filhos da direita
        else
        {
            //o centro pode pedir fornecer ajuda?
            if(conta_info_album(vai_sumir->centro)>1)
            {
                Arv_23_album *menor_centro = buscar_menor_album(vai_sumir->centro);
                vai_sumir->info1 = menor_centro->info1;
                remover_album_arv23(menor_centro,menor_centro->info1.titulo);
            }
            // se o centro não puder ajudar, procuramos ajuda na esquerda
            else if (conta_info_album(vai_sumir->esquerda) > 1)
            {
                Arv_23_album *maior_esquerda = buscar_maior_album(vai_sumir->esquerda);
                if(maior_esquerda->qtd_infos == 2)
                {
                    vai_sumir->info1 = maior_esquerda->info2;
                    remover_album_arv23(maior_esquerda,maior_esquerda->info2.titulo);
                }
                else
                {
                    vai_sumir->info1 = maior_esquerda->info1;
                    remover_album_arv23(maior_esquerda,maior_esquerda->info1.titulo);    
                }
            }
            //se nem o centro nem a esquerda podem ajudar, então vamos remover e juntar
            else
            {
                vai_sumir->info1 = vai_sumir->esquerda->info1;
                vai_sumir->info2 = vai_sumir->centro->info1;
                vai_sumir->qtd_infos = 2;
                Arv_23_album *esquerda, *centro;
                esquerda = vai_sumir->esquerda;
                centro = vai_sumir->centro;
                vai_sumir->esquerda = NULL;
                vai_sumir->centro = NULL;
                free(esquerda);
                free(centro);
            }
        }
    }

    if (raiz != NULL)
    {
        while (raiz->pai != NULL)
            raiz = raiz->pai;
    }

    return raiz;
}
