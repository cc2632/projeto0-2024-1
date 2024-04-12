#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    printf("Entre com a prioridade: "); // Solicita e armazena a prioridade da tarefa.
    scanf("%d", &tarefas[*pos].prioridade); // Solicita e armazena a prioridade da tarefa.
    clearBuffer(); // Limpa o buffer do teclado.

    printf("Entre com a categoria: "); // Solicita e armazena a categoria da tarefa.
    fgets(tarefas[*pos].categoria, 100, stdin); // Solicita e armazena a categoria da tarefa.

    printf("Entre com a descricao: "); // Solicita e armazena a descrição da tarefa.
    fgets(tarefas[*pos].descricao, 300, stdin); // Solicita e armazena a descrição da tarefa.

    *pos = *pos + 1; // Atualiza a posição atual das tarefas.

    return OK;
}
 // Função para deletar uma tarefa.
ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

// Move as tarefas uma posição para frente para preencher o espaço da tarefa deletada.
    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

// Função para listar todas as tarefas.
ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;
      // Percorre todas as tarefas e as imprime na tela.
    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

// Função para salvar as tarefas em um arquivo binário.
ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");  // Abre o arquivo para escrita binária.
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);  // Escreve as tarefas no arquivo.
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f); // Escreve a posição atual no arquivo.
    if(qtd == 0)
        return ESCREVER; 

    if(fclose(f)) // fecha o arquivo
        return FECHAR;

    return OK;
}
ERROS exportar(Tarefa tarefas[], int *pos){ // Função para exportar as tarefas para um arquivo de texto.
    char nome_arquivo[100];

    printf("Digite o nome do arquivo para exportar as tarefas: ");
    scanf("%s", nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita.
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return ABRIR;
    }

    for (int i = 0; i < *pos; i++) { // Escreve as tarefas no arquivo de texto.
        fprintf(arquivo, "Prioridade: %d\n", tarefas[i].prioridade);
        fprintf(arquivo, "Categoria: %s", tarefas[i].categoria);
        fprintf(arquivo, "Descricao: %s", tarefas[i].descricao);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo); // fecha o arquivo

    return OK;
}

//função para carregar as tarefas de um arquivo binário.
ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;

}
 // Função para limpar o buffer do teclado.
void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
