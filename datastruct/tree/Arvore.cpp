#include "Arvore.h"
#include <string>
#include <fstream>
#include <iostream>

	
NoArvore::NoArvore(string info)
{
	this->info = info;
	this->esq = NULL;
	this->dir = NULL;
}

NoArvore* NoArvore::getNoEsquerda()
{
	return this->esq;
}

NoArvore* NoArvore::getNoDireita()
{
	return this->dir;
}

void NoArvore::setNoEsquerda(NoArvore * no)
{
	this->esq = no;
}

void NoArvore::setNoDireita(NoArvore * no)
{
	this->dir = no;
}

string NoArvore::getInfo()
{
	return this->info;
}

void Arvore::insere(string nome){
	if(raiz == NULL){
		raiz = new NoArvore(nome);
		cout << "Inserio na raiz" << endl;
	}else{
		insereNo(raiz, nome);
	}
}

Arvore::Arvore()
{
	this->raiz = NULL;
}

void Arvore::insereNo(NoArvore *no, string nome)
{
	if(no->getInfo().compare(nome) > 0){
		if(no->getNoEsquerda() == NULL){
			NoArvore * novoNo = new NoArvore(nome);
			no->setNoEsquerda(novoNo);
			cout << "Inserio na esquerda" << endl;
		}else{
			this->insereNo(no->getNoEsquerda(), nome);
		}
	}else{
		if(no->getNoDireita() == NULL){
			NoArvore * novoNo = new NoArvore(nome);
			no->setNoDireita(novoNo);
			cout << "Inserio na direita" << endl;
		}else{
			this->insereNo(no->getNoDireita(), nome);
		}
	}
}	

void Arvore::imprimeSimetrico(NoArvore *no)
{
	if(no){
	cout << "<";
	imprimeSimetrico(no->getNoEsquerda());
	cout << no->getInfo();
	imprimeSimetrico(no->getNoDireita());
	cout << ">";	
	}
}

NoArvore* Arvore::getRaiz()
{
	cout << "Raiz = " << this->raiz->getInfo() << endl;
	return this->raiz;
}

int main(int argc, char ** argv)
{
	Arvore * arvore = new Arvore();
	arvore->insere("b");
	arvore->insere("c");
	arvore->insere("a");
	arvore->insere("e");
	arvore->insere("f");
	arvore->insere("g");
	arvore->imprimeSimetrico(arvore->getRaiz());
	return 0;
}
