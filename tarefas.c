#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    do {
    printf("Entre com a prioridade: ");
    scanf("%d", &tarefas[*pos].prioridade);
    clearBuffer();
  } while (tarefas[*pos].prioridade < 1 || tarefas[*pos].prioridade > 10);
  
    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, 100, stdin);
    clearBuffer();
    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, 300, stdin);
    clearBuffer();

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

    clearBuffer();
    char list_categoria[100]; // Declarando a variável pela qual será filtrada a lista
    printf("Entre com a categoria pela qual deseja listar: "); // Pedindo para o usuário a categoria que ele deseja filtrar
    fgets(list_categoria, 100, stdin); // Lendo a categoria
    clearBuffer(); // Limpando o buffer do teclado

    if(strcmp(list_categoria, "\n") == 0) {// Comparando o que o usuário escolheu com o \n
        for (int i = 0; i < *pos; i++) { // Loop para percorrer todas as tarefas
            printf("Pos: %d\t", i + 1); // Exibindo a posição da tarefa
            printf("Prioridade: %d\t", tarefas[i].prioridade); // Exibindo a prioridade da tarefa
            printf("Categoria: %s\t", tarefas[i].categoria); // Exibindo a categoria da tarefa
            printf("Descricao: %s\n", tarefas[i].descricao); // Exibindo a descrição da tarefa
        }
    } else { // Caso contrário, o usuário digitou algo
        int categoria_existe = 0; // Declarando a variável que será usada para verificar se a categoria já existe
        for (int i = 0; i < *pos; i++) { // Loop para percorrer todas as tarefas
            if (strcmp(list_categoria, tarefas[i].categoria) == 0) { // Comparando se alguma categoria das tarefas é igual a que o usuário digitou
                categoria_existe = categoria_existe + 1; // Se a categoria existir, a variável categoria_existe recebe +1
            }
        }
    
        if (categoria_existe == 0){ // Se a variável categoria_existe for igual a 0, significa que a categoria que o usuário digitou não existe
            printf("Não existe essa categoria."); // Exibindo mensagem de que não existe a categoria para o usuário
        } else { // Caso contrário, a categoria que o usuário digitou existe
            for (int i = 0; i < *pos; i++) { // Loop para percorrer todas as tarefas
                if (strcmp(list_categoria, tarefas[i].categoria) == 0) { // Filtrando apenas as tarefas que possuem a categoria que o usuário digitou
                    printf("Pos: %d\t", i + 1); // Exibindo a posição da tarefa
                    printf("Prioridade: %d\t", tarefas[i].prioridade); // Exibindo a prioridade da tarefa
                    printf("Categoria: %s\t", tarefas[i].categoria); // Exibindo a categoria da tarefa
                    printf("Descricao: %s\n", tarefas[i].descricao); // Exiibindo a descrição da tarefa
                }
            }
        }
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
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
