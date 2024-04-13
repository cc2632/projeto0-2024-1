#include <stdio.h>
#include <string.h>
#include "tarefas.h"

#define TAMANHO_CATEGORIA 100
#define TAMANHO_DESCRICAO 300

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    int prioridade;
    // Do while para forçar que o usuario entre com a prioridade entre 1 e 10
    do {
        printf("Entre com a prioridade: ");
        scanf("%d", &prioridade);
        clearBuffer();
        if (prioridade < 1 || prioridade > 10)
            printf("Digite um valor entre 1 e 10");
    } while (prioridade < 1 || prioridade > 10);

    tarefas[*pos].prioridade = prioridade;

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, TAMANHO_CATEGORIA, stdin);

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, TAMANHO_DESCRICAO, stdin);

    // STRCSPN tras oque é similar entre as string, nessa comparação vai trazer tudo que é 
    // vazio dentro da string que o usuario incluiu e vai jogar isso com NULO = \0
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

    *pos = *pos + 1;

    return OK;
}

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

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){
    if(*pos == 0)
        return SEM_TAREFAS;

    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){

    char txt[] = ".txt";
    char nomeArq[100];
    printf("Entre com o nome do arquivo: ");
    clearBuffer();
    fgets(nomeArq, 100, stdin);
    nomeArq[strcspn(nomeArq, "\n")] = '\0';
    strcat(nomeArq, txt);

    FILE *f = fopen(nomeArq, "w");
    if (f == NULL)
        return ABRIR;

    for (int i = 0; i < *pos; i++) {
        fprintf(f, "Prioridade:     %d", tarefas[i].prioridade);
        fprintf(f, "Categoria:       %s", tarefas[i].categoria);
        fprintf(f, "Descricao:       %s", tarefas[i].descricao);
    }

    // int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    // if (qtd == 0)
    //   return ESCREVER;

    // qtd = fwrite(pos, 1, sizeof(int), f);
    // if (qtd == 0)
    //   return ESCREVER;

    if (fclose(f))
        return FECHAR;
    printf("Salvo e exportado com sucesso!");
    return OK;
}

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

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
