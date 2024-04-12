#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    
    // Carrega as tarefas do arquivo binário
    ERROS erro = fs[4](tarefas, &pos); 
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Salvar tarefas\n"); // Adiciona a opção de salvar tarefas
        printf("5 - Carregar tarefas\n"); // Adiciona a opção de carregar tarefas
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        if(opcao > 5 || opcao < 0) {
            printf("Opcao invalida\n");
            continue; // Volta para o início do loop
        }

        if(opcao == 0)
            printf("Sair...\n");
        else if(opcao == 4 || opcao == 5)
            fs[opcao-1](tarefas, &pos); // Chama a função correspondente à opção
        else
            fs[opcao-1](tarefas, &pos);

    } while(opcao != 0);

    return 0;
}
 