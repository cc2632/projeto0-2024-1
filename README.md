# Projeto 2 - Vespertino (CC2632)

## Objetivo

Gerenciador de tarefas permite criar, deletar e listar tarefas.

Cada tarefa possui uma prioridade, uma descrição e uma categoria, sendo que o progama permite armazenar até 100 tarefas em um arquivo binário.

## Compilação e execução

Para a compilação é necessário ter um compilador de C com as bibliotecas stdio.h e string.h.
...
Para compilar e nomear o arquivo
...
gcc *.c -o tarefas.out
...

Para a execução do arquivo
...
./tarefas.out
...

## Arquivos necessários
O progama salva as tarefas cadastradas no arquivo 'tarefas', um arquivo binário, que po justamente ser binário, não é lido facilmente e caso compartilhado não terá o codigo explicito.