
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
	ifstream in;
	in.open("example.txt");
	if (!in) { /* report an error */ }
	string str;
	while(in.good()){
		string line;
		in >> line;
		str.append(line);
	}
	cout << "Conteudo = " << str << endl;
	return 0;
}
