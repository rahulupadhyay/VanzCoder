
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main () {

//	ifstream in;
//	in.open("example.txt");
//	if (!in) { /* report an error */ }
//	string str;
//	while(in.good()){
//		string line;
//		in >> line;
//		str.append(line);
//	}
//	cout << "Conteudo = " << str << endl;

	FILE* file = fopen("example.txt", "r");
	if(file){
		char line[256];
		char* fileContent;
		memset(fileContent, 0, sizeof(fileContent));
		while(fgets(line,100, file) != NULL){
			strcat(fileContent, line);
		}
		cout << "ARQUIVO = " << fileContent << endl;
	}

	return 0;
}
