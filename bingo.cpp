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
#include <fstream>

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
//#9 Lista os vencedores do arquivo vencedores.txt
void imprime_vencedores ();
//#10 Imprime todas as cartelas
void imprime_todas_cartelas ();


//Array para armazenar os numeros préviamente sorteados, variável para armazenar o numero sorteado e flag para determinar se o número sorteado é válido (não é repetido)
int numeros_sorteados[NUM_PEDRAS];
int numero_sorteado;
bool numero_sorteado_valido = false;

//Começo do programa
int main() {
	srand((unsigned) time(NULL)); // gerador de semente aleatoria
	// Declara vetor de jogadores e variável para armazenar a quantidade de jogadores
	vector<jogador_bingo> jogadores;
	int num_jogadores = 0;
	int menu;
	bool teve_ganhador = false;

	// Abertura do jogo
	cout << "\n>> ---------------------------------------------- <<\n";
	cout << "\nBem Vindo(a) ao Bingo da Computacao para Engenharia!\n";
	cout << "\n>> ---------------------------------------------- <<\n" << endl;
	
	//loop principal
	while(true){
		cout << "Opcoes: (1)Novo Jogo (2)Lista de Vencedores (3)Sair" << endl;
		cin >> menu;
		switch (menu){
			case 1:
				
				//limpeza do array contendo as pedras sorteadas
				for (int x = 0; x < NUM_PEDRAS; x++){
					numeros_sorteados[x] = 0;
				}
				
				system("cls");
				teve_ganhador = false;
				cout << "Para comecar, precisamos que cada jogador informe seus dados e preencha sua cartela." << endl;

				num_jogadores = 0; //inicializacao desta variavel para cada loop

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
				cout << "Todas as cartelas foram preenchidas!" << endl;
				system("pause");
				system("cls");

				cout << "Ok! Aqui esta a cartela dos participantes:" << endl;
				// Imprime as cartelas de cada jogador
				for (int i = 0; i < num_jogadores; i++) {
    				imprime_cartela(jogadores[i], numeros_sorteados, 1);
				}
				cout << "Pronto? O jogo ja vai comecar!" << endl;
				system("pause");
				system("cls");
				
				while(teve_ganhador == false){
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
    				        	avalia_linha(jogadores[k], j, i+1, numeros_sorteados);
    				        	avalia_coluna(jogadores[k], j, i+1, numeros_sorteados);
    				    	}
    					}

    					// Verifica se algum jogador ganhou
    					for (int k = 0; k < num_jogadores; k++) {
    				    	if (jogadores[k].ganhou == true) {
    				        	cout << "\n!!! BINGO PARA O JOGADOR(A) !!!\n\n\t>>> " << jogadores[k].nome_jogador << " <<<" << endl;
    				        	imprime_cartela(jogadores[k], numeros_sorteados, i+1);
								teve_ganhador = true;
								fstream vencedores;
								vencedores.open("vencedores.txt", ios::app);
								if (!vencedores){
									cout << "Erro critico! Falha ao abrir o arquivo vencedores.txt. Encerrando o programa...";
									return 1;
								}
								vencedores << jogadores[k].nome_jogador << " " << i+1 << endl;
								vencedores.close();
								system("pause");
								system("cls");
    				    	}
    					}
						if (teve_ganhador == false){
							for (jogador_bingo a : jogadores){             //iteracao do vetor jogadores para impressao de todas as cartelas
								imprime_cartela(a, numeros_sorteados, i+1);
							}		
							system("pause");
							system("cls");
						}
					if (teve_ganhador == true){
						break;
						}
					}
				}
				break;
			case 2:
				imprime_vencedores();
				system("pause");
				system("cls");
				break;
			case 3:
				system("cls");
				cout << "Muito obrigado por jogar! Ateh a proxima...";
				return 0;
			default:
				cout << "Opcao invalida. Repita por favor." << endl;
		}
	}
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
	cout << "\nCartela do jogador: " << jogador.nome_jogador << "\n" << endl;
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

//#9 Lista os vencedores do arquivo vencedores.txt
void imprime_vencedores(){
	system("cls");
	ifstream vencedores("vencedores.txt");  //abertura do arquivo vencedores.txt e teste para ver se o arquivo foi aberto com sucesso
	if (!vencedores){
		cout << "Erro ao abrir a lista dos vencedores... Você jah jogou alguma rodada? Voltando ao menu..." << endl;
		return;
	}

	// struct para montagem do vetor
	struct vencedor{
		string nome;
		int pontos;
	};

	vencedor v;

	// vetor para armazenar a lista dos vencedores
	vector<vencedor> lista_vencedores;
	while (vencedores >> v.nome >> v.pontos){
		lista_vencedores.push_back(v);
	}
	//apos carregar o vetor, fechamento do arquivo
	vencedores.close();

	//bubble sort para ordenar os vencedores por ordem de menos pedras para conseguir bingo
	bool numero_foi_trocado = false;
	do {
		numero_foi_trocado = false;
		for (long long unsigned int i = 0; i < (lista_vencedores.size() - 1 ); i++){
			if (lista_vencedores[i].pontos > lista_vencedores[i+1].pontos){
				swap(lista_vencedores[i], lista_vencedores[i+1]);
				numero_foi_trocado = true;
			}
		}
	} while (numero_foi_trocado == true);

	//impressao da lista ordenada dos vencedores
	cout << "Ranking dos Vencedores!!!" << endl;
	for (vencedor a : lista_vencedores){
		int p = 1;
		cout << "#" << p << ": " << a.nome << " - " << a.pontos << " pontos" << endl;
		p++;
	}
}

