#include <stdio.h>
#include "tarefas.h"
#include <stdlib.h>

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar,};

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
        printf("0 - Sair, salvar e carregar tarefas\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
            ERROS erro = salvarbinario(tarefas, &pos);
            if (erro != OK)
             printf("Erro ao salvar as tarefas\n");
            else
              printf("Tarefas salvas \n");
        

        if (opcao == 0){
            ERROS erro = carregarbinario(tarefas, &pos);
            if (erro != OK)
                printf("Erro ao carregar tarefa\n");
            else 
                printf("Tarefa carregada\n");
        }

        if(opcao > 2)
            printf("Opcao invalida\n");
            
        else if(opcao >= 0)
            fs[opcao](tarefas, &pos);
         if (erro != OK){//retornando um erro
              printf("Erro ao encontrar\n");
              return NAO_ENCONTRADO;
            }
        else
            printf("Sair...\n");

    } while(opcao >= 0);

    fs[3](tarefas, &pos);
    if(erro != OK){//retornando um erro 
      printf("Erro ao escrever\n");
      return  ESCREVER;
    }
}