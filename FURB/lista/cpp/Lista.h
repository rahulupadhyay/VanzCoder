/*
 * Lista.cpp
 *
 *  Created on: 10/09/2012
 *      Author: vanz
 */
#include<string>
#include"NoLista.h"
using namespace std;
class Lista{

private:
	int tamanho;
	NoLista *noInicial;
	bool primeiraStringAntes(string,string);
public:
		NoLista* getNoInicial();
		void limpaLista();
		bool isEmpty();
		void addLista(string valor);
		int getTamanho();
		NoLista* getNo(int posicao);
};

