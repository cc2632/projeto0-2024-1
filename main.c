#include "tarefas.h"
#include <stdio.h>

#define TAM_DESCRICAO 300
#define TAM_CATEGORIA 100

int main() {
  funcao fs[] = {criar, deletar, listar, salvar, carregar};

  Tarefa tarefas[TOTAL];
  int pos;
  ERROS erro = fs[4](tarefas, &pos);
  if (erro != OK)
    pos = 0;

  int opcao;
  do {
    printf("\nMenu principal\n");
    printf("1 - Criar tarefa\n");
    printf("2 - Deletar tarefa\n");
    printf("3 - Listar tarefas\n");
    printf("4 - Salvar e exportar\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d", &opcao);
    opcao--;
    if (opcao > 5)
      printf("Opcao invalida\n");
    else if (opcao >= 0)
      fs[opcao](tarefas, &pos);
    else if (opcao == 3)
      fs[opcao](tarefas, &pos);
    else
      printf("Sair...\n");

  } while (opcao >= 0);

  fs[3](tarefas, &pos);
}
