#include "tarefas.h"
#include <stdio.h>
#include <string.h>

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;


  int prioridade;
  printf("Entre com a prioridade (de 0 a 10): ");
  scanf("%d", &prioridade);
  if (prioridade < 1 || prioridade > 10) {
    printf("Prioridade inválida. A prioridade deve estar entre 0 e 10.\n");
    return PRIORIDADE_INVALIDA;
  }
    tarefas[*pos].prioridade = prioridade;

   
    clearBuffer();
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, CATEGORIA_MAX, stdin);
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, DESCRICAO_MAX, stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

  *pos = *pos + 1;

  return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
  // teste se existem tarefas
  if (*pos == 0)
    return SEM_TAREFAS;

  // verifica se a tarefa escolhida existe
  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
    tarefas[i].prioridade = tarefas[i + 1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
    strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
  }

  *pos = *pos - 1;

  return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
  if (*pos == 0)
    return SEM_TAREFAS;
  int co = 0;
  char categoria_acha[CATEGORIA_MAX];
  printf("Entre com a categoria da tarefa a ser listada. \n");
  printf("(para listar todas tarefas deixe esse espaço em branco): ");
  
  clearBuffer();
  fgets(categoria_acha, CATEGORIA_MAX, stdin);
  categoria_acha[strcspn(categoria_acha, "\n")] = '\0';
  
  for (int i = 0; i < *pos; i++) {
    if(!strcmp(categoria_acha,tarefas[i].categoria)  || !strcmp(categoria_acha,"\0") ){
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
      co++;
    }
  }
  if(co==0){
    printf("Nenhuma tarefa com essa categoria encontrada. \n");
  }

  return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
