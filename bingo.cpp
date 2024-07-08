/*  
Trabalho de Computação para Engenharia
Projeto Escolhido - Bingo
Autores: 
1. Arthur Augusto Frasson Ramos
2. Mateus
3. Pedro Henrique Dias Avelar
4. Vinicius Magao de Oliveira

Última compilação: 08/07/2024
*/


//headers utilizados
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

//Constantes para definir o intervalo de numeros das pedras a serem sorteadas e a quantidade de pedras
const int MENOR_PEDRA = 1;
const int MAIOR_PEDRA = 60;
const int NUM_PEDRAS = MAIOR_PEDRA - MENOR_PEDRA + 1;

//Struct contendo os dados para cada jogador - a cartela de bingo, o nome do jogador, e uma flag para determinar se o jogador ganhou o bingo
struct jogador_bingo {
	int cartela[5][5];
	string nome_jogador;
	bool ganhou;
};

//#1 PREENCHE: cartela
void preenche_cartela(jogador_bingo& jogador);
//#2 SORTEIA: gera um numero aleatorio
int sorteia_numero();
//#3 VERIFICA: numero na cartela
bool checa_numero_cartela_repetido(jogador_bingo& jogador, int numero);
//#3 IMPRIMI: cartela
void imprime_cartela(jogador_bingo& jogador, int n_sorteados[], int n_pedras);
//#5 VERIFICA: numero sorteado
bool checa_numero_sorteado_repetido(int n_sorteados[], int n_pedras, int numero);
//#6 IMPRIMI: imprimi os numeros sorteados
void imprime_numeros_sorteados(int n_sorteados[], int n_pedras);
//#7 VERIFICA: verifica linha da cartela
void avalia_linha(jogador_bingo& jogador, int linha, int n_pedras, int n_sorteados[]);
//#8 VERIFICA: verifica coluna da cartela
void avalia_coluna(jogador_bingo& jogador, int coluna, int n_pedras, int n_sorteados[]);

//Array para armazenar os numeros préviamente sorteados, variável para armazenar o numero sorteado e flag para determinar se o número sorteado é válido (não é repetido)
int numeros_sorteados[NUM_PEDRAS];
int numero_sorteado;
bool numero_sorteado_valido = false;

//Começo do programa
int main() {
	// Declara vetor de jogadores e variável para armazenar a quantidade de jogadores
	vector<jogador_bingo> jogadores;
	int num_jogadores = 0;

	// Abertura do jogo
	cout << "\n>> ---------------------------------------------- <<\n";
	cout << "\nBem Vindo(a) ao Bingo da Computacao para Engenharia!\n";
	cout << "\n>> ---------------------------------------------- <<\n" << endl;
	cout << "Para comecar, precisamos que cada jogador informe seus dados e preencha sua cartela." << endl;

	// Solicita o número de jogadores
	while (num_jogadores < 1){
		cout << "\nDigite o numero de jogadores: ";
		cin >> num_jogadores;
		if (num_jogadores < 1){
			cout << "Digite um numero valido! O numero de jogadores precisa ser maior ou igual a 1.";
		}
	}

	// Redimensiona o vetor de jogadores com base no número fornecido
	jogadores.resize(num_jogadores);

	// Preenche os dados de cada jogador
	for (int i = 0; i < num_jogadores; i++) {
    	cout << "\nPreencha os dados do jogador " << i + 1 << "..." << endl;
    	preenche_cartela(jogadores[i]);
	}

	// Imprime as cartelas de cada jogador
	for (int i = 0; i < num_jogadores; i++) {
    	imprime_cartela(jogadores[i], numeros_sorteados, 1);
	}

	// Para cada pedra sorteada, serao feitas iteracoes para avaliar se houve vencedor
	for (int i = 0; i < NUM_PEDRAS; i++) {
    	cout << "\nComecando o sorteio da " << i + 1 << "a pedra!" << endl;
    	numero_sorteado_valido = false;

    	// Loop para garantir que o numero sorteado nao seja repetido
    	while (numero_sorteado_valido == false) {
        	//#2 SORTEIA: sorteia um numero aleatorio
        	numero_sorteado = sorteia_numero();
        	if (checa_numero_sorteado_repetido(numeros_sorteados, i, numero_sorteado) == false) {
            	cout << "\nO " << i + 1 << "o numero sorteado eh: " << numero_sorteado << "!!!" << endl;
            	numero_sorteado_valido = true;
            	numeros_sorteados[i] = numero_sorteado;
            	cout << "--------------------------------\n";
            	cout << "\nNumeros sorteados ate o momento:\n" << endl;
            	//#6 IMPRIMI: imprimi os numeros sorteados
            	imprime_numeros_sorteados(numeros_sorteados, i + 1);
            	cout << "--------------------------------\n";
        	}
    	}

    	// Cinco iteracoes para avaliar as 5 linhas / 5 colunas das cartelas dos jogadores
    	for (int j = 0; j < 5; j++) {
        	for (int k = 0; k < num_jogadores; k++) {
            	avalia_linha(jogadores[k], j, i, numeros_sorteados);
            	avalia_coluna(jogadores[k], j, i, numeros_sorteados);
        	}
    	}

    	// Verifica se algum jogador ganhou
    	for (int k = 0; k < num_jogadores; k++) {
        	if (jogadores[k].ganhou == true) {
            	cout << "\n!!! BINGO PARA O JOGADOR(A) !!!\n\n\t>>> " << jogadores[k].nome_jogador << " <<<" << endl;
            	imprime_cartela(jogadores[k], numeros_sorteados, i);
            	return 0;
        	}
    	}		
		system("pause");
	}
	return 0;
}

