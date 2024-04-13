#include <stdio.h>
#include "tarefas.h"

int main(){
    int opcao;

    Tarefa tarefas[TOTAL];
    int pos = 0;
    ERROS erro = carregar(tarefas, &pos, TOTAL);
    if(erro == ABRIR || erro == LER || erro == FECHAR)
    pos = 0;
    printf("Arquivo não encontrado\n");

    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
scanf("%d", &opcao);
    printf("Opcao escolhida: %d\n", opcao);

    if (opcao == 1) {
      erro = criar(tarefas, &pos);
      if(erro == MAX_TAREFA)
        printf("Maximo de tarefas atingido\n");

    } else if (opcao == 2) {
      erro = deletar(tarefas, &pos);
      if(erro == SEM_TAREFAS)
        printf("Tarefa nao encontrada\n");
    } else if (opcao == 3) {
      erro = listar(tarefas, &pos);
      if(erro == SEM_TAREFAS)
        printf("Nao ha tarefas\n");
      listar(tarefas, &pos);
    } else if (opcao == 0)
      printf("Sair...\n");
      erro = salvar(tarefas, &pos, TOTAL);
      if(erro == LER || erro == FECHAR)
        printf("Erro ao ler as tarefas do arquivo\n");
      else if (erro == ABRIR){
        pos = 0;
        printf("Arquivo não encontrado\n");
      }
    else
      printf("Opcao invalida\n");

  } while (opcao != 0);
}
