#include <stdio.h>
#include "tarefas.h"

int main(){
    // Declaração de um array de ponteiros para função 'funcao' chamado fs, inicializado com as funções do arquivo "tarefas.h".
    funcao fs[] = {criar, deletar, listar, salvar, carregar, exportar};
    // Declaração de um array de estruturas Tarefa chamado 'tarefas' com tamanho TOTAL.
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
        printf("4 - Salvar tarefas\n"); // Adiciona a opção de salvar tarefas
        printf("5 - Carregar tarefas\n"); // Adiciona a opção de carregar tarefas
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        opcao--;
        if(opcao > 4) {
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
        else if(opcao == 3 || opcao == 4){
            fs[opcao](tarefas, &pos); // Chama a função correspondente à opção
        }else {
            printf("Sair...\n");
        }


    } while(opcao != -1); // Continua no loop até que o usuário escolha sair.

    if (opcao == -1) { // Se a opção for -1 (Sair), então exporta as tarefas para um arquivo de texto
        ERROS exportar_erro = fs[5](tarefas, &pos); // Chama a função exportar
        if (exportar_erro == OK) // mensagem de sucesso
            printf("Tarefas exportadas com sucesso para um arquivo de texto!\n");
        else
            printf("Erro ao exportar as tarefas para o arquivo de texto!\n"); // mensagem de erro
    }

    erro = fs[3](tarefas, &pos);
    if (erro == ABRIR) {
        printf("Erro para abrir o arquivo ao salvar\n");
    } else if (erro == FECHAR) {
        printf("Erro para fechar o arquivo ao salvar\n");
    } else if (erro == ESCREVER) {
        printf("Erro ao escrever no arquivo ao salvar\n");
    }
  
    return 0;
}

