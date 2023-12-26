#include "artista.c"

//Esta função remove todas as musicas,albuns e artistas do sistema visando liberar toda a memória usada para encerrar o sistema
void encerrar_sistema(RB_artista **arvore)
{
    if(*arvore != NULL)
    {
        remover_todos_artistas(&(*arvore));
    }
}
