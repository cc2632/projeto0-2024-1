#define TOTAL 100
#define CATEGORIA_MAX 100
#define DESCRICAO_MAX 300

typedef struct {
    int prioridade;
    char descricao[DESCRICAO_MAX];
    char categoria[CATEGORIA_MAX];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER, PRIORIDADE_INVALIDA,CRIAR} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);

void clearBuffer();
void printErro(ERROS e);