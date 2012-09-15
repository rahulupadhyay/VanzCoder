/*
 * Lista.cpp
 *
 *  Created on: 10/09/2012
 *      Author: vanz
 */
#include "Lista.h"
using namespace std;

Lista::Lista() {
	tamanho = 0;
	noInicial = NULL;
}

NoLista* Lista::getNoInicial() {
	return noInicial;
}

void Lista::limpaLista() {
	delete noInicial;
	tamanho = 0;
}

bool Lista::isEmpty() {
	return tamanho == 0;
}

bool Lista::primeiraStringAntes(string s1, string s2) {
	return s1 <= s2;
}

void Lista::addLista(string valor) {
	NoLista * novoNo = new NoLista();
	novoNo->setProximoNo(NULL);
	novoNo->setValor(valor);
	if(isEmpty()){ /*Primeiro elemento da lista*/
		noInicial = novoNo;
	}else{
		NoLista * noAtual = noInicial;
		NoLista * noAnterior = NULL;
		while(noAtual != NULL){
			if(primeiraStringAntes(valor,noAtual->getValor())){
				if(noInicial == noAtual){
					novoNo->setProximoNo(noAtual);
					noInicial = novoNo;
					tamanho++;
					return;
				}else{
					novoNo->setProximoNo(noAtual);
					noAnterior->setProximoNo(novoNo);
					tamanho++;
					return;
				}

			}else{
				if(noAtual->getProximoNo() == NULL){
					noAtual->setProximoNo(novoNo);
					tamanho++;
					return;
				}
				noAnterior = noAtual;
				noAtual = noAtual->getProximoNo();
			}
		}


	}


}

int Lista::getTamanho() {
	return tamanho;
}

NoLista* Lista::getNo(int posicao) {
	if(posicao < tamanho){
		NoLista * noAtual = noInicial;
		int contador = 0;
		while(noAtual != NULL){
			if(contador == posicao){
				return noAtual;
			}
			noAtual = noAtual->getProximoNo();
			contador++;
		}
	}
	return NULL;
}
