#include <stdio.h>
#include "tarefas.h"

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if (erro == ABRIR) {
        printf("Erro ao carregar o arquivo para abrir.\n");
        pos = 0;

    } else if (erro == FECHAR) {
        printf("Erro ao carregar o arquivo para fechar.\n");
        pos = 0;

    } else if (erro == LER) {
        printf("Erro ao carregar o arquivo para ler.\n");
        pos = 0;
    }

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao > 2){
            printf("Opcao invalida\n");
        } else if (opcao == 0) {
            erro = fs[opcao](tarefas, &pos);
            if (erro == MAX_TAREFA) {
                printf("Máximo de tarefas alcançadas\n");
            }
        } else if (opcao == 1) {
            erro = fs[opcao](tarefas, &pos);
            if (erro == SEM_TAREFAS) {
                printf("Sem tarefas para deletar\n");
            } else if (erro == NAO_ENCONTRADO) {
                printf("Tarefa não existe\n");
            }
        } else if (opcao == 2) {
            erro = fs[opcao](tarefas, &pos);
            if (erro == NAO_ENCONTRADO) {
                printf("Sem tarefas para listar\n");
            }
        }
        else
            printf("Sair...\n");

    } while(opcao >= 0);

    erro = fs[3](tarefas, &pos);
    if (erro == ABRIR) {
        printf("Erro para abrir o arquivo ao salvar\n");
    } else if (erro == FECHAR) {
        printf("Erro para fechar o arquivo ao salvar\n");
    } else if (erro == ESCREVER) {
        printf("Erro ao escrever no arquivo ao salvar\n");
    }
}
