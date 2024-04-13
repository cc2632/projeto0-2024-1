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
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        clearBuffer();
        opcao--;
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