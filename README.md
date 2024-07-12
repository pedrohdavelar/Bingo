# Trabalho Final de Computação para Engenharia: Bingo 

## Descrição

O programa "Bingo.exe" oferece uma experiência digital do clássico jogo de sorteio Bingo. Desenvolvido como trabalho final da disciplina de Computação para Engenharia, este software proporciona uma interface intuitiva e funcionalidades que replicam a dinâmica do jogo tradicional.

## Funcionalidades

### Menu Principal

O programa apresenta três opções principais:

1. Novo Jogo
2. Lista de Vencedores
3. Sair

### Novo Jogo

Ao iniciar um novo jogo, o usuário deve:

1. Informar o número de participantes.
2. Para cada participante:
   - Fornecer o nome.
   - Escolher o modo de preenchimento da cartela (automático ou manual).
3. Após o preenchimento, cada cartela é exibida para registro (cópia ou captura de tela).

O sorteio das pedras começa em seguida. O programa verifica automaticamente, após cada sorteio, se algum jogador completou uma linha ou coluna, caracterizando o Bingo. Ao identificar um vencedor, o programa:

- Declara o vencedor.
- Salva o nome do vencedor e sua pontuação (número de pedras sorteadas até o Bingo) no arquivo "vencedores.txt".

### Lista de Vencedores

Esta opção:

1. Lê o arquivo "vencedores.txt".
2. Ordena os vencedores por pontuação (ordem crescente).
3. Exibe uma lista formatada dos vencedores.

### Sair

Encerra a execução do programa.

