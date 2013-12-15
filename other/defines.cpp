/*
 * This program is only to show how we can use the defines.
 *
 * */

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	#ifdef DEBUG
	cout << "Modo debug ativo" << endl;
	#else
	cout << "Modo debug desativado" << endl;
	#endif
}
