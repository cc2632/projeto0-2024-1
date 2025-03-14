# projeto0-2024-1

Este projeto foi desenvolvido em sala no primeiro semestre de 2024 e será usado como base para outras atividades da disciplina.

# Bugs para correção e melhorias

1. Os valores de categoria e descrição estão com quebra de linha no final da string. Adicione o código necessário para que esta quebra de linha não seja armazenada
2. O valor da prioridade não está limitado entre 1 e 10
3. Os erros não foram tratados na função main
4. Os tamanhos da categoria e descrição na função de criar tarefas e na descrição do struct estão com os valores definidos, mas não usam uma variável ou parâmetro para isso. Use o #define para mudar estes valores
5. Altere o README.md para descriver melhor a forma como o programa funciona

## Funcionalidades para implementar

1. Altere a função listar para pedir que o usuário a categoria que ele deseja listar:
    - Se o usuário escolher uma categoria existente, imprima as tarefas encontradas;
    - Se a categoria não existir, avise que nenhuma tarefa foi encontrada;
    - Se o usuário deixar a categoria vazia, exiba todas as tarefas;
2. Implemente uma forma de exportar as tarefas para um arquivo de texto simples em que cada tarefa deve aparecer em uma linha do arquivo. O usuário deve conseguir usar as mesmas opções que o item anterior e pode escolher o nome do arquivo texto que será gerado  
3. Altere o programa para deixar o usuário carregar e salvar o arquivo binário com as tarefas.
