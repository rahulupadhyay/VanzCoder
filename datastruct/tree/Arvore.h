#ifndef ARVORE_H
#define ARVORE_H
#include <string>

using namespace std;

class NoArvore
{
private:
	string info;
	NoArvore *esq;
	NoArvore *dir;
public:
	NoArvore(string info);
	NoArvore* getNoEsquerda();	
	NoArvore* getNoDireita();	
	void setNoEsquerda(NoArvore * no);	
	void setNoDireita(NoArvore * no);	
	string getInfo();
};

class Arvore
{
	private:		
		NoArvore* raiz;
		void insereNo(NoArvore *no, string nome);
	public:
		Arvore();	
		void insere(string nome);
		void imprimeSimetrico(NoArvore * no);
		NoArvore* getRaiz();
};

#endif
