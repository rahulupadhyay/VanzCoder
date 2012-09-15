/*
 * Principal.cpp
 *
 *  Created on: 10/09/2012
 *      Author: vanz
 */

/*Implementação do trabalho de lista encadeada
 *Autor: José Guilherme Vanz
 * */
#include<iostream>
#include<string>
#include<vector>
#include"Lista.h"

using namespace std;

class Principal {
private:
	Lista lista;
	void getNomesCidades();
	void listarCidades();
	void limparLista();
	void stringsplit(string, string, vector<string>&);
public:
	Principal();
};

Principal::Principal() {
	getNomesCidades();
	listarCidades();
	limparLista();

}

void Principal::getNomesCidades() {
	cout << "Informe os nomes das cidades ( separados por \",\" ):" << endl;
	string entrada;
	cin >> entrada;
	vector<string> valores;
	stringsplit(entrada, ",", valores);
	cout << valores.size() << endl;
	for (int index = 0; index < valores.size(); index++) {
		lista.addLista(valores[index]);
	}
}

void Principal::stringsplit(string str, string delim, vector<string> &results) {
	int cutAt;
	while ((cutAt = str.find_first_of(delim)) != str.npos) {
		if (cutAt > 0) {
			results.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0) {
		results.push_back(str);
	}

}

void Principal::listarCidades() {
	cout << "INÍCIO DA LISTAGEM\n";
	for (int index = 0; index < lista.getTamanho(); index++) {
		cout << lista.getNo(index)->getValor() << endl;
	}
	cout << "FIM DA LISTAGEM" << endl;
}

void Principal::limparLista() {
	lista.limpaLista();
}

int main() {
	cout << "L1221C25 – José Guilherme Vanz" << endl;
	Principal principal;
}
