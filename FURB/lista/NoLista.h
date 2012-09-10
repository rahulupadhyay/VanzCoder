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
	void setValor(string);
	void setProximoNo(NoLista*);
	string getValor();
	NoLista getProximoNo();
};
