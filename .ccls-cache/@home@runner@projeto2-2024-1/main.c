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
        printf("4 - Listar tarefas por categoria\n");
        printf("5 - Exportar tarefas para arquivo de texto|n");
        printf("6 - Salvar tarefas em arquivo binário\n"); 
        printf("7 - Carregar tarefas de arquivo binário\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao > 2)
            printf("Opcao invalida\n");
        else if(opcao >= 0)
            fs[opcao](tarefas, &pos);
        else {
            printf("Sair...\n");
            fs[3](tarefas, &pos); 
            exit(0);
        }
      } while(opcao >= 0);

          return 0; 
      }
    } while(opcao >= 0);

    fs[3](tarefas, &pos);
}

