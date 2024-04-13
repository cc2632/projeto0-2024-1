#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

       printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, sizeof(tarefas[*pos].categoria), stdin);
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0'; // Remove a quebra de linha

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, sizeof(tarefas[*pos].descricao), stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0'; // Remove a quebra de linha

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
        tarefas[i].prioridade, tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos){

    int Dado;
    printf("Entre com a categoria: ");
    scanf("%d",&Dado);


    for(int i = 0; i < *pos; i++) {
        if(tarefas[i].categoria == Dado) {
            printf("Pos: %d\t", i+1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
            return OK;
            }
        else if(*pos == 0)
            printf("Não a categorias registradas com essa especificação \n");
            return SEM_TAREFAS;
        }   

    
    for(int i=0; i<*pos; i++){
        printf("Pos: %d\t", i+1);
        printf("Prioridade: %d\t", tarefas[i].prioridade);
        printf("Categoria: %s\t", tarefas[i].categoria);
        printf("Descricao: %s\n", tarefas[i].descricao);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int pos, int tamanho){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos, int tamanho){
  FILE *f = fopen("tarefas", "rb");
  if (f == NULL)
    return ABRIR;

  int i = fread(tarefas, tamanho, sizeof(Tarefa), f);
  if(i <= 0)
    return LER;

  i = fread(pos, 1, sizeof(int), f);
  if(i <= 0)
    return LER;
  
  i = fclose(f);
  if(i == 0)
    return FECHAR;
  
  return OK;

}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
