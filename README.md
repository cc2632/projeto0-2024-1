Projeto de C -> Resumo de como o programa funciona
Estruturas e Enumerações:

A estrutura Tarefa define os atributos de uma tarefa, incluindo sua prioridade, descrição e categoria. A enumeração ERROS lista os possíveis erros que podem ocorrer durante a execução do programa.

Declarações de Funções: São declaradas as funções que manipulam as tarefas, como criar, deletar, listar, salvar e carregar. Cada função recebe um array de tarefas e a posição atual no array como argumentos e retorna um código de erro.

Implementações das Funções: A função criar solicita ao usuário que insira os detalhes de uma nova tarefa, como prioridade, categoria e descrição. A função deletar permite ao usuário remover uma tarefa existente com base na posição no array. A função listar exibe todas as tarefas armazenadas, mostrando sua posição, prioridade, categoria e descrição. A função salvar grava as tarefas e a posição atual no array em um arquivo binário chamado "tarefas.bin". A função carregar lê as tarefas e a posição atual do arquivo binário "tarefas.bin" para restaurar o estado anterior.

Função Principal (main): A função main inicializa um array de ponteiros para funções (fs) que representam as operações disponíveis. Carrega as tarefas salvas no início da execução usando a função carregar. Exibe um menu para o usuário selecionar uma operação, como criar, deletar, listar tarefas ou sair do programa. Executa a operação escolhida pelo usuário e lida com quaisquer erros que possam ocorrer. Salva as tarefas de volta no arquivo binário antes de encerrar o programa. Este código permite ao usuário criar, deletar, listar e salvar tarefas, mantendo o estado das tarefas entre as execuções por meio de um arquivo binário.
