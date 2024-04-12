#include "tarefas.h"
#include <stdio.h>

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
    if (opcao  > 5)
      printf("Opcao invalida\n");
    else if (opcao >= 0) {
      ERROS resultado = fs[opcao](tarefas, &pos);
      if (resultado != OK) {
        switch (resultado) {
          case MAX_TAREFA:
            printf("Erro: Numero maximo de tarefas atingido!\n");
            break;
          case SEM_TAREFAS:
            printf("Erro: Nao ha tarefas para realizar essa operacao!\n");
            break;
          case NAO_ENCONTRADO:
            printf("Erro: Tarefa nao encontrada!\n");
            break;
          case ABRIR:
            printf("Erro: Nao foi possivel abrir o arquivo!\n");
            break;
          case FECHAR:
            printf("Erro: Nao foi possivel fechar o arquivo!\n");
            break;
          case ESCREVER:
            printf("Erro: Nao foi possivel escrever no arquivo!\n");
            break;
          case LER:
            printf("Erro: Nao foi possivel ler do arquivo!\n");
            break;
          default:
            printf("Erro desconhecido!\n");
            break;
        }
      }
    } else if (opcao == 3) {
      ERROS resultado = fs[opcao](tarefas, &pos);
      if (resultado != OK) {
        switch (resultado) {
          case SEM_TAREFAS:
            printf("Erro: Nao ha tarefas para listar!\n");
            break;
          default:
            printf("Erro desconhecido!\n");
            break;
        }
      }
    } else {
      printf("Sair...\n");
    }
  } while (opcao >= 0);

  fs[3](tarefas, &pos);
}
