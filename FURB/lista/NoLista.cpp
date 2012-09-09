/*Implementa o no da lista encadeada
 * Autor: José Guilherme Vanz*/
#include <iostream>
#include <string>
using namespace std;

class NoLista
{

	private:
		string valorNo;
		NoLista *proximoNo;

		void setValor(string valor)
		{
			valorNo = valor;
		}

		void setProximoNo(NoLista *no)
		{
			proximoNo = no;
		}

	public:
		NoLista(string valor, NoLista *proximo) /* Construtor da classe NoLista*/
		{
			setValor(valor);
			setProximoNo(proximo);
		}

		string getValor() /*Retorna valor do no*/
		{
			return valorNo;
		}

		NoLista getProximoNo() /*Retorna proximo no da lista*/
		{
				return *proximoNo;
		}
};

