#include "tarefas.h"
#include <stdio.h>
#include <string.h>


#define TAMANHO_CATEGORIA 100
#define TAMANHO_DESCRICAO 300

void clearBuffer();

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

ERROS listar(Tarefa tarefas[], int *pos) {
      if (*pos == 0)
          return SEM_TAREFAS;
      char categoria_desejada[100];
       clearBuffer();
          printf("Entre com a categoria desejada (deixe em branco para listar todas): ");
          // scanf(" %99[^\n]", categoria_desejada);
          fgets(categoria_desejada, 100, stdin);


          printf("Tarefas com a categoria '%s'", categoria_desejada);
              int encontrou_tarefa = 0;

              for (int i = 0; i < *pos; i++) {
                  if (strcmp(tarefas[i].categoria, categoria_desejada) == 0) {
                      printf("Pos: %d\t", i + 1);
                      printf("Prioridade: %d\t", tarefas[i].prioridade);
                      printf("Categoria: %s\t", tarefas[i].categoria);
                      printf("Descricao: %s\n", tarefas[i].descricao);
                      encontrou_tarefa = 1;
                  }
              }

              if (!encontrou_tarefa) {
                printf("Nenhuma tarefa encontrada com a categoria '%s'\n", categoria_desejada);
              }else{
                printf("---- listando todas as tarefas ---- \n");

                    for(int i=0; i<*pos; i++){
                      printf("Pos: %d\t", i+1);
                      printf("Prioridade: %d\t", tarefas[i].prioridade);
                      printf("Categoria: %s\t", tarefas[i].categoria);
                      printf("Descricao: %s\n", tarefas[i].descricao);
                    }
              }


              // se categoria desejada tiver vazio imprime isso
              //printf("---- listando todas as tarefas ---- \n");

              //     for(int i=0; i<*pos; i++){
              //       printf("Pos: %d\t", i+1);
              //       printf("Prioridade: %d\t", tarefas[i].prioridade);
              //       printf("Categoria: %s\t", tarefas[i].categoria);
              //       printf("Descricao: %s\n", tarefas[i].descricao);
              //     }

              // se categoria desejada tiver com um valor que nao possui na categoria 
              // retorno um printf com um aviso de que nao encontrou
     return OK;
  }



ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;
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
        fprintf(f, "Prioridade:     %d\n", tarefas[i].prioridade);
        fprintf(f, "Categoria:       %s\n", tarefas[i].categoria);
        fprintf(f, "Descricao:       %s\n\n", tarefas[i].descricao);
    }

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