//#1 PREENCHE: funcao para preencher o nome do jogador e os numeros da cartela
void preenche_cartela(jogador_bingo& jogador) {
	bool numero_valido = false;
	int numero_digitado = 0;

	// Inicializacao da cartela
	for (int i = 0; i < 5; i++) {
    	for (int j = 0; j < 5; j++) {
        	jogador.cartela[i][j] = 0;
    	}
	}

	// Nome do jogador
	cout << "Digite o seu nome: ";
	cin >> jogador.nome_jogador;
	jogador.ganhou = false;

	//variaveis para determinar se a cartela sera preenchida manualmente ou automaticamente
	char preenchimento_automatico = 's';
	bool flag_preenchimento_automatico_ok = false;

	//loop para garantir que a opcao de preenchimento automatico seja válida
	while (flag_preenchimento_automatico_ok == false){
		cout << "Deseja preencher a cartela automaticamente? (s/n)" << endl;
		cin >> preenchimento_automatico;
		if (preenchimento_automatico == 's' || preenchimento_automatico == 'n'){
			flag_preenchimento_automatico_ok = true;
		} else {
			cout << "Digite uma opcao valida por favor." << endl;
		}
	}

	
	if (preenchimento_automatico == 's' || preenchimento_automatico == 'S'){
		// Preenchimento da cartela AUTOMATICO
		for (int i = 0; i < 5; i++) {
    		for (int j = 0; j < 5; j++) {
    	    	numero_valido = false;
    	    	while (numero_valido == false) {
    	        	//#2 SORTEIA: sorteia um numero aleatorio
    	        	numero_digitado = sorteia_numero();
    	        	//#3 VERIFICA: verifica se um numero existe na cartela
    	        	if (checa_numero_cartela_repetido(jogador, numero_digitado) == true || numero_digitado > MAIOR_PEDRA || numero_digitado < MENOR_PEDRA) {
    	            	// Nao faz nada, apenas volta pro inicio do while
    	        	} else {
    	            	jogador.cartela[i][j] = numero_digitado;
    	            	numero_valido = true;
    	        	}
    	    	}
    		}
		}
	} else {	
		//preenchimento da cartela MANUAL
		for (int i = 0; i < 5; i++){
    		for (int j = 0; j < 5; j++){
    	    	numero_valido = false;
    	    	while (numero_valido == false){
   				 std::cout << "Digite o numero da posicao [" << i << "] [" << j << "]: ";
    	        	std::cin >> numero_digitado;
    	        	//#3 VERIFICA: verifica se um numero existe na cartela
    	        	if (checa_numero_cartela_repetido (jogador, numero_digitado) == true){
    	            	std::cout << "\n>> ATENCAO! <<\n" << std::endl;
   					 std::cout << "Numero repetido!\nDigite outro por favor...\n" << std::endl;
    	            	std::cout << "Sua cartela ate o momento:" << std::endl;
    	            	imprime_cartela(jogador, numeros_sorteados, 1);
    	        	} else if (numero_digitado > MAIOR_PEDRA || numero_digitado < MENOR_PEDRA) {
    	            	std::cout << "\n>> ATENCAO! <<\n" << std::endl;
    	            	std::cout << "Numero fora do aceitado! Precisa estar entre " << MENOR_PEDRA << " e " << MAIOR_PEDRA << ".\nDigite outro por favor...\n" << std::endl;
    	        	} else {
    	            	jogador.cartela[i][j] = numero_digitado;
    	            	numero_valido = true;
    	        	}
    	    	}
    		}
		}
	}
    imprime_cartela(jogador, numeros_sorteados, 1);

}

