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
    fgets(tarefas[*pos].categoria, MAX_CATEGORIA, stdin);
    clearBuffer();
    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, MAX_DESCRICAO, stdin);
    clearBuffer();

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
