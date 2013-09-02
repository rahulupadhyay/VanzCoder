	
/**
 * Exercícios da disciplina de iOS
 * Aluno: José Guilherme Vanz
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototipos
bool ehSerieFibonacci(int numero);
bool is_perfect_square(int n);
int busca(int n, int * vector, int x);
int matriz_identidade(int * mat, int n);
void executaQuestaoFibonacci();
void executaQuestaoBuscaVetor();
void executaQuestaoMatrixIdentidade();
void printCabecalho();

using namespace std;

/*
 * Faça um programa completo (função main e inclusao dos arquivos de cabçalhos adequados) 
 * que teste se um número pertence a série de Fibonacci, lembrando que esta série é definida da seguinte forma:
 * 	termo1 = 1
 *	termo2 = 1
 *	termon = termon−1 + termon−2
 * O núumero a ser testado deve ser fornecido pelo usúario do programa. O programa deve
 * imprimir a mensagem “PERTENCE A SERIE” caso o número pertença a série, e “NAO PERTENCE A SERIE” caso contrário.
 */	
bool ehSerieFibonacci(int numero)
{
	float result = (5 * ( numero * numero)) + 4; 
	float result2 = (5 * ( numero * numero)) - 4; 

	if(is_perfect_square(result) | is_perfect_square(result2)){
		return true;
	}
	return false;
}

bool is_perfect_square(int n) {
	if (n < 0){
		return false;
	}
    	int root(round(sqrt(n)));
    	return n == root * root;
}

/*
 * Implemente a função busca, que recebe como parâmetro um vetor de números inteiros
 * (vet) de tamanho n e um valor x. A função deve retornar 1 se x pertence a esse vetor
 * e 0 caso contrário. Essa função deve obedecer o protótipo:
 *
 * 	int busca (int n, int * vet, int x);
 */
int busca(int n, int * vector, int x)
{
	for(int i = 0; i < n; i++){
		if(vector[i] == x){
			return 1;
		}
	}
	return 0;
}

/*
 * Implemente uma função que indique se uma matriz quadrada de números inteiros é uma
 * matriz identidade ou não. A função deve retornar 1 se a matriz for uma matriz identi-
 * dade, e 0 caso contrário. A funçao recebe como parâmetros a matriz de inteiros, usando
 * a representação de matrizes através de vetores simples, e um inteiro n, indicando a
 * dimensão da matriz. Essa função deve obedecer o protótipo:
 *
 * 	int matriz_identidade (int* mat, int n);
*/
int matriz_identidade(int * mat, int n)
{
	int tamanho = n * n;
	for(int i = 0; i < tamanho; i+=(n+1)){
		if(mat[i] != 1){
			return 0;
		}
	}
	return 1;
}

void executaQuestaoFibonacci()
{
	cout << "Informe um número: ";
	int numero;
	scanf("%d", &numero);
	if(ehSerieFibonacci(numero)){
		cout << "PERTENCE A SERIE FIBONACCI" << endl;
	}else{
		cout << "NÃO PERTENCE A SERIE FIBONACCI" << endl;
	}
	
}
void executaQuestaoBuscaVetor()
{

}

void executaQuestaoMatrixIdentidade()
{
	
}

int main( int argc, char** argv)
{
	printCabecalho();
	while(true){	
		int selecao = getchar();
	
		switch(selecao){
			case '1':
				executaQuestaoFibonacci();
				break;
			case '2':
				executaQuestaoBuscaVetor();
				break;
			case '3':
				executaQuestaoMatrixIdentidade();
				break;
			case '4': // finalizar
				return 0;
				break;
		}
	}
 
}

void printCabecalho()
{
	cout << string(300,'\n') << endl;
	cout << "Exercícios da disciplina de iOS." << endl;
	cout << "Aluno: José Guilherme Vanz" << endl;
	cout << endl << "Escolha uma opção:" << endl;
	cout << "1. Lista 1 - Exec 07" << endl; 
	cout << "2. Lista 1 - Exec 25" << endl; 
	cout << "3. Lista 2 - Exec 16" << endl;
	cout << "4. Finalizar" << endl;
}
