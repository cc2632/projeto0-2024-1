#include <stdio.h>
#include "tarefas.h"

int main(){
    // Declaração de um array de ponteiros para função 'funcao' chamado fs, inicializado com as funções do arquivo "tarefas.h".
    funcao fs[] = {criar, deletar, listar, salvar, carregar, exportar};
    // Declaração de um array de estruturas Tarefa chamado 'tarefas' com tamanho TOTAL.
    Tarefa tarefas[TOTAL];

    int pos;
    // Declaração da variável 'pos' que será usada para armazenar a posição atual no array 'tarefas'.
    ERROS erro = fs[4](tarefas, &pos);// Chama a função de carregar tarefas do arquivo binário e armazena um possível erro retornado.
    if(erro != OK)
        pos = 0;

    int opcao; 
    do{ // looping do menu
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);// Lê a opção do usuário.
        opcao--;
        if(opcao > 3) // Verifica se a opção é válida.
            printf("Opcao invalida\n");
        else if(opcao >= 0)
            fs[opcao](tarefas, &pos); // Chama a função correspondente à opção escolhida pelo usuário.
        else
            printf("Sair...\n"); 

    } while(opcao != -1); // Continua no loop até que o usuário escolha sair.

    if (opcao == -1) { // Se a opção for -1 (Sair), então exporta as tarefas para um arquivo de texto
        ERROS exportar_erro = fs[5](tarefas, &pos); // Chama a função exportar
        if (exportar_erro == OK) // mensagem de sucesso
            printf("Tarefas exportadas com sucesso para um arquivo de texto!\n");
        else
            printf("Erro ao exportar as tarefas para o arquivo de texto!\n"); // mensagem de erro
    }

    return 0;
}
