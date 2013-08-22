	
/**
 * Exercícios da disciplina de iOS
 * Aluno: José Guilherme Vanz
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Prototipos
bool ehSerieFibonacci(int numero);
int busca(int n, int * vector, int x);
char * matriz_identidade(int * mat, int n);
void executaQuestaoFibonacci();
void executaQuestaoBuscaVetor();
void executaQuestaoMatrixIdentidade();

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

}

/*
 * Implemente uma funçã que indique se uma matriz quadrada de números inteiros é uma
 * matriz identidade ou não. A função deve retornar 1 se a matriz for uma matriz identi-
 * dade, e 0 caso contrário. A funçao recebe como parâmetros a matriz de inteiros, usando
 * a representação de matrizes através de vetores simples, e um inteiro n, indicando a
 * dimensão da matriz. Essa função deve obedecer o protótipo:
 *
 * 	int matriz_identidade (int* mat, int n);
*/
char* matriz_identidade(int * mat, int n)
{

}

void executaQuestaoFibonacci()
{

}
void executaQuestaoBuscaVetor()
{

}

void executaQuestaoMatrixIdentidade()
{
	cout << "Indique a dimensão da matrix quadrada: " << endl;
	char charDimensao = fgetc(stdin);
	int dimensao = atoi(&charDimensao);

	cout << "Dimensão eh = " << dimensao << endl;
}

int main( int argc, char** argv)
{
	cout << string(300,'\n') << endl;	
	cout << "Exercícios da disciplina de iOS." << endl;
	cout << "Aluno: José Guilherme Vanz" << endl;
	cout << endl << "Escolha uma opção:" << endl;
	cout << "1. Lista 1 - Exec 07" << endl; 
	cout << "2. Lista 1 - Exec 25" << endl; 
	cout << "3. Lista 2 - Exec 16" << endl;
	cout << "4. Finalizar" << endl;

	while(true){	
		int selecao = getchar();
	
		switch(selecao){
			case '1':
				break;
			case '2':
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
