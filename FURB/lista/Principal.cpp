/*Implementação do trabalho de lista encadeada
 *Autor: José Guilherme Vanz
 * */
#include<iostream>

using namespace std;


class Principal
{
	private:
		Lista lista;

		void getNomesCidades()
		{
			cout << "Informe o nomes das cidade ( separados por \", \" )" << endl;

		}

		void listarCidades()
		{
			cout << "INÍCIO DA LISTAGEM";
			cout << "FIM DA LISTAGEM" << endl; 
		}

		void limparLista()
		{
			lista.limparLista();
		}

	public:
		Principal() 
		{
			getNomesCidades();	
			listarCidades();
			limparLista();
		}
};

int main()
{
	cout << "L1221C25 – José Guilherme Vanz" << endl;
	Principal principal();
}
