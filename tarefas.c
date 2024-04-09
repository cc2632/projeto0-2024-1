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
  if (*pos == 0){
    return SEM_TAREFAS;
  }
    
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
    return NAO_ENCONTRADO;
  }else{
    Tarefa lista[co];
    int simNao;
    char nome[DESCRICAO_MAX+3];

    printf("Deseja salvar essa lista em um arquivo de texto?(1 = Sim/2 = Nao) \n");
    scanf("%d", &simNao);
    if(simNao==1){
      
      clearBuffer();
      printf("Entre com o nome do arquivo: ");
      fgets(nome, DESCRICAO_MAX, stdin);
      nome[strcspn(nome,"\n")] = '.';
      strcat(nome,"txt");
      FILE *f = fopen(nome, "w");
      if (f == NULL)
        return CRIAR;

      for (int i = 0; i < *pos; i++) {
        if(!strcmp(categoria_acha,tarefas[i].categoria)  || !strcmp(categoria_acha,"\0") ){
          fprintf(f,"Pos: %d\t", i + 1);
          fprintf(f,"Prioridade: %d\t", tarefas[i].prioridade);
          fprintf(f,"Categoria: %s\t", tarefas[i].categoria);
          fprintf(f,"Descricao: %s\n", tarefas[i].descricao);
          co++;
        }
      }
      
      if (fclose(f))
        return FECHAR;

      printf("%s criado com sucesso! \n",nome);
      
  }
  return OK;
}
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  char filename[300];
  printf("Selecione o arquivo para salvar as tarefas! (deixe vazio para arquivo padrão) \n");
  clearBuffer();
  fgets(filename,300,stdin);
  if(strlen(filename)==0){
    strcpy(filename,"tarefas.");
  }
  filename[strcspn(filename, "\n")] = '.';
  strcat(filename,"bin");
  FILE *f = fopen(filename, "wb");
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
  char filename[300];
  printf("Selecione o arquivo para leitura!(deixe vazio para arquivo padrão) \n");
    fgets(filename,300,stdin);
  if(strlen(filename)==0){
    strcpy(filename,"tarefas.");
  }
    filename[strcspn(filename, "\n")] = '.';
    strcat(filename,"bin");
  FILE *f = fopen(filename, "rb");
  if (f == NULL){
    return ABRIR;
  }
    
  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0){
    return LER;
  }

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0){
    return LER;
  }

  if (fclose(f)){
    return FECHAR;
  }

  return OK;
}

void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
  
void printErro(ERROS e){
  switch(e){
    case 0:
    printf("OK\n");
    break;
      case 1:
    printf("Maximo de tarefas atingido!\n");
    break;
        case 2:
    printf("Sem tarefas no arquivo!\n");
    break;
          case 3:
    printf("Tarefa não encontrada!\n");
    break;
            case 4:
    printf("Erro ao abrir o arquivo!\n");
    break;
              case 5:
    printf("Erro ao fechar o arquivo!\n");
    break;
                case 6:
    printf("Erro ao escrever no arquivo!\n");
    break;
                  case 7:
    printf("Erro ao ler o arquivo!\n");
    break;
                    case 8:
    printf("Prioridade inserida invalida!\n");
    break;
                      case 9:
    printf("Prioridade inserida invalida!\n");
    break;
    default:
    printf("Erro desconhecido!\n");
  }
}
