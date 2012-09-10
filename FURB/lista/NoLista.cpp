/*
 * NoLista.cpp
 *
 *  Created on: 10/09/2012
 *      Author: vanz
 */

#include "NoLista.h"

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

NoLista NoLista::getProximoNo() {
	return proximoNo;
}
