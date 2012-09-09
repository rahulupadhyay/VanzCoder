/*Implementação da lista encadeada
 *Autor: José Guilherme Vanz
 * */
#include<string>
#include<iostream>
#include"NoLista.cpp"

using namespace std;

class Lista
{
	private:
		NoLista *noInicial;
		
		void setNoInicial(NoLista *noInicialLista){
			noInicial = noInicialLista;
		}

	public:
		Lista()
		{
			setNoInicial(NULL);
		}

		NoLista getNoInicial() /*Retorna o no inicial da lista*/
		{
			return *noInicial;
		}

		void limpaLista() /*Limpa a lista encadeada*/
		{
			setNoInicial(NULL);
		}

		bool isEmpty()
		{
			return noInicial == NULL;
		}

		void addLista(string valorNovoNo) /*Adiciona um novo valor na lista*/
		{
			if(isEmpty()) /*Verifica se eh o primeiro elemento da lista*/
			{
				cout << "Empty list " << endl;
			}else
			{
				cout << "The list is not empty" << endl;
			}
		}
};


int main()
{
	Lista lista;
	lista::addLista("");
}
