#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao:\n");
        fflush(stdin);
        scanf(" %d", &opcao);

        opcao--;
        if(opcao > 2)
            printf("Opcao invalida\n");
        else if(opcao >= 0)
  {
              ERROS erro = fs[opcao](tarefas, &pos);
              if (erro != OK) {
                  printf("Erro ao executar a opcao %d: %d\n", opcao + 1, erro);
              }
          } else
              printf("Sair...\n");

      } while (opcao >= 0);

      ERROS erro_salvar = fs[3](tarefas, &pos);
      if (erro_salvar != OK) {
          printf("Erro ao salvar as tarefas: %d\n", erro_salvar);
      }

      return 0;
  }

