//Erik Kenzo Hashizume RA: 24.223.001-9
//Gustavo Lima de Azevedo RA: 24.123.096-0
//Rafael Vianna Maistro RA: 24.223.011-8



// main.c
#include <stdio.h>
#include "tarefas.h"

int main() {  
    funcao *fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos = 0;
    ERROS erro = carregar(tarefas, &pos);
    if (erro == ABRIR) {
        pos = 0;
        printf("Arquivo não encontrado\n");
    } else if (erro == LER || erro == FECHAR) {
        printf("Arquivo vazio\n");
    }

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            fs[0](tarefas, &pos); 
        } else if (opcao == 2) {
            fs[1](tarefas, &pos);
        } else if (opcao == 3) {
            fs[2](tarefas, pos);
        } else if (opcao == 0) {
            printf("Sair...\n");
            break;
        } else {
            printf("opção inválida\n");
        }
    } while (opcao != 0);
    return 0;
}

 // para rodar o codigo basta usar o comando gcc *.c && ./a.out