//#2 SORTEIA: gera um numero aleatorio
int sorteia_numero() {
	return MENOR_PEDRA + (rand() % NUM_PEDRAS);
}

//#3 VERIFICA: verifica se um determinado numero existe na cartela; se sim retorna true, se nao retorna false
bool checa_numero_cartela_repetido(jogador_bingo& jogador, int numero) {
	for (int i = 0; i < 5; i++) {
    	for (int j = 0; j < 5; j++) {
        	if (jogador.cartela[i][j] == numero) {
            	return true;
        	}
    	}
	}
	return false;
}

//#4 IMPRIMI: imprime a cartela do jogador
void imprime_cartela(jogador_bingo& jogador, int n_sorteados[], int n_pedras) {
	cout << "\nCartela gerada para: " << jogador.nome_jogador << "\n" << endl;
	for (int i = 0; i < 5; i++) {
    	cout << "|";
    	for (int j = 0; j < 5; j++) {
        	if (checa_numero_sorteado_repetido(n_sorteados, n_pedras, jogador.cartela[i][j]) == true) {
            	cout << "*";
            	// Acrescenta um 0 a esquerda para numeros menores que 10
            	if (jogador.cartela[i][j] < 10) {
                	cout << "0" << jogador.cartela[i][j] << "|";
            	} else {
                	cout << jogador.cartela[i][j] << "|";
            	}
        	}
        	// Acrescenta um 0 a esquerda para numeros menores que 10
        	else if (jogador.cartela[i][j] < 10) {
            	cout << " 0" << jogador.cartela[i][j] << "|";
        	} else {
            	cout << " " << jogador.cartela[i][j] << "|";
        	}
    	}
    	cout << endl;
	}
}

//#5 VERIFICA: verifica se o numero ja foi sorteado; se sim retorna true, se nao retorna false
bool checa_numero_sorteado_repetido(int n_sorteados[], int n_pedras, int numero) {
	for (int i = 0; i < n_pedras; i++) {
    	if (n_sorteados[i] == numero) {
        	return true;
    	}
	}
	return false;
}

//#6 IMPRIMI: imprimi os numeros sorteados
void imprime_numeros_sorteados(int n_sorteados[], int n_pedras) {
	for (int i = 0; i < n_pedras; i++) {
    	if (n_sorteados[i] < 10) {
        	cout << "0" << n_sorteados[i] << " ";
    	} else {
        	cout << n_sorteados[i] << " ";
    	}
	}
	cout << endl;
}

//#7 VERIFICA: verifica se a linha da cartela contem todos os numeros sorteados
void avalia_linha(jogador_bingo& jogador, int linha, int n_pedras, int n_sorteados[]) {
	int cont = 0;
	for (int j = 0; j < 5; j++) {
    	if (checa_numero_sorteado_repetido(n_sorteados, n_pedras, jogador.cartela[linha][j]) == true) {
        	cont++;
    	}
	}
	if (cont == 5) {
    	jogador.ganhou = true;
	}
}

//#8 VERIFICA: verifica se a coluna da cartela contem todos os numeros sorteados
void avalia_coluna(jogador_bingo& jogador, int coluna, int n_pedras, int n_sorteados[]) {
	int cont = 0;
	for (int i = 0; i < 5; i++) {
    	if (checa_numero_sorteado_repetido(n_sorteados, n_pedras, jogador.cartela[i][coluna]) == true) {
        	cont++;
    	}
	}
	if (cont == 5) {
    	jogador.ganhou = true;
	}
}
