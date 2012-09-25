/*
 * NoLista.h
 *
 *  Created on: 10/09/2012
 *      Author: vanz
 */

#include<string>
using namespace std;

class NoLista {
private:
	string valor;
	NoLista* proximoNo;
public:
	NoLista();
	void setValor(string);
	void setProximoNo(NoLista*);
	string getValor();
	NoLista* getProximoNo();
};


NoLista::NoLista() {
	valor = "";
	proximoNo = NULL;
}

void NoLista::setValor(string novoValor) {
	valor = novoValor;
}

void NoLista::setProximoNo(NoLista* proximo) {
	proximoNo = proximo;
}

string NoLista::getValor() {
	return valor;
}

NoLista* NoLista::getProximoNo() {
	return proximoNo;
}
