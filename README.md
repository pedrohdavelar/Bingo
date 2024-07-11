# Bingo
 Trabalho Final de Computação para Engenharia

O programa Bingo.exe replica o famoso jogo de sorteio Bingo.

O menu do programa apresenta 3 opções: Novo jogo, Lista de Vencedores e Sair.

A opção Novo Jogo inicia o jogo.
Inicialmente, o usuário precisa informar o número de participantes.

Em seguida, deve ser informado o nome de cada participante e o modo de 
preenchimento de sua cartela - automático ou manual.

Apos o preenchimento de cada cartela, é exibida a cartelha preenchida, 
de modo que possa ser copiada ou gerada um print de cada cartela.

Inicia-se então o sorteio das pedras. Após o sorteio de cada pedra, o 
programa irá verificar, cartela por cartela, se houve alguma linha ou 
coluna preenchida.
Caso sim, o programa irá então declarar o vencedor e salvar seu nome e sua 
quantidade de pontos no arquivo vencedores.txt. A quantidade de pontos é
a quantidade de pedras sorteadas que foram necessárias para o jogador conseguir
o Bingo.

A opção Lista de Vencedores faz a leitura do arquivo vencedores.txt, seguida da 
ordenação dos vencedores em ordem crescente de pontos e, por fim, a impressão formatada
da lista dos vencedores.

A opção Sair encerra o programa.
